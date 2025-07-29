/*
  ==============================================================================

    GeneticEngine.h
    Created: 10 Jul 2025 12:20:04pm
    Author:  Daniel Lister

    Where main evolutionary algorithm loop is run
  ==============================================================================
*/

#pragma once
#include "Individual.h"
#include "GenomeProcessor.h"
#include "PerceptualFeatures.h"
#include "Population.h"
#include "ParameterFifo.h"

class GeneticEngine
{
    public:
    GeneticEngine();
    explicit GeneticEngine(JX11AudioProcessor* mainProcessor);
    
    void start(ParameterFifo& parameterFifo);
    
    private:
    const Individual& basicEvolutionaryLoop();
    JX11AudioProcessor* mainInstance;
};
