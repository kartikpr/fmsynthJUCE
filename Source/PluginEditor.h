/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Interface/envelopeComponent.h"
#include "Interface/oscillatorComponent.h"
#include "Interface/effectComponent.h"


//==============================================================================
/**
*/
class SynthJUCEAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthJUCEAudioProcessorEditor (SynthJUCEAudioProcessor&);
    ~SynthJUCEAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //SynthJUCEAudioProcessor audioProcessorTest;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthJUCEAudioProcessor& audioProcessor;
    
    envelopeComponent env;
    oscillatorComponent osc;
    effectComponent effect;

    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthJUCEAudioProcessorEditor)
};
