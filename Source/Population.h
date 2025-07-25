/*
  ==============================================================================

    Population.h
    Created: 25 Jul 2025 1:43:46pm
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>
#include "Individual.h"

class Population
{
    public:
    Population() : gen(std::random_device{}()), dist(0.0f, 1.0f) { randInit(10); };
    Population(size_t popSize) : gen(std::random_device{}()), dist(0.0f, 1.0f) { randInit(popSize); };
    
    // Randomly initialize a population of individuals
    void randInit(size_t popSize);
    
    const std::vector<Individual>& getMembers() const { return members; }
    
    // When accessing individual for read only purposes (i.e parents during crossover and mutation)
    const Individual& getIndividual(size_t index) const { return members.at(index); };
    
    // When accessing individual with read and write purposes (when setting fitness)
    Individual& getIndividual(size_t index) { return members.at(index); };
    
    void addIndividual(const Individual& ind) { members.push_back(ind); }
    void clear() { members.clear(); }
    size_t size() const { return members.size(); }
    
    void sortByFitness(bool ascending = false);
    
    // Iterator support
    auto begin() { return members.begin(); }
    auto end() { return members.end(); }
    
    void printStatistics();
    
    private:
    std::vector<Individual> members;
    
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;
};
