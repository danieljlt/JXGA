/*
  ==============================================================================

    FitnessEvaluator.h
    Created: 15 Jul 2025 11:27:13am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once

#include "PerceptualFeatures.h"

class FitnessEvaluator
{
    public:
    
    float evaluateFitness(const PerceptualFeatures& candidateFeatures, const PerceptualFeatures& targetFeatures);
    
    private:
    
    float mfccSimilarity(const std::vector<std::vector<float>>& candidateMFCC, const std::vector<std::vector<float>>& targetMFCC);
    float cosineSimilarity(const std::vector<float>& a, const std::vector<float>& b);
    
};
