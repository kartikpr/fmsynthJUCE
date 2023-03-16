/*
  ==============================================================================

    envelopeComponent.h
    Created: 11 Oct 2022 3:29:32pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class envelopeComponent  : public juce::Component
{
public:
    envelopeComponent(juce::AudioProcessorValueTreeState& paramTree);
    ~envelopeComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliderParams(juce::Slider& slider);

private:
    juce::Slider sliderAttack;
    juce::Slider sliderDecay;
    juce::Slider sliderSustain;
    juce::Slider sliderRelease;

public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAtc;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAtc;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAtc;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAtc;
    juce::Label adsrLabel;


   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (envelopeComponent)
};
