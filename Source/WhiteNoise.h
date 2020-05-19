/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2017 - ROLI Ltd.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             SynthLevelControlTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Synthesiser with level control.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
class MainContentComponent   : public AudioAppComponent
{
public:
    MainContentComponent()
    {
        setSize (600, 100);
        setAudioChannels (0, 2);

        addLeftNoiseLevelSlider();
        addRightNoiseLevelSlider();
    }

    void addRightNoiseLevelSlider() {
        channel0LevelSlider.setRange(0.0, 0.25);
        channel0LevelSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
        channel0LevelLabel.setText("Channel 0 Level", dontSendNotification);

        addAndMakeVisible(channel0LevelSlider);
        addAndMakeVisible(channel0LevelLabel);
    }

    void addLeftNoiseLevelSlider() {
        channel1LevelSlider.setRange (0.0, 0.25);
        channel1LevelSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
        channel1LevelLabel.setText ("Channel 1 Level", dontSendNotification);

        addAndMakeVisible(channel1LevelSlider);
        addAndMakeVisible(channel1LevelLabel);
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }

    void prepareToPlay (int, double) override {}

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            float level = 0.0;

            if (channel == 0)
            {
                level = (float) channel0LevelSlider.getValue();
            }
            if (channel == 1)
            {
                level = (float) channel1LevelSlider.getValue();
            }

            auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            {
                auto noise = random.nextFloat() * 2 - 1.0f;
                buffer[sample] = noise * level;
            }
        }
    }

    void releaseResources() override {}

    void resized() override
    {
        channel0LevelLabel.setBounds(10, 10, 90, 20);
        channel0LevelSlider.setBounds(100, 10, getWidth() - 110, 20);

        channel1LevelLabel .setBounds (10, 40, 90, 20);
        channel1LevelSlider.setBounds (100, 40, getWidth() - 110, 20);
    }

private:
    Random random;

    Slider channel1LevelSlider;
    Label  channel1LevelLabel;

    Slider channel0LevelSlider;
    Label  channel0LevelLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
