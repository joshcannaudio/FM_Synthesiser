/*
  ==============================================================================

    Parameters.cpp
    Created: 12 Jan 2022 1:15:40pm
    Author:  Josh Cann

  ==============================================================================
*/

#include "Parameters.h"

float Parameters::parameters[] = {0};

float MyFunctions::amplitudeTodB(float amplitude)
{
    return 20 * log10(amplitude);
}

/** Converts dB to amplitude */
float MyFunctions::dBtoAmplitude(float dB)
{
    float amplitude = pow(10, dB / 20);
    if(dB <= -60)
        amplitude = 0;
    return amplitude;
}

float MyFunctions::cube(float value)
{
    return value * value * value;
}

float MyFunctions::getSemitoneTuning(float frequency, float semitones) // +- 1 for +- Octave
{
   semitones /= 12;
   float tune = semitones * semitones;//powf(2.0, semitones);
   return frequency * tune;
}
