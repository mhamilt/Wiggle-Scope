/*
  ==============================================================================

    HookiltonLookAndFeel.h
    Created: 10 May 2021 7:19:44pm
    Author:  mhamilt7

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class HookiltonLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    HookiltonLookAndFeel();
    ~HookiltonLookAndFeel() override;

    void drawRotarySlider (juce::Graphics &,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider &) override;
private:
    juce::Colour blue = juce::Colour(0xff3891a6);
    juce::Colour grey = juce::Colour(0xff4c5b5c);
    juce::Colour yell = juce::Colour(0xfffde74c);
    juce::Colour redd = juce::Colour(0xffdb5461);
    juce::Colour opal = juce::Colour(0xffe3655b);
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HookiltonLookAndFeel)
};
