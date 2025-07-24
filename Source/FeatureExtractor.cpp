/*
  ==============================================================================

    FeatureExtractor.cpp
    Created: 15 Jul 2025 11:26:56am
    Author:  Daniel Lister

  ==============================================================================
*/

#include "FeatureExtractor.h"

// Extract perceptual features from a given audio buffer(passed as an array)
void FeatureExtractor::extractFeatures(PerceptualFeatures& features, const float *audioOutput, const int& sampleRate, const int& totalSamples)
{
    int frameSize = 1024;
    int hopSize = frameSize / 2;    // 50% overlap between frames
    Gist<float> gist (frameSize, sampleRate);
    
    // Go through each frame(1024 samples) and calculate feature values
    for (int i = 0; i <= totalSamples - frameSize; i += hopSize)
    {
        int samplesThisFrame = std::min(frameSize, totalSamples - i);
        gist.processAudioFrame(&audioOutput[i], samplesThisFrame);
        features.rmsValues.push_back(gist.rootMeanSquare());
        features.mfccFrames.push_back(gist.getMelFrequencyCepstralCoefficients());
    }
}
