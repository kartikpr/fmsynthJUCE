/*
  ==============================================================================

    synthSound.h
    Created: 10 Oct 2022 12:53:54pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class synthSound :public juce::SynthesiserSound {
    bool appliesToNote(int midiNoteNumber) override {
        return true;
    }

    bool appliesToChannel(int midiChannel) override {
        return true;
    }
};
