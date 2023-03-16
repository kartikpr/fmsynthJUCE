/*
  ==============================================================================

    oscillatorData.h
    Created: 11 Oct 2022 5:09:56pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class oscData : public juce::dsp::Oscillator<float> {
public:
    void setOscType(int type);
    void prepareToPlay(juce::dsp::ProcessSpec);
    void nextAudioBlock(juce::dsp::AudioBlock<float>&);
    void frequencySet(int note);
    void setFmParams(float depth, float freq);
    void processFmOsc(juce::dsp::AudioBlock<float>& block);

private:

    juce::dsp::Oscillator<float> fmOsc{ [](float x) {return std::sin(x);} };
    int lastMidiNote;
    float fmDepth;
    float fmVal;

};