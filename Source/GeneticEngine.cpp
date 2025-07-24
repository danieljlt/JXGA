/*
  ==============================================================================

    GeneticEngine.cpp
    Created: 10 Jul 2025 12:20:04pm
    Author:  Daniel Lister

  ==============================================================================
*/

#include "GeneticEngine.h"

GeneticEngine::GeneticEngine()
{
    
}

// Begin the genetic algorithm
void GeneticEngine::start()
{
    // Retreive features from target audio sample
    GenomeProcessor targetProcessor;
    Individual target;
    PerceptualFeatures targetFeatures;
    targetFeatures = targetProcessor.returnFeaturesFromGenome(target.normalizedParams);
    
    // Evaluate a given individual (caclculate fitness from set of params)
    GenomeProcessor candidateProcessor;
    Individual individual;
    individual.fitness = candidateProcessor.returnFitnessFromGenome(individual.normalizedParams, targetFeatures);
    
    DBG("Fitness: " + juce::String(individual.fitness));
}
