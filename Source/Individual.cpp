/*
  ==============================================================================

    Individual.cpp
    Created: 9 Jul 2025 11:48:53am
    Author:  Daniel Lister

  ==============================================================================
*/

#include "Individual.h"

Individual::Individual()
{
    float paramValues[23] = {
        0.00f, 0.25f, 0.5f, 0.00f, 0.35f, 0.5f,
        1.00f, 0.15f, 0.75f, 0.00f, 0.5f, 0.00f,
        0.3f, 0.00f, 0.25f, 0.00f, 0.5f, 1.0f,
        0.3f, 0.81f, 0.5f, 0.00f, 0.5f
    };
    
    std::memcpy(normalizedParams, paramValues, sizeof(float) * 23);
}

Individual::Individual(float paramValues[23])
{
    std::memcpy(normalizedParams, paramValues, sizeof(float) * 23);
}

void Individual::setAllParameters(float paramValues[23])
{
    std::memcpy(normalizedParams, paramValues, sizeof(float) * 23);
}
