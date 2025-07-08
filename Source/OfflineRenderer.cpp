/*
  ==============================================================================

    OfflineRenderer.cpp
    Created: 6 Jul 2025 11:33:56am
    Author:  Daniel Lister

  ==============================================================================
*/

#include "OfflineRenderer.h"


OfflineRenderer::OfflineRenderer()
{
    
}


OfflineRenderer::~OfflineRenderer()
{
    if (backgroundRenderThread.joinable())
    {
        backgroundRenderThread.join();
    }
}


// Gets called when "Render Test" button is pressed on the UI
// Starts a background thread for the rendering to take place on
void OfflineRenderer::renderCallAsync()
{
    // Check if already rendering
    if (isRendering.load())
    {
        DBG("Rendering already in progress...");
        return;
    }
    
    // Join previous thread if it exists
    if (backgroundRenderThread.joinable())
    {
        backgroundRenderThread.join();
    }
    
    // Start new background thread
    backgroundRenderThread = std::thread([this]() {
        isRendering.store(true);
        
        try
        {
            coreRendering(); // Call the main render function
            DBG("Background rendering completed successfully");
        }
        catch (const std::exception& e)
        {
            DBG("Error during background rendering: " + juce::String(e.what()));
        }
        catch (...)
        {
            DBG("Unknown error during background rendering");
        }
        
        isRendering.store(false);
    });
}


// Main logic that calls process block in a loop
void OfflineRenderer::coreRendering()
{
    DBG("Starting offline render...");
    
    const int sampleRate = 44100;
    const int lengthInSamples = 5 * sampleRate; // 5 seconds
    
    const int blockSize = 4096;
    const int noteOnSample = 0;
    const int noteOffSample = 3 * sampleRate; // 3 seconds
    const int midiNote = 60; // Middle C
    const int velocity = 80;
    
    bool noteTriggered = false;
    bool noteReleased = false;
    
    // Create output buffer
    juce::AudioBuffer<float> outputBuffer(2, lengthInSamples);
    outputBuffer.clear();
    
    // Allocate resources to audio processor
    processor.setNonRealtime(true);
    processor.prepareToPlay(sampleRate, blockSize);
    processor.setCurrentProgram(1);
    
    // Process audio in blocks
    for (int currentSample = 0; currentSample < lengthInSamples; currentSample += blockSize)
    {
        int samplesThisBlock = std::min(blockSize, lengthInSamples - currentSample);
        juce::AudioBuffer<float> audioBlock(2, samplesThisBlock);
        audioBlock.clear();
        juce::MidiBuffer midiBlock;
        midiBlock.clear();
        
        // Trigger note on at the beginning
        if (!noteTriggered && currentSample >= noteOnSample)
        {
            // Send MIDI Note On
            midiBlock.addEvent(juce::MidiMessage::noteOn(1, midiNote, (juce::uint8)velocity), 0);
            noteTriggered = true;
            DBG("Note ON triggered at sample: " + juce::String(currentSample));
        }
        
        // Trigger note off at 3 seconds
        if (!noteReleased && currentSample >= noteOffSample)
        {
            // Send MIDI Note Off
            midiBlock.addEvent(juce::MidiMessage::noteOff(1, midiNote), noteOffSample - currentSample);
            noteReleased = true;
            DBG("Note OFF triggered at sample: " + juce::String(currentSample));
        }
        
        // Render this block
        processor.processBlock(audioBlock, midiBlock);
        
        // Copy intermediary block's data over to full output buffer
        for (int ch = 0; ch < 2; ++ch)
            outputBuffer.copyFrom(ch, currentSample, audioBlock, ch, 0, samplesThisBlock);
    }
    
    processor.releaseResources();
    
    DBG("Rendering complete!");
    printBufferStats(outputBuffer);
    
    // Save to file
    saveBufferToWav(outputBuffer, sampleRate, "rendered_test.wav");
}

// Helper function to save an audio buffer to a wav file on my desktop
void OfflineRenderer::saveBufferToWav(const juce::AudioBuffer<float>& buffer, int sampleRate, const juce::String& filename)
{
    // Get the desktop directory
    juce::File desktopDir = juce::File::getSpecialLocation(juce::File::userDesktopDirectory);
    juce::File file = desktopDir.getChildFile(filename);
    
    // Delete existing file if it exists
    if (file.exists())
        file.deleteFile();
    
    juce::WavAudioFormat format;
    std::unique_ptr<juce::AudioFormatWriter> writer;

    writer.reset(format.createWriterFor(new juce::FileOutputStream(file),
      sampleRate,
      buffer.getNumChannels(),
      24, // Bit depth
      {}, // Metadata
      0 // Quality Option
    ));

    if (writer != nullptr)
      writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());;
    
    DBG("Audio saved to: " + file.getFullPathName());
}


// Helper function to check for silence and print buffer stats
void OfflineRenderer::printBufferStats(const juce::AudioBuffer<float>& buffer)
{
    float maxPeak = 0.0f;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        // getMagnitude is a JUCE function that finds the max absolute value in a range.
        float peak = buffer.getMagnitude(channel, 0, buffer.getNumSamples());
        if (peak > maxPeak)
        {
            maxPeak = peak;
        }
    }
    
    // DBG is JUCE's macro for printing to the debug console.
    DBG("Buffer analysis complete. Max peak level: " + juce::String(maxPeak));

    if (maxPeak == 0.0f)
    {
        DBG("CONCLUSION: The buffer is completely silent.");
    }
    else
    {
        DBG("CONCLUSION: The buffer contains audio data.");
    }
}
