/*
  ==============================================================================

    Additive.cpp
    Created: 17 Jan 2022 1:52:00pm
    Author:  Josh Cann

  ==============================================================================
*/

#include "Additive.h"

Additive::Additive()
{
    
}

Additive::~Additive() {}

void Additive::updateSampleRate(float sampleRate)
{
    currentSampleRate = sampleRate;
    for(int h = 0; h < MAX_HARMONICS; h++)
        harmonic[h].updateSampleRate(currentSampleRate);
    nyquist = sampleRate * 0.5;
}

const float Additive::getNyquist()
{
    return nyquist;
}

void Additive::setFrequency(float frequency)
{
    for (int h = 0; h < MAX_HARMONICS; h++) {
        const int n = h + 1;
        harmonic[h].setFrequency(frequency * n);
    }
}
