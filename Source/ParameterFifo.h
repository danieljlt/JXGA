/*
  ==============================================================================

    ParameterFifo.h
    Created: 29 Jul 2025 11:13:32am
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ParameterFifo
{
    public:
    explicit ParameterFifo(int capacity); // capacity = number of parameter sets the fifo can store
    
    // Producer method
    bool push(const std::array<float, 23>& params);
    
    // Consumer method
    bool pop(std::array<float, 23>& params);
    
    // utility methods
    int getFreeSpace() const { return abstractFifo.getFreeSpace(); }
    int getNumReady() const { return abstractFifo.getNumReady(); }
    bool isEmpty() const { return abstractFifo.getNumReady() == 0; }
    bool isFull() const { return abstractFifo.getFreeSpace() == 0; }
    
    private:
    juce::AbstractFifo abstractFifo;
    std::vector<std::array<float, 23>> storage;
};
