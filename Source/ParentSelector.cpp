/*
  ==============================================================================

    ParentSelector.cpp
    Created: 5 Aug 2025 12:09:47pm
    Author:  Daniel Lister

  ==============================================================================
*/

#include "ParentSelector.h"

ParentSelector::ParentSelector() : ParentSelector(3)  // Delegate to parameterized constructor
{
}

ParentSelector::ParentSelector(int tournamentSize)
    : tournamentSize(tournamentSize), gen(std::random_device{}())
{
}

// Create mating pool and return pairs in one step
std::vector<std::pair<size_t, size_t>> ParentSelector::createMatingPairs( const Population& population, size_t numPairs)
{
    const size_t popSize = population.size();
    if (popSize < 2)
        return {};
    
    std::vector<size_t> matingPool = createMatingPool(population, numPairs * 2);
    if (matingPool.size() < 2) return {};

    std::vector<std::pair<size_t, size_t>> pairs;
    pairs.reserve(numPairs);
    
    std::shuffle(matingPool.begin(), matingPool.end(), gen);
    
    for (size_t i = 0; (i + 1) < matingPool.size(); i += 2)
    {
        size_t a = matingPool[i];
        size_t b = matingPool[i + 1];
        
        // Ensure self-mating is not allowed
        if (a == b)
        {
            // Try to swap b with a later element != a
            for (size_t k = i + 2; k < matingPool.size(); ++k)
            {
                if (matingPool[k] != a)
                {
                    std::swap(matingPool[i + 1], matingPool[k]);
                    b = matingPool[i + 1];
                    break;
                }
            }
        }

        pairs.emplace_back(a, b);
    }

    return pairs;
}


// Returns vector of indices representing mating pool
std::vector<size_t> ParentSelector::createMatingPool(const Population& population, size_t poolSize)
{
    std::vector<size_t> matingPool;
    matingPool.reserve(poolSize);

    for (size_t i = 0; i < poolSize; ++i)
    {
        matingPool.push_back(tournamentSelect(population));
    }
    
    return matingPool;
}

// Perform a single tournament selection
size_t ParentSelector::tournamentSelect(const Population& population)
{
    const size_t popSize = population.size();
    std::uniform_int_distribution<size_t> dist(0, popSize - 1);
    
    const size_t tSizeClamped = std::max<size_t>(1, std::min(tournamentSize, popSize));
    
    // Initialize with random candidate
    size_t bestIndex = dist(gen);
    float bestFitness = population.getIndividual(bestIndex).fitness;

    for (size_t i = 1; i < tSizeClamped; ++i)
    {
        size_t candidateIndex = dist(gen);
        const Individual& candidate = population.getIndividual(candidateIndex);

        // Check if the current candidate is fitter than the best one found so far
        if (candidate.fitness > bestFitness)
        {
            bestFitness = candidate.fitness;
            bestIndex = candidateIndex;
        }
    }
    return bestIndex;
}
