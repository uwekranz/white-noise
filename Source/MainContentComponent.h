#pragma once

#include "DecibelSlider.h"

class MainContentComponent : public AudioAppComponent {
public:
    MainContentComponent();

    ~MainContentComponent() override;

    void prepareToPlay(int, double) override;

    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;

    void releaseResources() override;

    void resized() override;

    void addGainSlider(const String &labelText, Slider &slider, Label &label);

    void addDecibelSlider(const String &labelText, DecibelSlider &slider, Label &label);

    void addSliders();

private:
    float channel0Level = 0;
    float channel1Level = 0;

    Random random;

    Slider channel0GainSlider;
    Label channel0GainLabel;
    DecibelSlider channel0DecibelSlider;
    Label channel0DecibelLabel;

    Slider channel1GainSlider;
    Label channel1GainLabel;
    DecibelSlider channel1DecibelSlider;
    Label channel1DecibelLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)

    void addSlider(const String &labelText, Slider &slider, Label &label);

    void synchronizeSliders();

    void initializeSliderValues();
};
