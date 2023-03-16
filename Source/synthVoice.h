/*
  ==============================================================================

    synthVoice.h
    Created: 10 Oct 2022 12:53:20pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include "synthSound.h"
#include <JuceHeader.h>
#include "Data/envelopeData.h"
#include "Data/oscillatorData.h"
class synthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesperBlock, int outputChannels);
    void updateParams(const float a, const float d, const float s, const float r);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override; 
    oscData& getOsicalltor();
private:
    envData envData;
    oscData oscData;
    juce::dsp::Gain<float> gain;
    juce::AudioBuffer<float> synthBuffer;
   

    //return std::sin(x);
    //return x/MathConstants<float>::pi;
    //return x<0.0f?-1.0f:1.0f;
};