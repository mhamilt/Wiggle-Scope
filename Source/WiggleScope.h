/*
 =============================================================================
 
 WiggleScope.
 Created: 10 May 2021 8:50:07a
 Author:  mhamilt
 
 =============================================================================
 */
#pragma onc

#include <JuceHeader.h>

//=============================================================================

class WiggleScope : public juce::Component, public juce::Timer
{
public:
    WiggleScope();
    ~WiggleScope() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    void setup(juce::AudioBuffer<float>* currentBuffer, float sampRate);
    void setScopeBuffer(juce::AudioBuffer<float>* currentBuffer);
    void setSampleRate(float sampRate);
    void setRefreshRate(float refreshMs);
    void setNumSamplesToDraw(unsigned int numSamps);
    int getMaxNumSamplesToDraw();
    
private:
    void timerCallback() override
    {
        repaint();
        if (adjustTimer)
        {
            stopTimer();
            startTimer(refreshRate);
            adjustTimer = false;
        }
    };
    
private:
    
    juce::AudioBuffer<float>* scopeBuffer = nullptr;
    unsigned int numSamplesToDraw  = 0;
    unsigned int maxNumSamplesToDraw = 0;
    unsigned int drawSampleSkip = 1;
    float refreshRate = 60.0f;
    float sampleRate = 44100.0f;
    juce::Path test;
    bool adjustTimer = false;
    bool triggerOn = true;
    
    
    juce::Colour channelColour[8]
    {
        juce::Colours::white,
        juce::Colours::red,
        juce::Colours::orange,
        juce::Colours::yellow,
        juce::Colours::green,
        juce::Colours::blue,
        juce::Colours::purple,
        juce::Colours::violet
    };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WiggleScope)
};

