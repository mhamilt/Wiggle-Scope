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
    setLookAndFeel(&hookLook);
    scope.setup(audioProcessor.getLatestBuffer(), audioProcessor.getSampleRate());
    scope.setEnabled(true);
    addAndMakeVisible(scope);
    
    numSampsToDraw.setEnabled(true);
    numSampsToDraw.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox,
                                   true, 0, 0);
    numSampsToDraw.setRange(63, scope.getMaxNumSamplesToDraw());
    numSampsToDraw.addListener(this);
    numSampsToDraw.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible(numSampsToDraw);
    
    refreshRate.setEnabled(true);
    
    refreshRate.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox,
                                   true, 0, 0);
    refreshRate.setRange(20, 100);
    refreshRate.addListener(this);
    refreshRate.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible(refreshRate);
}

WiggleScopeAudioProcessorEditor::~WiggleScopeAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void WiggleScopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour(0xff4c5b5c).darker().darker());
    juce::String timeDivLabel = juce::String("Time / Div");
    g.setColour(juce::Colour(0xFF252525).contrasting());
    g.drawFittedText(timeDivLabel,
                     (getWidth() - 65) - g.getCurrentFont().getStringWidth(timeDivLabel) / 3,
                     numSampsToDraw.getY() - 20,
                     g.getCurrentFont().getStringWidth(timeDivLabel),
                     g.getCurrentFont().getHeight(),
                     juce::Justification::centred,
                     1);
    
    
    
    juce::String rateLabel = juce::String("Rate");
    g.drawFittedText(rateLabel,
                     getWidth() - 65,
                     refreshRate.getY() - 20,
                     g.getCurrentFont().getStringWidth(rateLabel),
                     g.getCurrentFont().getHeight(),
                     juce::Justification::centred,
                     1);
    
    g.setColour(juce::Colour(0xffe3655b).darker());
    g.drawLine(400, numSampsToDraw.getBottom() + 8, 500, numSampsToDraw.getBottom() + 8);
    g.drawLine(400, refreshRate.getBottom() + 8, 500, refreshRate.getBottom() + 8);
}

void WiggleScopeAudioProcessorEditor::resized()
{
    scope.setBounds(0, 0, 400, 300);
    numSampsToDraw.setBounds(getWidth() - 65, 24, 26, 26);
    refreshRate.setBounds(getWidth() - 65, 80, 26, 26);
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
