/*
  ==============================================================================

    Individual.h
    Created: 9 Jul 2025 11:48:53am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once
#include <thread>


class Individual
{
    public:
    Individual();
    Individual(std::array<float, 23> paramValues);
    
    const std::array<float, 23>& getParams() const { return normalizedParams; };
    
    float fitness;
    
    private:
    std::array<float, 23> normalizedParams;
};
