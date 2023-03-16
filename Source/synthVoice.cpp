/*
  ==============================================================================

    synthVoice.cpp
    Created: 10 Oct 2022 12:53:20pm
    Author:  user

  ==============================================================================
*/

#include "synthVoice.h"
#include <JuceHeader.h>

bool synthVoice::canPlaySound(juce::SynthesiserSound* sound) {

    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;


}
void synthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    oscData.frequencySet(midiNoteNumber);
    envData.noteOn();


}

void synthVoice::pitchWheelMoved(int newPitchWheelValue) {




}
void synthVoice::stopNote(float velocity, bool allowTailOff) {

    envData.noteOff();
    if (!allowTailOff || !envData.isActive()) {
        clearCurrentNote();
    }

}
void synthVoice::controllerMoved(int controllerNumber, int newControllerValue) {




}

oscData& synthVoice::getOsicalltor() {
    return oscData;
}


void synthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

    oscData.prepareToPlay(spec);
  

    gain.prepare(spec);
    gain.setGainLinear(0.3f);
    envData.setSampleRate(sampleRate);





}


void synthVoice::updateParams(const float a, const float d, const float s, const float r) {
    envData.updateEnvelope(a, d, s, r);
}


void synthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    oscData.nextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    envData.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels();channel++) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!envData.isActive()) {
            clearCurrentNote();
        }
    }
}