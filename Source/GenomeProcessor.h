/*
  ==============================================================================

    GenomeProcessor.h
    Created: 11 Jul 2025 1:26:36pm
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once
#include "OfflineRenderer.h"
#include "FeatureExtractor.h"
#include "FitnessEvaluator.h"
#include "PerceptualFeatures.h"

class GenomeProcessor
{
    public:
    // Function that for a given genome (parameter set), renders audio into buffer, extracts features, evaluates and returns a fitness score
    // IDEA: could use this class to setup multiple evaluation pipelines, each might use a different fitness evaluation or feature extraction function
    // so the goal of the genome processor is to have multiple options that can the engine can call
    float returnFitnessFromGenome(const std::array<float, 23> normalizedParams, const PerceptualFeatures targetFeatures, int totalSamples);
    
    // Used for getting set of features for the target audio sample
    PerceptualFeatures returnFeaturesFromGenome(const std::array<float, 23> normalizedParams, int totalSamples);
    
    // used for debugging
    void paramsToWav(const std::array<float, 23> normalizedParams, int totalSamples);
    
    private:
};
