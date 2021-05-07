/*
 ==============================================================================
 
 Phasor.cpp
 Created: 3 May 2021 2:55:35pm
 Author:  mhamilt7
 
 ==============================================================================
 */

#include "Phasor.h"
Phasor::~Phasor(){}

void Phasor::setup(float sampRate, float freq)
{
    setSampleRate(sampRate);
    setFrequency(freq);
}

void Phasor::setSampleRate(float sampRate)
{
    sampleRate = sampRate;
}

float Phasor::getSampleRate()
{
    return sampleRate;
}

void Phasor::setFrequency(float freq)
{
    if(frequency != freq)
    {
        frequency = freq;
        phaseDelta = frequency / sampleRate;
    }
}
float Phasor::getFrequency()
{
    return frequency;
}

float Phasor::process()
{
    phase += phaseDelta;
    
    if (phase > 1.0f)
        phase -= 1.0f;
    
    return output();
}

float Phasor::output()
{
    return phase;
}

