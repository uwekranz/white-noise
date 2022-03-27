#include <JuceHeader.h>
#include "DecibelSlider.h"

juce::String DecibelSlider::getTextFromValue(double value) {
    return juce::Decibels::toString(value);
}

double DecibelSlider::getValueFromText(const juce::String &text) {
    auto minusInfinitydB = -100.0;

    auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();

    return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB : decibelText.getDoubleValue();
}
