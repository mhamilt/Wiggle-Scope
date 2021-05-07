/*
 ==============================================================================
 
 Oscillator.h
 Created: 3 May 2021 2:55:47pm
 Author:  mhamilt7
 
 ==============================================================================
 */

#pragma once

#include "Phasor.h"

class SinOsc : public Phasor
{
public:    
    float output() override;
};
