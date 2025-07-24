/*
  ==============================================================================

    OfflineRenderer.h
    Created: 6 Jul 2025 11:33:56am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>
#include "PluginProcessor.h"
#include <juce_audio_formats/juce_audio_formats.h>
#include "Individual.h"

class OfflineRenderer
{
    public:
    OfflineRenderer();
    ~OfflineRenderer();
    
    const float* coreRendering(const float normalisedParams[23], const int& sampleRate, const int& totalSamples);
    
    void saveBufferToWav(const juce::AudioBuffer<float>& buffer, int sampleRate, const juce::String& filename);
    
    private:
    std::atomic<bool> isRendering{false};
    JX11AudioProcessor processor;

    void printBufferStats(const juce::AudioBuffer<float>& buffer);
};
