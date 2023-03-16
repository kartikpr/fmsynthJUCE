/*
  ==============================================================================

    effectComponent.h
    Created: 13 Oct 2022 5:31:57pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class effectComponent  : public juce::Component
{
public:
    effectComponent(juce::AudioProcessorValueTreeState &paramTree);
    ~effectComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;


    juce::Slider preGainSlider;
    juce::Slider postGainSlider;


    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> preGainAtc;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> postGainAtc;



    juce::Slider LPFCutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LPFCutoffAtc;

    juce::Slider HPFCutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HPFCutoffAtc;

    juce::ToggleButton Reverb;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbAtc;

    juce::ToggleButton DistToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> distToggleAtc;

    juce::ToggleButton FilterToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> FilterToggleAtc;

    juce::ToggleButton FilterToggleHp;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> FilterToggleHpAtc;


    juce::Label reverbLabel;
    juce::Label lpfLabel;
    juce::Label hpfLabel;
    juce::Label distLabel;




private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (effectComponent)
};
