/*
 ==============================================================================
 
 Phasor.h
 Created: 3 May 2021 2:55:35pm
 Author:  mhamilt7
 
 ==============================================================================
 */

#pragma once

#include <cmath>

class Phasor
{
public:
    virtual ~Phasor();
    /// setup required parameters for oscillator to function
    ///
    ///  You can run setSampleRate and setFrequency separately but failing to call this method
    ///  or any other before `process` will result in undefined behaviour
    ///
    /// @see setSampleRate, setFrequency
    /// @param sampRate current audio sampling rate.: typically 44100 or 48000, though other values will be allowed
    /// @param freq fundamental frequency this should be greater than zero and less than sampleRate / 2 (i.e. Nyquist)
    void setup(float sampRate, float freq);
    /// Set the internal sample so that the correct phase delta is used. You **MUST** call this method before setFrequency
    /// @see setup, setFrequency
    /// @param sampRate current audio sampling rate.: typically 44100 or 48000, though other values will be allowed
    void setSampleRate(float sampRate);
    /// Set the fundamental frequency of the oscillator. Remember you **MUST** call setSampleRate before calling this method
    ///
    /// @warning Calling this method will reset the phase of the oscillator so take care to only call this at a zero crossing value to avoid
    ///          clipping audio
    /// @param freq fundamental frequency this should be greater than zero and less than sampleRate / 2 (i.e. Nyquist)
    ///                  Negative frequency will be interpreted as _phase inverted_
    void setFrequency(float freq);
    /// @return current internal reference sample rate
    float getSampleRate();
    /// @return current frequency in Hz
    float getFrequency();
    /// get the next amplitude of the oscillator. This method will increment the phase of the oscillator.
    /// @return sample value in floating point format scaled between -1.0 and 1.0
    float process();
private:
    /// output is called by process after increment the internl phase reference by the phase delta. Override this method when inheriting to construct other oscillators
    /// @return sample value in floating point format scaled between -1.0 and 1.0
    virtual float output();
protected:
    float phase = 0.0f;
    static constexpr float tau = 2.0f * 3.14159;
private:
    float frequency;
    float sampleRate;
    float phaseDelta;
};
