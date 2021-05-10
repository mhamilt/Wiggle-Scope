/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WiggleScope.h"
#include "HookiltonLookAndFeel.h"
//==============================================================================
/**
*/
class WiggleScopeAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    WiggleScopeAudioProcessorEditor (WiggleScopeAudioProcessor&);
    ~WiggleScopeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider *slider) override;
private:
    /// This reference is provided as a quick way for your editor to
    /// access the processor object that created it.
    HookiltonLookAndFeel hookLook;
    WiggleScopeAudioProcessor& audioProcessor;
    WiggleScope scope;
    juce::Slider numSampsToDraw;
    juce::Slider refreshRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WiggleScopeAudioProcessorEditor)
};
