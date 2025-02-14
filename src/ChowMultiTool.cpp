#include "ChowMultiTool.h"
#include "gui/PluginEditor.h"
#include "state/PresetManager.h"

namespace
{
const juce::String settingsFilePath = "ChowdhuryDSP/ChowMultiTool/.plugin_settings.json";
const juce::String logFileSubDir = "ChowdhuryDSP/ChowMultiTool/Logs";
const juce::String logFileNameRoot = "ChowMultiTool_Log_";
} // namespace

ChowMultiTool::ChowMultiTool() : chowdsp::PluginBase<State> (&undoManager, createBusLayout()),
                                 logger (logFileSubDir, logFileNameRoot)
{
    juce::Logger::writeToLog (chowdsp::PluginDiagnosticInfo::getDiagnosticsString (*this));
    pluginSettings->initialise (settingsFilePath);

    presetManager = std::make_unique<state::presets::PresetManager> (*this);
    programAdaptor = std::make_unique<chowdsp::presets::frontend::PresetsProgramAdapter> (presetManager);
}

juce::AudioProcessor::BusesProperties ChowMultiTool::createBusLayout()
{
    return BusesProperties()
        .withInput ("Main", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Main", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Band-Split (Low)", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Band-Split (Mid)", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Band-Split (High)", juce::AudioChannelSet::stereo(), true);
}

bool ChowMultiTool::isBusesLayoutSupported (const BusesLayout& layout) const
{
    const auto mainInputLayout = layout.getMainInputChannelSet();
    if (mainInputLayout.isDisabled() || mainInputLayout.isDiscreteLayout())
        return false;

    for (const auto& bus : layout.outputBuses)
    {
        if (bus.isDiscreteLayout() || bus.isDisabled())
            return false;
    }

    return true;
}

void ChowMultiTool::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    processor.prepare ({ sampleRate, (uint32_t) samplesPerBlock, (uint32_t) getMainBusNumInputChannels() });
}

void ChowMultiTool::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
{
    juce::ScopedNoDenormals noDenormals;

    state.getParameterListeners().callAudioThreadBroadcasters();

    processor.processBlock (buffer, midiBuffer);

    chowdsp::BufferMath::sanitizeBuffer (buffer);
}

juce::AudioProcessorEditor* ChowMultiTool::createEditor()
{
    return new gui::PluginEditor { *this };
}

#if ! JUCE_IOS
bool ChowMultiTool::remoteControlsPageFill (uint32_t pageIndex,
                                            juce::String& sectionName,
                                            uint32_t& pageID,
                                            juce::String& pageName,
                                            std::array<juce::AudioProcessorParameter*, CLAP_REMOTE_CONTROLS_COUNT>& params) noexcept
{
    remoteControls.pageFill (pageIndex, sectionName, pageID, pageName, params);
    return true;
}
#endif

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChowMultiTool();
}
