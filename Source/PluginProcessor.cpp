#include "PluginProcessor.h"
#include "PluginEditor.h"

RedSignalProcessor::RedSignalProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STATE", redsignal::createLayout())
{
}

bool RedSignalProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void RedSignalProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    maxBlock = juce::jmax (1, samplesPerBlock);
    engine.prepare (sampleRate, maxBlock);

    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) maxBlock, 2 };
    chorus.prepare (spec);
    chorus.reset();
    chorus.setCentreDelay (7.0f);
    chorus.setFeedback (0.0f);

    delay.prepare (sampleRate);

    reverb.setSampleRate (sampleRate);
    reverb.reset();
    wetBuffer.setSize (2, maxBlock);

    masterSm.reset (sampleRate, 0.02);
    masterSm.setCurrentAndTargetValue (get ("master"));
}

redsignal::SynthParams RedSignalProcessor::readSynthParams() const
{
    redsignal::SynthParams p;
    for (int i = 0; i < 3; ++i)
    {
        p.osc[i].wave = (int) get (redsignal::oscId (i, "wave"));
        p.osc[i].semis = get (redsignal::oscId (i, "oct")) * 12.0f + get (redsignal::oscId (i, "semi")) + get (redsignal::oscId (i, "fine")) / 100.0f;
        p.osc[i].level = get (redsignal::oscId (i, "level"));
    }
    p.ampA = get ("amp_a");
    p.ampD = get ("amp_d");
    p.ampS = get ("amp_s");
    p.ampR = get ("amp_r");
    p.filterType = (int) get ("f_type");
    p.cutoff = get ("f_cut");
    const float res = get ("f_res");
    p.q = 0.7f + res * res * 12.0f;
    p.envAmount = get ("f_env");
    p.envDecay = get ("f_dec");
    return p;
}

void RedSignalProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    const int n = buffer.getNumSamples();
    buffer.clear();
    if (buffer.getNumChannels() < 2 || n == 0)
        return;

    engine.process (buffer, midi, readSynthParams());

    float* l = buffer.getWritePointer (0);
    float* r = buffer.getWritePointer (1);

    // Chorus
    chorus.setRate (get ("ch_rate"));
    chorus.setDepth (get ("ch_depth"));
    chorus.setMix (get ("ch_mix"));
    for (int pos = 0; pos < n; pos += maxBlock)
    {
        const int c = juce::jmin (maxBlock, n - pos);
        juce::dsp::AudioBlock<float> block (buffer);
        auto sub = block.getSubBlock ((size_t) pos, (size_t) c);
        chorus.process (juce::dsp::ProcessContextReplacing<float> (sub));
    }

    // Delay
    delay.setParams (get ("dl_time"), get ("dl_fb"), get ("dl_mix"), get ("dl_pp") > 0.5f);
    delay.process (l, r, n);

    // Reverb (crossfade between dry and wet)
    juce::Reverb::Parameters rp;
    rp.roomSize = get ("rv_size");
    rp.damping = get ("rv_damp");
    rp.wetLevel = 0.33f;
    rp.dryLevel = 0.0f;
    rp.width = 1.0f;
    rp.freezeMode = 0.0f;
    reverb.setParameters (rp);
    const float rvMix = get ("rv_mix");
    for (int pos = 0; pos < n; pos += maxBlock)
    {
        const int c = juce::jmin (maxBlock, n - pos);
        float* wl = wetBuffer.getWritePointer (0);
        float* wr = wetBuffer.getWritePointer (1);
        juce::FloatVectorOperations::copy (wl, l + pos, c);
        juce::FloatVectorOperations::copy (wr, r + pos, c);
        reverb.processStereo (wl, wr, c);
        for (int i = 0; i < c; ++i)
        {
            l[pos + i] = l[pos + i] * (1.0f - rvMix) + wl[i] * rvMix;
            r[pos + i] = r[pos + i] * (1.0f - rvMix) + wr[i] * rvMix;
        }
    }

    // Master volume and soft limiter
    masterSm.setTargetValue (get ("master"));
    auto softClip = [] (float x)
    {
        const float a = std::abs (x);
        if (a <= 0.8f) return x;
        const float y = 0.8f + 0.2f * std::tanh ((a - 0.8f) / 0.2f);
        return x < 0.0f ? -y : y;
    };
    for (int i = 0; i < n; ++i)
    {
        const float g = masterSm.getNextValue();
        l[i] = softClip (l[i] * g);
        r[i] = softClip (r[i] * g);
    }
}

juce::AudioProcessorEditor* RedSignalProcessor::createEditor()
{
    return new RedSignalEditor (*this);
}

void RedSignalProcessor::loadFactoryPreset (int index)
{
    const auto& bank = redsignal::getFactoryPresets();
    if (bank.empty()) return;
    currentProgram = juce::jlimit (0, (int) bank.size() - 1, index);

    for (const auto& entry : bank[(size_t) currentProgram].values)
    {
        if (auto* parameter = dynamic_cast<juce::RangedAudioParameter*> (apvts.getParameter (entry.first)))
            parameter->setValueNotifyingHost (parameter->convertTo0to1 (entry.second));
    }
}

void RedSignalProcessor::setCurrentProgram (int index)
{
    loadFactoryPreset (index);
}

const juce::String RedSignalProcessor::getProgramName (int index)
{
    const auto& bank = redsignal::getFactoryPresets();
    if (juce::isPositiveAndBelow (index, (int) bank.size()))
        return bank[(size_t) index].category + " - " + bank[(size_t) index].name;
    return {};
}

void RedSignalProcessor::getStateInformation (juce::MemoryBlock& dest)
{
    auto state = apvts.copyState();
    state.setProperty ("factoryProgram", currentProgram, nullptr);
    if (auto xml = state.createXml())
        copyXmlToBinary (*xml, dest);
}

void RedSignalProcessor::setStateInformation (const void* data, int size)
{
    if (auto xml = getXmlFromBinary (data, size))
    {
        if (xml->hasTagName (apvts.state.getType()))
        {
            auto state = juce::ValueTree::fromXml (*xml);
            currentProgram = (int) state.getProperty ("factoryProgram", 0);
            apvts.replaceState (state);
        }
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RedSignalProcessor();
}
