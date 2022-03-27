#pragma once

class DecibelSlider : public Slider {
public:
    String getTextFromValue(double value) override;

    double getValueFromText(const String &text) override;
};