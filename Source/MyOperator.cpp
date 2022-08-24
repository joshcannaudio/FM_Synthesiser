/*
  ==============================================================================

    MyOperator.cpp
    Created: 12 Jan 2022 6:50:14pm
    Author:  Josh Cann

  ==============================================================================
*/

#include "MyOperator.h"

MyOperator::MyOperator()
{
}

void MyOperator::reset()
{
//    carrier.reset();
//    modulator.reset();
}

void MyOperator::setOscillator(float fFrequency)
{
    carrier.setFrequency(blit(fFrequency));
}

void MyOperator::setModulator(float fIndex, float fFrequency)
{
    fc = fFrequency;
    fd = fc;
    I = fIndex;
    Ifd = fd * I;
    modulator.setFrequency(blit(fd));
}

float MyOperator::tickCarrier()
{
    return carrier.nextSample();
}

float MyOperator::tickModulator()
{
    return modulator.nextSample() * Ifd;
}

float MyOperator::blit(float frequency)
{
    auto nyquist = currentSampleRate * 0.5;
    if(frequency > nyquist)
        frequency = nyquist;
    return frequency;
}
