/*
  ==============================================================================

    SineOscillator.h
    Created: 25 Nov 2021 11:04:41am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>

class SineOscillator {
public:
    /** Contructor */
    SineOscillator();
    
    /** Destructor */
    ~SineOscillator();
    
    /** Gets next sample */
    float nextSample();
    
    /** Updates oscillator frequency */
    void setFrequency(float freq);
    
    /** Returns the current frequency */
    const float getFrequency();
    
    /** Sets current sample rate and updates the phase increment */
    void updateSampleRate(float newSampleRate);
    
    /** Renders a Sine Wave */
    float renderWaveShape(float phase);
    
    float blit(float frequency);
    
private:
    void updatePhaseIncrement();
    
    float phasePosition = 0.f;
    float phaseIncrement = 0.f;
    float currentSampleRate = 44100.f;
    
    float frequency = 440.f;
};
