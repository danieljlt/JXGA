/*
  ==============================================================================

    GenomeProcessor.cpp
    Created: 11 Jul 2025 1:26:36pm
    Author:  Daniel Lister

  ==============================================================================
*/

#include "GenomeProcessor.h"

// Return fitness of given set of parameteres compared to target features
float GenomeProcessor::returnFitnessFromGenome(const std::array<float, 23> normalizedParams, const PerceptualFeatures targetFeatures, int length)
{
    PerceptualFeatures candidateFeatures;
    FitnessEvaluator fitnessEvaluator;
    
    // Render audio, extract features, and evaluate fitness
    candidateFeatures = returnFeaturesFromGenome(normalizedParams, length);
    float fitness = fitnessEvaluator.evaluateFitness(candidateFeatures, targetFeatures);

    return fitness;
}

// Return set of features given a set of parameters
PerceptualFeatures GenomeProcessor::returnFeaturesFromGenome(const std::array<float, 23> normalizedParams, int length)
{
    int sampleRate = 44100;
    int totalSamples = length * sampleRate;
    PerceptualFeatures candidateFeatures;
    OfflineRenderer offlineRenderer;
    FeatureExtractor featureExtractor;
    
    
    // Render audio, extract features
    const float* audioOutput = offlineRenderer.coreRendering(normalizedParams, sampleRate, totalSamples);
    featureExtractor.extractFeatures(candidateFeatures, audioOutput, sampleRate, totalSamples);

    return candidateFeatures;
}

