#pragma once
#include "Common.h"
#include "Parameters.h"
#include "SynthEngine.h"
#include "Effects.h"
#include "Presets.h"

class RedSignalProcessor : public juce::AudioProcessor
{
public:
    RedSignalProcessor();
    ~RedSignalProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "RED SIGNAL"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 5.0; }

    int getNumPrograms() override { return (int) redsignal::getFactoryPresets().size(); }
    int getCurrentProgram() override { return currentProgram; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& dest) override;
    void setStateInformation (const void* data, int size) override;

    juce::AudioProcessorValueTreeState apvts;
    void loadFactoryPreset (int index);

private:
    float get (const juce::String& id) const { return apvts.getRawParameterValue (id)->load(); }
    redsignal::SynthParams readSynthParams() const;

    redsignal::SynthEngine engine;
    juce::dsp::Chorus<float> chorus;
    redsignal::StereoDelay delay;
    juce::Reverb reverb;
    juce::AudioBuffer<float> wetBuffer;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> masterSm;
    int maxBlock = 512;
    int currentProgram = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedSignalProcessor)
};
