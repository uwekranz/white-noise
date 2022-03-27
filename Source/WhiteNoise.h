#pragma once

class MainContentComponent: public AudioAppComponent
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
            float level = 0;
            float levelScale = 0;

            if (channel == 0)
            {
                level = (float) channel0LevelSlider.getValue();
                levelScale = level * 2;
            }
            if (channel == 1)
            {
                level = (float) channel1LevelSlider.getValue();
                levelScale = level * 2;
            }

            auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            {
                buffer[sample] = random.nextFloat() * levelScale - level;
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
