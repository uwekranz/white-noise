#include <JuceHeader.h>
#include "DecibelSlider.h"
#include "DecibelConfig.h"

juce::String DecibelSlider::getTextFromValue(double value) {
    return juce::Decibels::toString(
            value,
            2,
            (double) DecibelConfig::minusInfinityDb,
            false,
            DecibelConfig::customMinusInfinityString);
}

double DecibelSlider::getValueFromText(const juce::String &text) {
    auto decibelText = text.upToFirstOccurrenceOf(
                    "dB",
                    false,
                    false)
            .trim();

    return decibelText.equalsIgnoreCase(DecibelConfig::customMinusInfinityString)
           ? DecibelConfig::minusInfinityDb
           : decibelText.getDoubleValue();
}
