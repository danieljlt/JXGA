/*
  ==============================================================================

    ParentSelector.h
    Created: 5 Aug 2025 12:09:47pm
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once
#include <vector>
#include <random>
#include <utility>
#include "Individual.h"
#include "Population.h"

class ParentSelector
{
    public:
    ParentSelector();
    ParentSelector(int tournamentSize);
    
    // Create mating pool and return pairs in one step
    std::vector<std::pair<size_t, size_t>> createMatingPairs( const Population& population, size_t numPairs);
    
    void setTournamentSize(int size) { tournamentSize = size; }
    
    private:
    
    size_t tournamentSize = 3;
        
    // Random number generation
    std::random_device rd;
    std::mt19937 gen;
    
    // Returns vector of indices representing mating pool
    std::vector<size_t> createMatingPool(const Population& population, size_t poolSize);
    
    // Perform a single tournament selection
    size_t tournamentSelect(const Population& population);
    
};
