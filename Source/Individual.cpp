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
    std::array<float, 23> paramValues = {
        0.00f, 0.25f, 0.5f, 0.00f, 0.35f, 0.5f,
        1.00f, 0.15f, 0.75f, 0.00f, 0.5f, 0.00f,
        0.3f, 0.00f, 0.25f, 0.00f, 0.5f, 1.0f,
        0.3f, 0.81f, 0.5f, 0.00f, 0.5f
    };
    
    normalizedParams = paramValues;
    fitness = -1.0f;
}

Individual::Individual(std::array<float, 23> paramValues)
{
    normalizedParams = paramValues;
    fitness = -1.0f;
}
