/*
  ==============================================================================

    oscillatorData.cpp
    Created: 11 Oct 2022 5:09:56pm
    Author:  user

  ==============================================================================
*/

#include "oscillatorData.h"
void oscData::prepareToPlay(juce::dsp::ProcessSpec spec) {
    fmOsc.prepare(spec);
    prepare(spec);
}
void oscData::frequencySet(int note) {
    lastMidiNote = note;
}


void oscData::setOscType(int type) {
    switch (type) {
    case 0:
        initialise([](float x) {return std::sin(x);});
        break;

    case 1:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
        break;
    case 2:
        initialise([](float x) {return x / juce::MathConstants<float>::pi;});
        break;
    }

    
}

void oscData::setFmParams(float depth, float freq) {
    fmOsc.setFrequency(freq);
    fmDepth = depth;

}
    void oscData::nextAudioBlock(juce::dsp::AudioBlock<float>& block)
    {

        float fmVal{};
        for (int i = 0; i < block.getNumChannels(); i++) {
            for (int j = 0; j < block.getNumSamples(); j++) {
               fmVal =  fmOsc.processSample(block.getSample(i,j));
            }
        }
        float frequency = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + (fmVal * fmDepth);
        if (frequency < 0) {
            frequency = frequency * (-1.0f);
        }
        setFrequency(frequency);

       process(juce::dsp::ProcessContextReplacing<float>(block));

    }

    //return std::sin(x);
  //  return x / juce::MathConstants<float>::pi;
//    return x < 0.0f ? -1.0f : 1.0f;
