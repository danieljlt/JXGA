/*
  ==============================================================================

    OfflineRenderer.h
    Created: 6 Jul 2025 11:33:56am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include "PluginProcessor.h"

class OfflineRenderer
{
    public:
    OfflineRenderer();
    
    const float* coreRendering(const std::array<float, 23> normalisedParams, const int& sampleRate, const int& totalSamples, bool saveFile = false);
    
    void saveBufferToWav(const juce::AudioBuffer<float>& buffer, int sampleRate, const juce::String& filename);
    
    private:
    std::atomic<bool> isRendering{false};
    JX11AudioProcessor processor;

    void printBufferStats(const juce::AudioBuffer<float>& buffer);
};
