/*
  ==============================================================================

    Effects.h
    Created: 18 Jan 2022 9:44:32am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "SineOscillator.h"

class MyFilter {
public:
    void updateSampleRate(float sampleRate) { currentSampleRate = sampleRate; }
    
    /** Sets the cutoff coefficient */
    void setCutoff(float coeff);
   
    /** Filters the input */
    float tick(float input);
    
    float getCutoff();
    
private:
    float a, b;
    float currentSample, previousSample = 0, currentSampleRate = 44100;
};

class Distortion {
public:
    Distortion(){};
    float getSoftClip(float input, float inGain, float aCoeff);
private:
};

class MyModulation {
public:
    MyModulation(){}
    
    void setLFO(float rate, float depth);
    
    float tick();
    
private:
    SineOscillator sine;
    float fMod, fDepth;
};
