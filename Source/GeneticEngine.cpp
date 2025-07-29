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

GeneticEngine::GeneticEngine(JX11AudioProcessor* mainProcessor) : mainInstance(mainProcessor)
{
    
}

// Choose which genetic algorithm to run and with what parameters
void GeneticEngine::start(ParameterFifo& parameterFifo)
{
    // Here is where I would check the arguments I passed in from the UI
    // I would then be able to call the appropriate type of evolutionary algorithm.
    // Right now I just have a basic evolutionary algorithm so I can only choose that.
    Individual fittest = basicEvolutionaryLoop();
    //std::cout << fittest.getParams()[0] << std::endl;
    bool push = parameterFifo.push(fittest.getParams());
}


// Basic Genetic Algorithm that returns fittest individual
const Individual& GeneticEngine::basicEvolutionaryLoop()
{
    // Retreive features from target audio sample
    GenomeProcessor targetProcessor;
    Individual target;
    int targetLength = 4;
    PerceptualFeatures targetFeatures;
    targetFeatures = targetProcessor.returnFeaturesFromGenome(target.getParams(), targetLength);
    
    GenomeProcessor candidateProcessor;
    Population population(10);
    
    // Loop through population and evaluate fitness
    for (Individual& individual : population)
    {
        // Negative fitness indicates that said individual has not be evaluated yet
        if (individual.fitness < 0.0f)
        {
            individual.fitness = candidateProcessor.returnFitnessFromGenome(individual.getParams(), targetFeatures, targetLength);
        }
    }
    population.sortByFitness();
    //population.printStatistics();
    return population.getIndividual(0);
}
