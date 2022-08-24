/*
  ==============================================================================

    Process.h
    Created: 10 Jan 2022 8:08:45pm
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"
#include "Effects.h"

class Audio : public AudioAppComponent
{
public:
    /** Consructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** Returns the AudioDeviceManager so it can be accessed from other classes */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager; }
    
    /** Called to set the sample rate of SynthProcessor.
                  @param samplesPerBlockExpected this is the buffer size
                  @param sampleRate the current playback sample rate
     */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    /** Releases the resources */
    void releaseResources() override;
    
    /** Use this method to add samples to the output buffer.
                @param bufferToFill is AudioSourceChannlInfo containing a buffer
                                    it provides a buffer ot other renderNextBlock functions
     */
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    
    /** Processes the audio buffer seperately to save on CPU power.
                @param buffer the input buffer taken from Synthesiser
                @param outBuffer copy output samples to this
     */
    void process(AudioBuffer<float> &buffer, float** outBuffer, int startSample, int numSamples);
    
private:
    AudioDeviceManager audioDeviceManager;
    Synthesiser synth;
    MidiMessageCollector midiCollector;
    MyFilter globalFilter, parameterSmoother;
    Distortion distortion;
    MyModulation tremolo;
};

