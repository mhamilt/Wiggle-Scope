/*
 ==============================================================================
 
 Oscillator.cpp
 Created: 3 May 2021 2:55:47pm
 Author:  mhamilt7
 
 ==============================================================================
 */

#include "SineOsc.h"

float SinOsc::output()
{
    return std::sin(phase * tau);
}
