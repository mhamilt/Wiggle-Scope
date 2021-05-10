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
    setSize (500, 300);
    
    scope.setup(audioProcessor.getLatestBuffer(), audioProcessor.getSampleRate());
    scope.setEnabled(true);
    addAndMakeVisible(scope);
    
    numSampsToDraw.setEnabled(true);
    numSampsToDraw.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox,
                                   true, 0, 0);
    numSampsToDraw.setRange(63, scope.getMaxNumSamplesToDraw());
    numSampsToDraw.addListener(this);
    addAndMakeVisible(numSampsToDraw);
    
    refreshRate.setEnabled(true);
    
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
    g.fillAll (juce::Colour(0xFF252525));
}

void WiggleScopeAudioProcessorEditor::resized()
{
    scope.setBounds(0, 0, 400, 300);
    numSampsToDraw.setBounds(getWidth() - 95, 40, 90, 20);
    refreshRate.setBounds(getWidth() - 95, 80, 90, 20);
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
