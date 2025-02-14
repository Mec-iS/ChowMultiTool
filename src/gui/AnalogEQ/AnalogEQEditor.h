#pragma once

#include "AnalogEQPlot.h"

namespace gui::analog_eq
{
class AnalogEQEditor : public juce::Component
{
public:
    AnalogEQEditor (State& pluginState, dsp::analog_eq::Params& params, const chowdsp::HostContextProvider& hcp);

    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    AnalogEQPlot plot;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalogEQEditor)
};
} // namespace gui::analog_eq
