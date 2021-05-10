/*
 ==============================================================================
 
 WiggleScope.cpp
 Created: 10 May 2021 8:50:07am
 Author:  mhamilt7
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "WiggleScope.h"

//==============================================================================
WiggleScope::WiggleScope()
{
    startTimer(40.0);
}

WiggleScope::~WiggleScope()
{
}

void WiggleScope::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    if (scopeBuffer)
    {
        juce::Path wave;
        float waveThickness = 1.0f;
        
        auto xStep  = getWidth() / float((numSamplesToDraw-1));
        auto midY = (getHeight() * 0.5f);
        float waveMargin = 0.9;
        
        for (int channel = 0; channel < 1 ; ++channel)
        {
            g.setColour (channelColour[channel]);
            auto* audioInput = scopeBuffer->getReadPointer(0);
            float lastSample = 0.0f;
            
            for (int i = 0 ; i < (numSamplesToDraw - drawSampleSkip); i += drawSampleSkip)
            {
                float fromY = -audioInput[i] * (midY * waveMargin);
                float toY   = -audioInput[i + drawSampleSkip] * (midY * waveMargin);
                
                wave.addLineSegment(juce::Line<float>(i * xStep,
                                                      midY + fromY,
                                                      (i + drawSampleSkip) * xStep,
                                                      midY + toY),
                                    waveThickness);
                lastSample = toY;
            }
        }
        
        g.strokePath(wave, juce::PathStrokeType(1.0f));
    }
}

void WiggleScope::resized()
{
}

void WiggleScope::setup(juce::AudioBuffer<float>* currentBuffer, float sampRate)
{
    setScopeBuffer(currentBuffer);
    setSampleRate(sampRate);

}


void WiggleScope::setScopeBuffer(juce::AudioBuffer<float>* currentBuffer)
{
    scopeBuffer = currentBuffer;
    numSamplesToDraw    = 256;
    maxNumSamplesToDraw = scopeBuffer->getNumSamples();    
}

void WiggleScope::setSampleRate(float sampRate)
{
    sampleRate = sampRate;
}

void WiggleScope::setRefreshRate(float reshreshMs)
{
    refreshRate = reshreshMs;
    
    adjustTimer = true;
}

void WiggleScope::setNumSamplesToDraw(unsigned int numSamples)
{
    numSamplesToDraw = ((numSamples > maxNumSamplesToDraw) ? maxNumSamplesToDraw : numSamples);
    if (numSamplesToDraw > 800)
        drawSampleSkip = numSamplesToDraw / 200;
    else
        drawSampleSkip = 1;
}

int WiggleScope::getMaxNumSamplesToDraw()
{
    return maxNumSamplesToDraw;
}
