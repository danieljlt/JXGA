/*
  ==============================================================================

    PerceptualFeatures.h
    Created: 18 Jul 2025 12:06:50pm
    Author:  Daniel Lister

  ==============================================================================
*/

#pragma once

#include <vector>

struct PerceptualFeatures
{
    std::vector<std::vector<float>> mfccFrames;
    std::vector<float> rmsValues;
};
