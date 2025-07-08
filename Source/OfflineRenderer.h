/*
  ==============================================================================

    OfflineRenderer.h
    Created: 6 Jul 2025 11:33:56am
    Author:  Daniel Lister

  ==============================================================================
*/
#include <juce_core/juce_core.h>
#include "PluginProcessor.h"
#include <juce_audio_formats/juce_audio_formats.h>

#pragma once

class OfflineRenderer
{
    public:
    OfflineRenderer();
    ~OfflineRenderer(); // Add a destructor
    
    void renderCallAsync();
    
    private:
    std::thread backgroundRenderThread;
    std::atomic<bool> isRendering{false};
    JX11AudioProcessor processor;
    
    void coreRendering();
    void saveBufferToWav(const juce::AudioBuffer<float>& buffer, int sampleRate, const juce::String& filename);
    void printBufferStats(const juce::AudioBuffer<float>& buffer);
};
