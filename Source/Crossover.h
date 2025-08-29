/*
  ==============================================================================

    Crossover.h
    Created: 27 Aug 2025 1:32:47pm
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once

#include "Individual.h"

class Crossover
{
    public:
    Crossover();
    std::array<float, 23> arithmeticCrossover(const Individual& ind1, const Individual& ind2) const;
    
    private:
    
    
};
