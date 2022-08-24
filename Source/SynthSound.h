/*
  ==============================================================================

    SynthSound.h
    Created: 16 Dec 2021 12:39:46am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public SynthesiserSound {
public:
    /** Returns true to say note should be played */
    bool appliesToNote(int) override { return true; }
    
    /** Returns true to say it applies to channel */
    bool appliesToChannel(int) override { return true; }
};
