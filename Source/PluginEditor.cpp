/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JX11AudioProcessorEditor::JX11AudioProcessorEditor (JX11AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(startGAButton);
    startGAButton.onClick = [this]()
    {
        startGAButton.setEnabled(false);
        startGAButton.setButtonText("Running");
        
        audioProcessor.startGa();
        
        audioProcessor.onGAComplete = [this]()
        {
            startGAButton.setEnabled(true);
            startGAButton.setButtonText("Run GA");
        };
    };
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

JX11AudioProcessorEditor::~JX11AudioProcessorEditor()
{
}

//==============================================================================
void JX11AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void JX11AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    startGAButton.setBounds(10, 10, 120, 30);
}
