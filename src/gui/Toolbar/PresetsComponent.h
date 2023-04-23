#pragma once

#include <pch.h>
#include "gui/Shared/Fonts.h"

namespace gui::presets
{
class PresetsComponent : public chowdsp::presets::PresetsComponent
{
public:
    PresetsComponent (chowdsp::presets::PresetManager& presetManager, chowdsp::presets::frontend::FileInterface& fileInterface);

private:
    SharedFonts fonts;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsComponent)
};
}
