#pragma once

#include <pch.h>

namespace gui::lnf
{
class MenuLNF : public chowdsp::ChowLNF
{
public:
    MenuLNF();

    void drawPopupMenuItem (juce::Graphics& g,
                            const juce::Rectangle<int>& area,
                            const bool isSeparator,
                            const bool isActive,
                            const bool isHighlighted,
                            const bool /*isTicked*/,
                            const bool hasSubMenu,
                            const juce::String& text,
                            const juce::String& shortcutKeyText,
                            const juce::Drawable* icon,
                            const juce::Colour* const textColourToUse) override;
    void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override;
};
} // namespace gui::lnf
