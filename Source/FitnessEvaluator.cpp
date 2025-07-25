/*
  ==============================================================================

    FitnessEvaluator.cpp
    Created: 15 Jul 2025 11:27:13am
    Author:  Daniel Lister

  ==============================================================================
*/

#include "FitnessEvaluator.h"

// Calculates simiiarity between given candidate and target features
float FitnessEvaluator::evaluateFitness(const PerceptualFeatures& candidateFeatures, const PerceptualFeatures& targetFeatures)
{
    float totalSimilarity = 0.0f;
    const int numOfObjectives = 1;
    
    totalSimilarity += mfccSimilarity(candidateFeatures.mfccFrames, targetFeatures.mfccFrames);
            
    totalSimilarity /= numOfObjectives;  // Average similarity across all frames
    
    return (totalSimilarity + 1.0f) / 2.0f; // return normalized similarity
}

// Calculates the similarity between two mfcc vectors
float FitnessEvaluator::mfccSimilarity(const std::vector<std::vector<float>>& candidateMFCC, const std::vector<std::vector<float>>& targetMFCC)
{
    float similarity = 0.0f;
    const size_t numFrames = std::min(candidateMFCC.size(), targetMFCC.size());
    
    // Goes through each frame and calculates the cosine similarity between them
    for (size_t frame = 0; frame < numFrames; frame++)
    {
        similarity += cosineSimilarity(candidateMFCC[frame], targetMFCC[frame]);
    }
    
    return similarity / static_cast<float>(numFrames);
}

// Calculates the consine similarity between two vectors of floats
float FitnessEvaluator::cosineSimilarity(const std::vector<float>& a, const std::vector<float>& b)
{
    if (a.size() != b.size()) return 0.0f;
            
    float dotProduct = 0.0f;
    float normA = 0.0f;
    float normB = 0.0f;
    
    for (size_t i = 0; i < a.size(); i++) {
        const float valA = a[i];
        const float valB = b[i];
        
        dotProduct += valA * valB;
        normA += valA * valA;
        normB += valB * valB;
    }
    
    if (normA == 0.0f || normB == 0.0f) return 0.0f;
    
    return dotProduct / std::sqrt(normA * normB);
}
