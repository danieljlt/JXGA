/*
  ==============================================================================

    FeatureExtractor.h
    Created: 15 Jul 2025 11:26:56am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once
#include "Gist.h"
#include "PerceptualFeatures.h"

class FeatureExtractor
{
    public:
    void extractFeatures(PerceptualFeatures& features, const float* audioOutput, const int& sampleRate, const int& totalSamples);
    
    private:
};
