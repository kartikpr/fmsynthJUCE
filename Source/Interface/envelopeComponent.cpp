/*
  ==============================================================================

    envelopeComponent.cpp
    Created: 11 Oct 2022 3:29:32pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "envelopeComponent.h"

//==============================================================================
envelopeComponent::envelopeComponent(juce::AudioProcessorValueTreeState& paramTree)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    attackAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "attack", sliderAttack);
    decayAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "decay", sliderDecay);
    sustainAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "sustain", sliderSustain);
    releaseAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "release", sliderRelease);


    adsrLabel.setText("ADSR", juce::NotificationType::dontSendNotification);
    adsrLabel.setSize(100, 100);
    addAndMakeVisible(adsrLabel);

    setSliderParams(sliderAttack);
    setSliderParams(sliderDecay);
    setSliderParams(sliderSustain);
    setSliderParams(sliderRelease);

}

envelopeComponent::~envelopeComponent()
{
}

void envelopeComponent::setSliderParams(juce::Slider& slider) {


    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 40);
    addAndMakeVisible(slider);

}


void envelopeComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::mediumpurple);
}

void envelopeComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto x = getWidth() / 10;
    auto y = getHeight() / 10;
    sliderAttack.setBounds(3 * x, 2 * y, x, 5 * y);
    sliderDecay.setBounds(4 * x, 2 * y, x, 5 * y);
    sliderSustain.setBounds(5 * x, 2 * y, x, 5 * y);
    sliderRelease.setBounds(6 * x, 2 * y, x, 5 * y);
    adsrLabel.setBounds(4.5 * x, 6 * y, x, 5 * y);



}
