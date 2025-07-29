/*
  ==============================================================================

    ParameterFifo.cpp
    Created: 29 Jul 2025 11:13:33am
    Author:  Daniel Lister

  ==============================================================================
*/

#include "ParameterFifo.h"

ParameterFifo::ParameterFifo(int capacity) : abstractFifo(capacity), storage(capacity)
{
    
}

bool ParameterFifo::push(const std::array<float, 23> &params)
{
    //std::cout << params[0];
    auto writeScope = abstractFifo.write(1);
    if (writeScope.blockSize1 > 0)
    {
        storage[writeScope.startIndex1] = params;
        return true;
    }
    return false;
}

bool ParameterFifo::pop(std::array<float, 23> &params)
{
    auto readScope = abstractFifo.read(1);
    if (readScope.blockSize1 > 0)
    {
        params = storage[readScope.startIndex1];
        return true;
    }
    return false;
}

