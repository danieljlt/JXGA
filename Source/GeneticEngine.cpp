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
    
    basicEvolutionaryLoop(parameterFifo);
}


// Basic Genetic Algorithm
void GeneticEngine::basicEvolutionaryLoop(ParameterFifo& parameterFifo)
{
    // Retreive features from target audio sample
    GenomeProcessor targetProcessor;
    Individual target;
    int targetLength = 4 * 44100;
    PerceptualFeatures targetFeatures;
    targetFeatures = targetProcessor.returnFeaturesFromGenome(target.getParams(), targetLength);
    GenomeProcessor candidateProcessor;
    
    // Create intial population
    size_t popSize = 10;
    Population population(popSize);
    population.randInit();
    
    int generations = 1;
    Individual bestIndividual;
    
    // EA loop runs until enough generations have passed
    for (int generation = 0; generation < generations; generation++)
    {
        // Loop through population and evaluate fitness
        for (Individual& individual : population)
        {
            // Negative fitness indicates that said individual has not be evaluated yet
            if (individual.fitness < 0.0f)
            {
                individual.fitness = candidateProcessor.returnFitnessFromGenome(individual.getParams(), targetFeatures, targetLength);
            }
        }
        
        // Track best individual
        Individual currentBest = *std::max_element(population.begin(), population.end(),
            [](const Individual& a, const Individual& b) { return a.fitness < b.fitness; });

        if (generation == 0 || currentBest.fitness > bestIndividual.fitness) {
            bestIndividual = currentBest;
        }
        
        // Parent selection (create list of pairs to mate)
        std::vector<std::pair<size_t, size_t>> matingPairs = parentSelector.createMatingPairs(population, popSize / 2);
        
        // Loop through pairs to create offspring
        for (const auto& pair : matingPairs)
        {
            DBG(juce::String::formatted("(%zu, %zu)", pair.first, pair.second));
            
            // if crossover rate is sufficient apply crossover
            // else copy parent
            
            // if mutation rate is sufficient apply mutation
            
            // add offspring to new list
        }
        
        // replace bottom x individuals from population with the offspring
        
    }
    
    parameterFifo.push(bestIndividual.getParams());
}
