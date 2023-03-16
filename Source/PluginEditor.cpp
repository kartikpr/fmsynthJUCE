/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthJUCEAudioProcessorEditor::SynthJUCEAudioProcessorEditor(SynthJUCEAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), env(audioProcessor.paramTree), osc(audioProcessor.paramTree), effect(audioProcessor.paramTree)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    //auto attack = audioProcessorTest.paramTree.getRawParameterValue("attack");
    addAndMakeVisible(env);
    addAndMakeVisible(osc);
    addAndMakeVisible(effect);






}

SynthJUCEAudioProcessorEditor::~SynthJUCEAudioProcessorEditor()
{
}

//==============================================================================
void SynthJUCEAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void SynthJUCEAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    env.setBounds(getWidth()/2,0, getWidth()/2, getHeight()/2);
    osc.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    effect.setBounds(0, getHeight() / 2, getWidth(), getHeight());
   





}

