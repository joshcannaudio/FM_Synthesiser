/*
  ==============================================================================

    Additive.h
    Created: 17 Jan 2022 1:52:00pm
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include "SineOscillator.h"
#define MAX_HARMONICS 32

class Additive {
public:
    Additive();
    
    virtual ~Additive() = 0;
    
    void updateSampleRate(float sampleRate);
    
    void setFrequency(float frequency);

    /** Pure virtual function to be overriden by the specific wave shape oscillator */
    virtual float nextSample() = 0;
    
protected:
    const float getNyquist();
    
    float wave;
    SineOscillator harmonic[MAX_HARMONICS];
private:
    float currentSampleRate = 44100.f;
    float nyquist = 22050.f;
};
