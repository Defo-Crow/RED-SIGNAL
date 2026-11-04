#pragma once
#include "Common.h"
#include <map>

namespace redsignal
{
struct FactoryPreset
{
    juce::String category;
    juce::String name;
    std::vector<std::pair<juce::String, float>> values;
};

inline const std::vector<FactoryPreset>& getFactoryPresets()
{
    static const auto presets = []
    {
        std::vector<FactoryPreset> result;
        const std::map<juce::String, float> defaults {
            { "osc1_wave", 1 }, { "osc1_oct", 0 }, { "osc1_semi", 0 }, { "osc1_fine", 0 }, { "osc1_level", 0.80f },
            { "osc2_wave", 1 }, { "osc2_oct", 0 }, { "osc2_semi", 0 }, { "osc2_fine", 8 }, { "osc2_level", 0.50f },
            { "osc3_wave", 2 }, { "osc3_oct", -1 }, { "osc3_semi", 0 }, { "osc3_fine", 0 }, { "osc3_level", 0.30f },
            { "amp_a", 0.01f }, { "amp_d", 0.30f }, { "amp_s", 0.70f }, { "amp_r", 0.40f },
            { "f_type", 0 }, { "f_cut", 4000 }, { "f_res", 0.20f }, { "f_env", 0.30f }, { "f_dec", 0.50f },
            { "master", 0.72f },
            { "ch_rate", 0.80f }, { "ch_depth", 0.40f }, { "ch_mix", 0.30f },
            { "dl_time", 350 }, { "dl_fb", 0.40f }, { "dl_mix", 0.20f }, { "dl_pp", 1 },
            { "rv_size", 0.60f }, { "rv_damp", 0.50f }, { "rv_mix", 0.25f }
        };

        auto add = [&] (const char* category, const char* name,
                        std::initializer_list<std::pair<const char*, float>> overrides)
        {
            auto values = defaults;
            for (const auto& item : overrides)
                values[item.first] = item.second;

            FactoryPreset preset;
            preset.category = category;
            preset.name = name;
            for (const auto& item : values)
                preset.values.emplace_back (item.first, item.second);
            result.push_back (std::move (preset));
        };

        // BASS — compact, warm, slightly unstable low-end sounds.
        add ("BASS", "Red Sub",       {{"osc1_wave", 2}, {"osc1_level", .65f}, {"osc2_wave", 0}, {"osc2_oct", -1}, {"osc2_level", .85f}, {"osc3_level", .12f}, {"f_cut", 180}, {"f_res", .12f}, {"amp_d", .22f}, {"amp_s", .82f}, {"amp_r", .18f}, {"ch_mix", .05f}, {"rv_mix", .04f}});
        add ("BASS", "Tramline Bass",  {{"osc1_wave", 2}, {"osc2_wave", 2}, {"osc2_oct", -1}, {"osc2_fine", -4}, {"osc2_level", .62f}, {"f_cut", 620}, {"f_res", .32f}, {"f_env", .20f}, {"amp_d", .28f}, {"amp_s", .62f}, {"amp_r", .22f}, {"dl_mix", .08f}, {"rv_mix", .05f}});
        add ("BASS", "Concrete Pulse", {{"osc1_wave", 2}, {"osc1_level", .85f}, {"osc2_wave", 1}, {"osc2_oct", -1}, {"osc2_level", .42f}, {"f_cut", 950}, {"f_res", .48f}, {"f_env", .55f}, {"amp_d", .18f}, {"amp_s", .48f}, {"amp_r", .15f}});
        add ("BASS", "Night Drive",    {{"osc1_wave", 1}, {"osc2_wave", 1}, {"osc2_fine", 14}, {"osc2_level", .48f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .3f}, {"f_cut", 520}, {"f_res", .16f}, {"amp_d", .42f}, {"amp_s", .68f}, {"amp_r", .32f}, {"ch_mix", .16f}});
        add ("BASS", "KGB Sequence",   {{"osc1_wave", 2}, {"osc2_wave", 1}, {"osc2_oct", -1}, {"osc2_level", .55f}, {"osc3_wave", 3}, {"osc3_oct", -2}, {"osc3_level", .25f}, {"f_cut", 340}, {"f_res", .62f}, {"f_env", .72f}, {"amp_d", .12f}, {"amp_s", .35f}, {"amp_r", .14f}});
        add ("BASS", "Soviet FM",      {{"osc1_wave", 0}, {"osc2_wave", 2}, {"osc2_oct", 1}, {"osc2_level", .25f}, {"osc3_wave", 1}, {"osc3_oct", -1}, {"osc3_level", .55f}, {"f_cut", 1300}, {"f_res", .2f}, {"amp_d", .16f}, {"amp_s", .55f}, {"amp_r", .18f}});
        add ("BASS", "Cold Engine",    {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_oct", -1}, {"osc2_level", .5f}, {"f_cut", 250}, {"f_res", .25f}, {"f_env", .18f}, {"amp_a", .04f}, {"amp_d", .6f}, {"amp_s", .75f}, {"amp_r", .55f}, {"rv_mix", .12f}});
        add ("BASS", "Tape Motor",     {{"osc1_wave", 3}, {"osc2_wave", 1}, {"osc2_oct", -1}, {"osc2_fine", -11}, {"osc2_level", .4f}, {"f_cut", 740}, {"f_res", .1f}, {"amp_a", .025f}, {"amp_d", .4f}, {"amp_s", .72f}, {"amp_r", .3f}, {"ch_rate", .22f}, {"ch_depth", .18f}, {"ch_mix", .28f}});
        add ("BASS", "Red Square",     {{"osc1_wave", 2}, {"osc1_oct", -1}, {"osc2_wave", 1}, {"osc2_oct", -1}, {"osc2_fine", 6}, {"osc2_level", .58f}, {"f_cut", 430}, {"f_res", .7f}, {"f_env", .35f}, {"amp_d", .25f}, {"amp_s", .5f}, {"amp_r", .22f}});
        add ("BASS", "Deep Archive",   {{"osc1_wave", 0}, {"osc1_oct", -1}, {"osc1_level", .88f}, {"osc2_wave", 3}, {"osc2_oct", -1}, {"osc2_level", .32f}, {"f_cut", 210}, {"amp_a", .08f}, {"amp_d", .9f}, {"amp_s", .8f}, {"amp_r", .8f}, {"rv_mix", .2f}});

        // LEAD — focused mono-like voices, cutting through a nostalgic mix.
        add ("LEAD", "Signal Flare",   {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_fine", 7}, {"osc2_level", .46f}, {"osc3_wave", 0}, {"osc3_oct", 1}, {"osc3_level", .18f}, {"f_cut", 4200}, {"f_res", .28f}, {"f_env", .24f}, {"amp_d", .35f}, {"amp_s", .7f}, {"amp_r", .3f}, {"dl_mix", .24f}});
        add ("LEAD", "Last Broadcast", {{"osc1_wave", 1}, {"osc2_wave", 1}, {"osc2_fine", -13}, {"osc2_level", .5f}, {"f_cut", 2600}, {"f_res", .18f}, {"amp_a", .025f}, {"amp_d", .5f}, {"amp_s", .76f}, {"amp_r", .7f}, {"ch_mix", .28f}, {"rv_mix", .2f}});
        add ("LEAD", "Red Beacon",     {{"osc1_wave", 2}, {"osc2_wave", 0}, {"osc2_oct", 1}, {"osc2_level", .22f}, {"osc3_wave", 1}, {"osc3_level", .28f}, {"f_cut", 5200}, {"f_res", .42f}, {"f_env", .35f}, {"amp_d", .22f}, {"amp_s", .62f}, {"amp_r", .24f}, {"dl_mix", .3f}});
        add ("LEAD", "Neon District",  {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_fine", 10}, {"osc2_level", .42f}, {"osc3_wave", 3}, {"osc3_oct", 1}, {"osc3_level", .2f}, {"f_cut", 3300}, {"f_res", .24f}, {"amp_a", .015f}, {"amp_d", .28f}, {"amp_s", .78f}, {"amp_r", .38f}, {"ch_mix", .34f}});
        add ("LEAD", "Sputnik Lead",   {{"osc1_wave", 0}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", 5}, {"osc2_level", .35f}, {"osc3_wave", 2}, {"osc3_oct", 1}, {"osc3_level", .22f}, {"f_cut", 6100}, {"amp_d", .22f}, {"amp_s", .6f}, {"amp_r", .25f}, {"dl_time", 280}, {"dl_mix", .24f}});
        add ("LEAD", "Museum Glass",   {{"osc1_wave", 3}, {"osc2_wave", 1}, {"osc2_fine", -9}, {"osc2_level", .3f}, {"f_cut", 2900}, {"f_res", .12f}, {"amp_a", .07f}, {"amp_d", .8f}, {"amp_s", .68f}, {"amp_r", .8f}, {"rv_size", .78f}, {"rv_mix", .3f}});
        add ("LEAD", "Voltage Bloom",  {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_oct", 1}, {"osc2_level", .25f}, {"osc3_wave", 1}, {"osc3_oct", -1}, {"osc3_level", .16f}, {"f_cut", 4800}, {"f_res", .55f}, {"f_env", .5f}, {"amp_a", .01f}, {"amp_d", .42f}, {"amp_s", .64f}, {"amp_r", .45f}});
        add ("LEAD", "Winter Radio",   {{"osc1_wave", 1}, {"osc2_wave", 3}, {"osc2_fine", 17}, {"osc2_level", .42f}, {"f_cut", 1800}, {"f_res", .16f}, {"amp_a", .045f}, {"amp_d", .65f}, {"amp_s", .68f}, {"amp_r", .65f}, {"ch_rate", .45f}, {"ch_depth", .55f}, {"ch_mix", .38f}});
        add ("LEAD", "Transmission",  {{"osc1_wave", 2}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", -5}, {"osc2_level", .42f}, {"f_cut", 3600}, {"f_res", .72f}, {"f_env", .42f}, {"amp_d", .16f}, {"amp_s", .5f}, {"amp_r", .2f}, {"dl_mix", .18f}});
        add ("LEAD", "Moscow Lights",  {{"osc1_wave", 1}, {"osc2_wave", 1}, {"osc2_fine", 5}, {"osc2_level", .54f}, {"osc3_wave", 0}, {"osc3_level", .23f}, {"f_cut", 2500}, {"amp_a", .03f}, {"amp_d", .34f}, {"amp_s", .73f}, {"amp_r", .54f}, {"ch_mix", .32f}, {"dl_mix", .22f}});

        // PAD — slow attacks, long tails, detuned oscillators and wide effects.
        add ("PAD", "Empty Platform", {{"osc1_wave", 1}, {"osc2_wave", 1}, {"osc2_fine", -12}, {"osc2_level", .52f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .34f}, {"amp_a", 1.5f}, {"amp_d", 2.5f}, {"amp_s", .8f}, {"amp_r", 4.5f}, {"f_cut", 1700}, {"ch_mix", .65f}, {"rv_size", .88f}, {"rv_mix", .5f}});
        add ("PAD", "Velvet Curtain", {{"osc1_wave", 3}, {"osc2_wave", 1}, {"osc2_fine", 9}, {"osc2_level", .38f}, {"osc3_wave", 0}, {"osc3_level", .3f}, {"amp_a", .8f}, {"amp_d", 2.2f}, {"amp_s", .76f}, {"amp_r", 3.2f}, {"f_cut", 2200}, {"ch_rate", .32f}, {"ch_depth", .72f}, {"ch_mix", .5f}, {"rv_mix", .4f}});
        add ("PAD", "Soviet Dawn",    {{"osc1_wave", 1}, {"osc2_wave", 3}, {"osc2_oct", 1}, {"osc2_fine", -7}, {"osc2_level", .26f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .5f}, {"amp_a", 2.2f}, {"amp_d", 3.5f}, {"amp_s", .84f}, {"amp_r", 5.5f}, {"f_cut", 1500}, {"rv_size", .95f}, {"rv_mix", .56f}});
        add ("PAD", "Grey Horizon",   {{"osc1_wave", 0}, {"osc2_wave", 1}, {"osc2_fine", 14}, {"osc2_level", .5f}, {"osc3_wave", 3}, {"osc3_oct", -1}, {"osc3_level", .3f}, {"amp_a", 1.1f}, {"amp_d", 2.4f}, {"amp_s", .68f}, {"amp_r", 4.2f}, {"f_cut", 900}, {"f_res", .12f}, {"ch_mix", .7f}, {"rv_mix", .45f}});
        add ("PAD", "Frozen TV Tower",{{"osc1_wave", 1}, {"osc2_wave", 1}, {"osc2_fine", 22}, {"osc2_level", .44f}, {"osc3_wave", 2}, {"osc3_oct", 1}, {"osc3_level", .14f}, {"amp_a", 2.5f}, {"amp_d", 4}, {"amp_s", .72f}, {"amp_r", 6}, {"f_cut", 1200}, {"f_res", .28f}, {"ch_rate", .18f}, {"ch_mix", .6f}, {"rv_mix", .6f}});
        add ("PAD", "Midnight Tram",   {{"osc1_wave", 1}, {"osc2_wave", 3}, {"osc2_fine", -16}, {"osc2_level", .42f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .22f}, {"amp_a", .9f}, {"amp_d", 1.8f}, {"amp_s", .75f}, {"amp_r", 3.8f}, {"f_cut", 1250}, {"ch_mix", .46f}, {"dl_mix", .28f}, {"rv_mix", .42f}});
        add ("PAD", "Red Snowfall",   {{"osc1_wave", 3}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", 12}, {"osc2_level", .33f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .36f}, {"amp_a", 1.8f}, {"amp_d", 3.2f}, {"amp_s", .7f}, {"amp_r", 4.8f}, {"f_cut", 2400}, {"ch_mix", .54f}, {"rv_size", .9f}, {"rv_mix", .55f}});
        add ("PAD", "Concrete Cathedral",{{"osc1_wave", 1}, {"osc2_wave", 1}, {"osc2_fine", -6}, {"osc2_level", .42f}, {"osc3_wave", 3}, {"osc3_oct", -1}, {"osc3_level", .35f}, {"amp_a", 3.2f}, {"amp_d", 4.5f}, {"amp_s", .82f}, {"amp_r", 7}, {"f_cut", 800}, {"ch_mix", .42f}, {"rv_size", .98f}, {"rv_damp", .25f}, {"rv_mix", .64f}});
        add ("PAD", "Blue Apartment", {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_fine", 16}, {"osc2_level", .27f}, {"osc3_wave", 0}, {"osc3_level", .35f}, {"amp_a", 1.25f}, {"amp_d", 2.1f}, {"amp_s", .8f}, {"amp_r", 3.5f}, {"f_cut", 1900}, {"ch_rate", .25f}, {"ch_depth", .8f}, {"ch_mix", .52f}, {"rv_mix", .34f}});
        add ("PAD", "Last Snow",       {{"osc1_wave", 0}, {"osc2_wave", 3}, {"osc2_oct", 1}, {"osc2_fine", -18}, {"osc2_level", .42f}, {"osc3_wave", 1}, {"osc3_oct", -1}, {"osc3_level", .26f}, {"amp_a", 2.7f}, {"amp_d", 3.8f}, {"amp_s", .73f}, {"amp_r", 6.5f}, {"f_cut", 1400}, {"dl_time", 520}, {"dl_mix", .35f}, {"rv_mix", .58f}});

        // KEYS — plucks, electric-piano-like tones, bells and soft organs.
        add ("KEYS", "Apartment EP",  {{"osc1_wave", 0}, {"osc2_wave", 3}, {"osc2_oct", 1}, {"osc2_level", .42f}, {"osc3_wave", 2}, {"osc3_oct", 1}, {"osc3_level", .12f}, {"amp_a", .003f}, {"amp_d", .7f}, {"amp_s", .25f}, {"amp_r", .5f}, {"f_cut", 5200}, {"f_env", .45f}, {"ch_mix", .2f}, {"rv_mix", .18f}});
        add ("KEYS", "Glass Keys",     {{"osc1_wave", 0}, {"osc2_wave", 0}, {"osc2_oct", 1}, {"osc2_level", .32f}, {"osc3_wave", 3}, {"osc3_oct", 2}, {"osc3_level", .22f}, {"amp_a", .002f}, {"amp_d", 1.4f}, {"amp_s", .08f}, {"amp_r", 1.2f}, {"f_cut", 8000}, {"rv_size", .72f}, {"rv_mix", .36f}});
        add ("KEYS", "Tape Piano",     {{"osc1_wave", 0}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", -8}, {"osc2_level", .22f}, {"amp_a", .004f}, {"amp_d", .9f}, {"amp_s", .3f}, {"amp_r", .65f}, {"f_cut", 3800}, {"ch_rate", .35f}, {"ch_depth", .38f}, {"ch_mix", .35f}, {"rv_mix", .22f}});
        add ("KEYS", "Soviet Organ",   {{"osc1_wave", 2}, {"osc2_wave", 2}, {"osc2_oct", 1}, {"osc2_level", .38f}, {"osc3_wave", 2}, {"osc3_oct", -1}, {"osc3_level", .2f}, {"amp_a", .005f}, {"amp_d", .2f}, {"amp_s", .95f}, {"amp_r", .12f}, {"f_cut", 6200}, {"ch_mix", .12f}, {"rv_mix", .1f}});
        add ("KEYS", "Station Bell",   {{"osc1_wave", 0}, {"osc2_wave", 3}, {"osc2_oct", 2}, {"osc2_level", .42f}, {"osc3_wave", 1}, {"osc3_oct", 1}, {"osc3_level", .12f}, {"amp_a", .001f}, {"amp_d", 1.8f}, {"amp_s", .02f}, {"amp_r", 1.4f}, {"f_cut", 9500}, {"dl_time", 410}, {"dl_mix", .24f}, {"rv_mix", .34f}});
        add ("KEYS", "Warm Mallet",    {{"osc1_wave", 0}, {"osc2_wave", 3}, {"osc2_oct", 1}, {"osc2_level", .3f}, {"amp_a", .001f}, {"amp_d", .55f}, {"amp_s", .12f}, {"amp_r", .4f}, {"f_cut", 4600}, {"f_env", .62f}, {"rv_mix", .15f}});
        add ("KEYS", "Night Shift",    {{"osc1_wave", 1}, {"osc2_wave", 0}, {"osc2_oct", 1}, {"osc2_level", .26f}, {"osc3_wave", 3}, {"osc3_level", .2f}, {"amp_a", .008f}, {"amp_d", .52f}, {"amp_s", .48f}, {"amp_r", .38f}, {"f_cut", 3100}, {"f_res", .15f}, {"ch_mix", .3f}});
        add ("KEYS", "Cinema Chime",   {{"osc1_wave", 0}, {"osc2_wave", 0}, {"osc2_oct", 2}, {"osc2_level", .25f}, {"osc3_wave", 3}, {"osc3_oct", 1}, {"osc3_fine", 11}, {"osc3_level", .18f}, {"amp_a", .001f}, {"amp_d", 1.6f}, {"amp_s", .04f}, {"amp_r", 1.8f}, {"f_cut", 10000}, {"rv_size", .84f}, {"rv_mix", .4f}});
        add ("KEYS", "Memory Keys",    {{"osc1_wave", 3}, {"osc2_wave", 0}, {"osc2_oct", 1}, {"osc2_fine", -5}, {"osc2_level", .38f}, {"amp_a", .025f}, {"amp_d", 1.1f}, {"amp_s", .38f}, {"amp_r", .95f}, {"f_cut", 3000}, {"ch_mix", .44f}, {"rv_mix", .3f}});
        add ("KEYS", "Plastic DX",     {{"osc1_wave", 0}, {"osc2_wave", 2}, {"osc2_oct", 2}, {"osc2_level", .18f}, {"osc3_wave", 3}, {"osc3_oct", 1}, {"osc3_level", .35f}, {"amp_a", .002f}, {"amp_d", .8f}, {"amp_s", .18f}, {"amp_r", .55f}, {"f_cut", 7200}, {"f_res", .36f}, {"dl_mix", .18f}});

        // SFX — tonal machines, warning tones and distant radio-like textures.
        add ("SFX", "Air Raid",        {{"osc1_wave", 2}, {"osc2_wave", 0}, {"osc2_oct", 1}, {"osc2_level", .25f}, {"osc3_wave", 1}, {"osc3_oct", -1}, {"osc3_level", .2f}, {"amp_a", .02f}, {"amp_d", 1.5f}, {"amp_s", .55f}, {"amp_r", 2.5f}, {"f_cut", 1800}, {"f_res", .65f}, {"dl_time", 620}, {"dl_mix", .28f}, {"rv_mix", .38f}});
        add ("SFX", "Numbers Station",{{"osc1_wave", 0}, {"osc2_wave", 2}, {"osc2_oct", 2}, {"osc2_fine", 19}, {"osc2_level", .28f}, {"osc3_wave", 4}, {"osc3_oct", -1}, {"osc3_fine", -23}, {"osc3_level", .18f}, {"amp_a", .001f}, {"amp_d", 1.1f}, {"amp_s", .24f}, {"amp_r", 1.5f}, {"f_cut", 5000}, {"f_res", .6f}, {"dl_mix", .32f}});
        add ("SFX", "Metal Corridor", {{"osc1_wave", 2}, {"osc2_wave", 0}, {"osc2_oct", 2}, {"osc2_level", .22f}, {"osc3_wave", 4}, {"osc3_oct", 1}, {"osc3_level", .3f}, {"amp_a", .001f}, {"amp_d", 2.2f}, {"amp_s", .04f}, {"amp_r", 2.8f}, {"f_cut", 9200}, {"f_res", .8f}, {"rv_size", .95f}, {"rv_mix", .58f}});
        add ("SFX", "Shortwave Ghost",{{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_fine", 31}, {"osc2_level", .24f}, {"osc3_wave", 0}, {"osc3_oct", 2}, {"osc3_fine", -17}, {"osc3_level", .2f}, {"amp_a", .12f}, {"amp_d", 1.8f}, {"amp_s", .22f}, {"amp_r", 3.2f}, {"f_cut", 2600}, {"f_res", .74f}, {"ch_mix", .48f}, {"dl_mix", .38f}});
        add ("SFX", "Voltage Arc",    {{"osc1_wave", 2}, {"osc2_wave", 1}, {"osc2_oct", 2}, {"osc2_level", .4f}, {"osc3_wave", 2}, {"osc3_oct", -2}, {"osc3_level", .3f}, {"amp_a", .001f}, {"amp_d", .16f}, {"amp_s", .08f}, {"amp_r", .08f}, {"f_cut", 7600}, {"f_res", .88f}, {"f_env", .86f}});
        add ("SFX", "Radar Sweep",    {{"osc1_wave", 0}, {"osc2_wave", 1}, {"osc2_oct", 2}, {"osc2_level", .25f}, {"osc3_wave", 3}, {"osc3_oct", -1}, {"osc3_level", .18f}, {"amp_a", .08f}, {"amp_d", 1.4f}, {"amp_s", .4f}, {"amp_r", 1.8f}, {"f_cut", 1200}, {"f_res", .72f}, {"dl_time", 470}, {"rv_mix", .3f}});
        add ("SFX", "Power Station",  {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_oct", -1}, {"osc2_level", .38f}, {"osc3_wave", 0}, {"osc3_oct", 1}, {"osc3_level", .25f}, {"amp_a", .25f}, {"amp_d", 2.8f}, {"amp_s", .75f}, {"amp_r", 3.5f}, {"f_cut", 680}, {"f_res", .4f}, {"ch_rate", .12f}, {"ch_mix", .25f}});
        add ("SFX", "Broken TV",      {{"osc1_wave", 2}, {"osc2_wave", 3}, {"osc2_oct", 2}, {"osc2_fine", 27}, {"osc2_level", .34f}, {"osc3_wave", 1}, {"osc3_oct", -2}, {"osc3_level", .24f}, {"amp_a", .001f}, {"amp_d", .42f}, {"amp_s", .12f}, {"amp_r", .35f}, {"f_cut", 9800}, {"f_res", .92f}, {"dl_mix", .12f}});
        add ("SFX", "Distant Siren",  {{"osc1_wave", 0}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", 6}, {"osc2_level", .36f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .22f}, {"amp_a", .3f}, {"amp_d", 2.8f}, {"amp_s", .8f}, {"amp_r", 3.8f}, {"f_cut", 1500}, {"f_res", .42f}, {"rv_size", .92f}, {"rv_mix", .52f}});
        add ("SFX", "Cold Machinery", {{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_oct", -1}, {"osc2_fine", -21}, {"osc2_level", .28f}, {"osc3_wave", 4}, {"osc3_oct", 2}, {"osc3_level", .22f}, {"amp_a", .4f}, {"amp_d", 2.2f}, {"amp_s", .62f}, {"amp_r", 3.2f}, {"f_cut", 2100}, {"f_res", .22f}, {"ch_mix", .34f}, {"rv_mix", .42f}});

        // OTHER — plucks, arpeggio-friendly patches and hybrid textures.
        add ("OTHER", "Metro Pluck",   {{"osc1_wave", 2}, {"osc2_wave", 0}, {"osc2_oct", 1}, {"osc2_level", .25f}, {"amp_a", .001f}, {"amp_d", .38f}, {"amp_s", .08f}, {"amp_r", .22f}, {"f_cut", 3600}, {"f_env", .7f}, {"dl_time", 260}, {"dl_mix", .2f}});
        add ("OTHER", "Glass Arp",     {{"osc1_wave", 0}, {"osc2_wave", 3}, {"osc2_oct", 1}, {"osc2_level", .34f}, {"osc3_wave", 0}, {"osc3_oct", 2}, {"osc3_level", .18f}, {"amp_a", .002f}, {"amp_d", .62f}, {"amp_s", .12f}, {"amp_r", .48f}, {"f_cut", 7200}, {"dl_time", 300}, {"dl_fb", .48f}, {"dl_mix", .3f}, {"rv_mix", .3f}});
        add ("OTHER", "Night Sequence",{{"osc1_wave", 1}, {"osc2_wave", 2}, {"osc2_oct", 1}, {"osc2_fine", -7}, {"osc2_level", .28f}, {"osc3_wave", 3}, {"osc3_oct", -1}, {"osc3_level", .22f}, {"amp_a", .006f}, {"amp_d", .5f}, {"amp_s", .45f}, {"amp_r", .32f}, {"f_cut", 2400}, {"f_res", .36f}, {"dl_mix", .26f}});
        add ("OTHER", "Tape Pluck",    {{"osc1_wave", 3}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", 13}, {"osc2_level", .25f}, {"amp_a", .003f}, {"amp_d", .85f}, {"amp_s", .18f}, {"amp_r", .75f}, {"f_cut", 4200}, {"ch_rate", .27f}, {"ch_mix", .32f}, {"rv_mix", .24f}});
        add ("OTHER", "Starlight",      {{"osc1_wave", 0}, {"osc2_wave", 1}, {"osc2_oct", 1}, {"osc2_fine", -16}, {"osc2_level", .36f}, {"osc3_wave", 3}, {"osc3_oct", 2}, {"osc3_level", .18f}, {"amp_a", .2f}, {"amp_d", 1.8f}, {"amp_s", .6f}, {"amp_r", 2.4f}, {"f_cut", 4600}, {"dl_mix", .3f}, {"rv_mix", .4f}});
        add ("OTHER", "Analog Sequence",{{"osc1_wave", 2}, {"osc2_wave", 1}, {"osc2_oct", -1}, {"osc2_level", .45f}, {"osc3_wave", 3}, {"osc3_oct", 1}, {"osc3_level", .2f}, {"amp_a", .004f}, {"amp_d", .24f}, {"amp_s", .35f}, {"amp_r", .14f}, {"f_cut", 1600}, {"f_res", .58f}, {"f_env", .62f}, {"dl_mix", .16f}});
        add ("OTHER", "Memory Leak",    {{"osc1_wave", 1}, {"osc2_wave", 0}, {"osc2_oct", 2}, {"osc2_fine", 18}, {"osc2_level", .22f}, {"osc3_wave", 3}, {"osc3_oct", -1}, {"osc3_fine", -12}, {"osc3_level", .24f}, {"amp_a", .08f}, {"amp_d", 1.1f}, {"amp_s", .52f}, {"amp_r", 1.5f}, {"f_cut", 2700}, {"ch_mix", .52f}, {"dl_mix", .36f}});
        add ("OTHER", "Warm Circuit",   {{"osc1_wave", 3}, {"osc2_wave", 1}, {"osc2_fine", 6}, {"osc2_level", .45f}, {"osc3_wave", 0}, {"osc3_oct", -1}, {"osc3_level", .2f}, {"amp_a", .015f}, {"amp_d", .75f}, {"amp_s", .64f}, {"amp_r", .6f}, {"f_cut", 3300}, {"ch_mix", .28f}, {"rv_mix", .18f}});
        add ("OTHER", "Terminal Bloom", {{"osc1_wave", 0}, {"osc2_wave", 2}, {"osc2_oct", 1}, {"osc2_level", .3f}, {"osc3_wave", 1}, {"osc3_oct", -1}, {"osc3_fine", 14}, {"osc3_level", .22f}, {"amp_a", .45f}, {"amp_d", 1.5f}, {"amp_s", .58f}, {"amp_r", 2.2f}, {"f_cut", 2200}, {"rv_size", .9f}, {"rv_mix", .46f}});
        add ("OTHER", "Sunset Boulevard",{{"osc1_wave", 1}, {"osc2_wave", 3}, {"osc2_fine", -8}, {"osc2_level", .35f}, {"osc3_wave", 0}, {"osc3_level", .3f}, {"amp_a", .03f}, {"amp_d", 1.1f}, {"amp_s", .72f}, {"amp_r", 1.25f}, {"f_cut", 2900}, {"ch_mix", .48f}, {"dl_time", 430}, {"dl_mix", .24f}, {"rv_mix", .28f}});
        return result;
    }();
    return presets;
}

inline juce::StringArray getPresetCategories()
{
    return { "BASS", "LEAD", "PAD", "KEYS", "SFX", "OTHER" };
}
} // namespace redsignal
