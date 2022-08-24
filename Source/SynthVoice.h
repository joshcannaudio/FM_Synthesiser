/*
  ==============================================================================

    SynthVoice.h
    Created: 16 Dec 2021 12:52:47am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthVoiceHeader.h"

class SynthVoice : public SynthesiserVoice {
public:
    
    /** Contructor, called when a new instance is created */
    SynthVoice();
    
    /** Checks to see if the synthesiser can play sound */
    bool canPlaySound(SynthesiserSound* sound) override;
    
    /** Called when a note on message is recieved, deals with setting oscillators and envelopes which dont need to be set in the audio process */
    void startNote(int midiNoteNumber,
                    float velocity,
                    SynthesiserSound*,
                    int currentPitchWheelPosition) override;
    
    /** Called when note off midi message is recieved, used to clear the note and frees up a voice for another note unless allowTailOff is true */
    void stopNote(float velocity, bool allowTailOff) override;
    
    /** Renders the next block of audio, most of the synthesis processing is done here */
    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
 
    /** Called when the pitch wheel moves */
    void pitchWheelMoved(int newPitchWheelValue) override;
      
    /** Called when recieving CC message from controller */
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    
    /** Sets the parameters, essentially tidies the code out of the way and enables the parameters to be set in multiple places */
    void setParameters();
    
    /** Finds longest release to enable all envelopes to finish releasing before  the current note is cleared
        @return the index of the envelope array which has the longest release
     */
    int getLongestReleaseIndex();
    
private:
    MyEnvelope oscEnv[4];
    MyFMSynth FMSynth;
    
    float osc[4] { 0 };
    float amplitude = 0.f;
    float frequency = 440.f;
    int pitch;
    float pitchBend = 0;
    
    float a[4], d[4], s[4], r[4];
    float oscGain[4], oscTune[4], env[4];
    float waveForm[2];
    
    float FMTone, filterCutoff, masterVolume = 0;
};
