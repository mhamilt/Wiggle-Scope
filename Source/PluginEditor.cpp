/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WiggleScopeAudioProcessorEditor::WiggleScopeAudioProcessorEditor (WiggleScopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    scope.setup(audioProcessor.getLatestBuffer(), audioProcessor.getSampleRate());
    scope.setEnabled(true);
    scope.setBounds(0, 0, 400, 300);
    addAndMakeVisible(scope);
    
    numSampsToDraw.setEnabled(true);
    numSampsToDraw.setBounds(getWidth() - 210, getHeight() - 40, 200, 20);
    numSampsToDraw.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox,
                                   true, 0, 0);
    numSampsToDraw.setRange(63, scope.getMaxNumSamplesToDraw());
    numSampsToDraw.addListener(this);
    addAndMakeVisible(numSampsToDraw);
    
    refreshRate.setEnabled(true);
    refreshRate.setBounds(getWidth() - 210, getHeight() - 80, 200, 20);
    refreshRate.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox,
                                   true, 0, 0);
    refreshRate.setRange(20, 100);
    refreshRate.addListener(this);
    addAndMakeVisible(refreshRate);
}

WiggleScopeAudioProcessorEditor::~WiggleScopeAudioProcessorEditor()
{
}

//==============================================================================
void WiggleScopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void WiggleScopeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void WiggleScopeAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    
    if      (slider == &numSampsToDraw)
    {
        scope.setNumSamplesToDraw((unsigned int) slider->getValue());
    }
    else if (slider == &refreshRate)
    {     
        scope.setRefreshRate(slider->getValue());
    }
    
}
