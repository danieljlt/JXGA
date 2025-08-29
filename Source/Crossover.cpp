/*
  ==============================================================================

    Crossover.cpp
    Created: 27 Aug 2025 1:32:47pm
    Author:  Daniel Lister

  ==============================================================================
*/

#include "Crossover.h"

std::array<float, 23> Crossover::arithmeticCrossover(const Individual &ind1, const Individual &ind2) const
{
    std::array<float, 23> child;
    const std::array<float, 23>& p1 = ind1.getParams();
    const std::array<float, 23>& p2 = ind2.getParams();
    
    for (size_t i = 0; i < child.size(); ++i)
        child[i] = 0.5f * (p1[i] + p2[i]);

    return child;
}
