/*
  ==============================================================================

    Population.cpp
    Created: 25 Jul 2025 1:43:46pm
    Author:  Daniel Lister

  ==============================================================================
*/

#include "Population.h"

void Population::randInit()
{
    for (size_t i = 0; i < popSize; i++)
    {
        std::array<float, 23> randParams;
        for (float& val: randParams)
        {
            val = dist(gen);
        }
        
        members.emplace_back(randParams);
    }
}

void Population::sortByFitness(bool ascending)
{
    std::sort(members.begin(), members.end(), [ascending](const Individual& a, const Individual& b)
    {
        return ascending ? (a.fitness < b.fitness) : (a.fitness > b.fitness);
    });
}

void Population::printStatistics()
{
    std::cout << "Fitness values of population:\n";
    for (size_t i = 0; i < members.size(); ++i)
    {
        std::cout << "Individual " << i << ": " << members.at(i).fitness << "\n";
    }
}
