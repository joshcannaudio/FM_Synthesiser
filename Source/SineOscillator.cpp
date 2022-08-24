/*
  ==============================================================================

    SineOscillator.cpp
    Created: 25 Nov 2021 11:04:32am
    Author:  Josh Cann

  ==============================================================================
*/

#include "SineOscillator.h"

SineOscillator::SineOscillator()
{
    updatePhaseIncrement();
}

SineOscillator::~SineOscillator()
{
    
}

float SineOscillator::nextSample()
{
    float nextSample = renderWaveShape(phasePosition);
    
    phasePosition += phaseIncrement;
    if(phasePosition > MathConstants<float>::twoPi)
        phasePosition -= MathConstants<float>::twoPi;
    
    return nextSample;
}

void SineOscillator::setFrequency(float freq)
{
    frequency = blit(freq);
    updatePhaseIncrement();
}

const float SineOscillator::getFrequency()
{
    return frequency;
}

void SineOscillator::updateSampleRate(float sampleRate)
{
    currentSampleRate = sampleRate;
    updatePhaseIncrement();
}

float SineOscillator::renderWaveShape(float phase)
{
    return std::sin(phase);
}

void SineOscillator::updatePhaseIncrement()
{
    phaseIncrement = (MathConstants<float>::twoPi * frequency) / currentSampleRate;
}

float SineOscillator::blit(float frequency)
{
    if(frequency > (currentSampleRate * 0.5))
       frequency = currentSampleRate * 0.5;
       
    return frequency;
}
