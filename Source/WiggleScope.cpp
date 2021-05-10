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
    auto midY = (getHeight() * 0.5f);
    float vertMargin = 0.8;
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (juce::Colours::yellow);
    g.setFont (10.0f);
        
    juce::Path grid;
    float gridThickness = 0.293;
    float numXlines = 8;
    float numYlines = 7;
    float yStep = (getHeight() * vertMargin  / (numYlines - 1) );
    float offset = getHeight() * ((1.0 - vertMargin) * 0.5);
    float ytickStep = 2 / float(numYlines - 1);
    for (int y = 0; y < numYlines; ++y)
    {
        juce::String ytickLabel = juce::String(1.0f - (float(y) * ytickStep), 1.0);
        g.drawFittedText(ytickLabel,
                         5,
                         y * yStep + offset + (g.getCurrentFont().getHeight() * 0.5),
                         g.getCurrentFont().getStringWidth(ytickLabel),
                         g.getCurrentFont().getHeight(),
                         juce::Justification::left,
                         1);
        
        
        grid.addLineSegment(juce::Line<float>(0.0,
                                              y * yStep + offset,
                                              getWidth(),
                                              y * yStep + offset),
                            gridThickness);
    }
    
    
    float xStep  = getWidth() / (numXlines - 1);
    for (int x = 0; x < numXlines; ++x)
    {
        grid.addLineSegment(juce::Line<float>(x * xStep,
                                              0.0,
                                              x * xStep,
                                              getHeight()),
                            gridThickness);
    }
    
    g.strokePath(grid, juce::PathStrokeType(gridThickness));
    
    if (scopeBuffer)
    {
        juce::Path wave;
        float waveThickness = 1.0f;
        
        auto xStep  = getWidth() / float((numSamplesToDraw-1));
        
        
        
        for (int channel = 0; channel < 1 ; ++channel)
        {
            g.setColour (channelColour[channel]);
            auto* audioInput = scopeBuffer->getReadPointer(0);
            float lastSample = 0.0f;
            
            for (int i = 0 ; i < (numSamplesToDraw - drawSampleSkip); i += drawSampleSkip)
            {
                float fromY = -audioInput[i] * (midY * vertMargin);
                float toY   = -audioInput[i + drawSampleSkip] * (midY * vertMargin);
                
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
