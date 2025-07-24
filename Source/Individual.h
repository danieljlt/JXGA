/*
  ==============================================================================

    Individual.h
    Created: 9 Jul 2025 11:48:53am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once
#include "thread"

class Individual
{
    public:
    Individual();
    Individual(float paramValues[23]);
    
    void setAllParameters(float paramsValues[23]);
    
    float normalizedParams[23];
    
    float fitness;
    
    private:
};
