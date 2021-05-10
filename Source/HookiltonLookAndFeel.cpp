/*
  ==============================================================================

    HookiltonLookAndFeel.cpp
    Created: 10 May 2021 7:19:44pm
    Author:  mhamilt7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HookiltonLookAndFeel.h"

//==============================================================================
HookiltonLookAndFeel::HookiltonLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

HookiltonLookAndFeel::~HookiltonLookAndFeel()
{
}



void HookiltonLookAndFeel::drawRotarySlider(juce::Graphics & g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &)
{
    int midX = x +  width / 2;
    int midY = y + height / 2;
    
    int baseDiam = ((width < height) ? width : height);
    
    if (width > height)
        x += midX;
    
    else if (width < height)
        y += midY;
    
    
    juce::Path dial;
    g.setColour(blue.darker().darker());
    g.fillEllipse(x, y, baseDiam, baseDiam);
    g.setColour(blue.darker());
    int rimDiam = baseDiam * 0.9;
    int rimX = x + (baseDiam - rimDiam) / 2;
    int rimY = y + (baseDiam - rimDiam) / 2;
    g.fillEllipse(rimX, rimY, rimDiam, rimDiam);
    g.setColour(blue);
    int topDiam = rimDiam * 0.85;
    int topX = rimX + (rimDiam - topDiam) / 2;
    int topY = rimY + (rimDiam - topDiam) / 2;
    g.fillEllipse(topX, topY, topDiam, topDiam);
    int topRingDiam = topDiam * 0.7;
    int topRingX = topX + (topDiam - topRingDiam) / 2;
    int topRingY = topY + (topDiam - topRingDiam) / 2;
    
    g.setColour(blue.contrasting(opal, 0.2f));
    g.drawEllipse(topRingX, topRingY, topRingDiam,topRingDiam, 1.0f);
    
    
    auto tau = juce::MathConstants<float>::twoPi;
    auto pi = juce::MathConstants<float>::pi;
    float phase = (sliderPosProportional *  5.0 * tau / 7.0) + 11.0 * pi / 14.0;
    float lineLength  = float(topDiam) * 0.45f;
    g.addTransform(juce::AffineTransform::translation(width/2, height/2));
    g.drawLine(0, 0, int(cos(phase) * lineLength), int(sin(phase) * lineLength));
        
}
