/*
  ==============================================================================

    Process.cpp
    Created: 10 Jan 2022 8:08:45pm
    Author:  Josh Cann

  ==============================================================================
*/

#include "Audio.h"

Audio::Audio()
{
    setAudioChannels(0, 2);
     auto errorMessage = audioDeviceManager.initialiseWithDefaultDevices(1, 2);
     if ( ! errorMessage.isEmpty())
         DBG (errorMessage);

    auto midiInputDevices = MidiInput::getAvailableDevices();
     if (midiInputDevices.size() > 0)
         audioDeviceManager.setMidiInputDeviceEnabled(midiInputDevices[0].identifier, true);
    audioDeviceManager.addMidiInputDeviceCallback("", &midiCollector);
    
    synth.clearVoices();
    for(int i = 0; i < 16; i++)
        synth.addVoice(new SynthVoice());

    synth.clearSounds();
    synth.addSound(new SynthSound());
}

Audio::~Audio()
{
    audioDeviceManager.removeMidiInputDeviceCallback("", &midiCollector);
    synth.clearVoices();
    synth.clearSounds();
    shutdownAudio();
}

void Audio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    midiCollector.reset(sampleRate);
}

void Audio::releaseResources()
{
}

void Audio::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);

    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi,
                                bufferToFill.startSample, bufferToFill.numSamples);
    
    process(*bufferToFill.buffer, bufferToFill.buffer->getArrayOfWritePointers(), bufferToFill.startSample, bufferToFill.numSamples);
}

void Audio::process(AudioBuffer<float> &buffer, float** outputBuffer, int startSample, int numSamples)
{
    float in0, in1, out0 = 0, out1 = 0;
    const float *inBuffer0 = buffer.getWritePointer(0), *inBuffer1 = buffer.getWritePointer(1);
    float *outBuffer0 = outputBuffer[0], *outBuffer1 = outputBuffer[1];
    
    
    float globalFilterCutoff = MyFunctions::cube(Parameters::parameters[25]);
    float masterLevel = MyFunctions::dBtoAmplitude(Parameters::parameters[26]) * 0.6;
    
    // Distortion Parameters
    bool distortionToggle = Parameters::parameters[27];
    float inGain = Parameters::parameters[28];
    float coeff = Parameters::parameters[29] * 0.01;
    float disMix = Parameters::parameters[30] * 0.01;
    
    
    // Tremolo Parameters
    bool tremoloToggle = Parameters::parameters[31];
    float tremRate = Parameters::parameters[32];
    float tremDepth = Parameters::parameters[33] * 0.01;
    tremolo.setLFO(tremRate, tremDepth);
    
    globalFilter.setCutoff(globalFilterCutoff);
    parameterSmoother.setCutoff(0.0005);
    
    while(--numSamples >= 0)
    {
        parameterSmoother.tick(masterLevel);
        
        in0 = *inBuffer0++;
        in1 = *inBuffer1++;
        
        if(distortionToggle) {
            float distorted = distortion.getSoftClip((in0 + in1) * 0.5, inGain, coeff);
            in0 = ((distorted * disMix) + (in0 * (1 - disMix)));
            in1 = ((distorted * disMix) + (in1 * (1 - disMix)));;
        }
        
        if(tremoloToggle) {
            float modulated = ((in0 + in1) * 0.5) * tremolo.tick();
            in0 = modulated;
            in1 = modulated;
        }
        
        out0 = globalFilter.tick(in0);
        out1 = globalFilter.tick(in1);
        
        *outBuffer0++ = out0 * masterLevel;
        *outBuffer1++ = out1 * masterLevel;
        ++startSample;
    }
}
