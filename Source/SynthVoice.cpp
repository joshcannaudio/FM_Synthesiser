/*
  ==============================================================================

    SynthVoice.cpp
    Created: 16 Dec 2021 12:52:47am
    Author:  Josh Cann

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
    setParameters();
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber,
                            float velocity,
                            juce::SynthesiserSound*,
                            int /*currentPitchWheelPosition*/)
{
    for(int i = 0; i < 4; i++) {
        oscEnv[i].updateSampleRate(getSampleRate());
        oscEnv[i].setADSR(a[i], d[i], s[i], r[i]);
    }
    
    FMSynth.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    setParameters();
    amplitude = velocity;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    setParameters();
    for(int i = 0; i < 4; i++) {
        oscEnv[i].release();
        if(oscEnv[i].getRelease() > 0)
            allowTailOff = true;
        else
            allowTailOff = false;
    }
}

void SynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) 
{
    setParameters();
    float fmSignal = 0;
    
    while (--numSamples >= 0)
    {
        if(oscEnv[getLongestReleaseIndex()].getStage() == MyEnvelope::STAGE::OFF)
            clearCurrentNote();
        
        for(int i = 0; i < 4; i++)
            env[i] = oscEnv[i].tick();
        
        // sets fm synth
        FMSynth.setFM(FMTone, oscGain, env, oscTune);
        fmSignal = FMSynth.nextSample();
        
        auto currentSample = fmSignal * amplitude;
        
        for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
            outputBuffer.addSample(channel, startSample, currentSample);
            outputBuffer.addSample(channel, startSample, currentSample);
        }
        ++startSample;
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}
  
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::setParameters()
{
    a[3] = Parameters::parameters[2];
    d[3] = Parameters::parameters[3];
    s[3] = Parameters::parameters[4];
    r[3] = Parameters::parameters[5];

    a[2] = Parameters::parameters[8];
    d[2] = Parameters::parameters[9];
    s[2] = Parameters::parameters[10];
    r[2] = Parameters::parameters[11];

    a[1] = Parameters::parameters[14];
    d[1] = Parameters::parameters[15];
    s[1] = Parameters::parameters[16];
    r[1] = Parameters::parameters[17];

    a[0] = Parameters::parameters[20];
    d[0] = Parameters::parameters[21];
    s[0] = Parameters::parameters[22];
    r[0] = Parameters::parameters[23];
    
    oscTune[3] = Parameters::parameters[0];
    oscTune[2] = Parameters::parameters[6];
    oscTune[1] = Parameters::parameters[12];
    oscTune[0] = Parameters::parameters[18];
    
    oscGain[3] = MyFunctions::dBtoAmplitude(Parameters::parameters[1]);
    oscGain[2] = MyFunctions::dBtoAmplitude(Parameters::parameters[7]);
    oscGain[1] = MyFunctions::dBtoAmplitude(Parameters::parameters[13]);
    oscGain[0] = MyFunctions::dBtoAmplitude(Parameters::parameters[19]);
    
//    filterCutoff = MyFunctions::cube(Parameters::parameters[32]);
//    masterVolume = Parameters::parameters[31];
    FMTone = Parameters::parameters[24] * 0.3;
    
    for(int i = 0; i < 4; i++)
        s[i] = MyFunctions::dBtoAmplitude(s[i]);
}

int SynthVoice::getLongestReleaseIndex()
{
    int releaseIndex = 0;
    float longestRelease = 0;
    for (int i = 0; i < 4; i++) {
        if(oscEnv[i].getRelease() > longestRelease) {
            longestRelease = oscEnv[i].getRelease();
            releaseIndex = i;
        }
    }
    return releaseIndex;
}
