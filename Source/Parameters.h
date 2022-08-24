/*
  ==============================================================================

    Parameters.h
    Created: 12 Jan 2022 1:15:40pm
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <cmath>

struct Parameters { static float parameters[39]; };

class MyFunctions {
public:
    /** Converts amplitude to dB */
    static float amplitudeTodB(float amplitude);
    
      /** Converts dB to amplitude */
    static float dBtoAmplitude(float dB);
      
    /** Returns a vlue cubed, quicker than using the pow function */
    static float cube(float value);
    
    /** Takes a frequency and returns a tuning value based*/
    static float getSemitoneTuning(float frequency, float semitones);
    
private:
};
