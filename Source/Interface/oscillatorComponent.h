/*
  ==============================================================================

    oscillatorComponent.h
    Created: 11 Oct 2022 6:17:14pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class oscillatorComponent  : public juce::Component
{
public:
    oscillatorComponent(juce::AudioProcessorValueTreeState& paramTree);
    ~oscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscSelect;
    juce::Slider fmDepthSlider;
    juce::Slider fmFreqSlider;

    juce::Label depthLabel;
    juce::Label freqLabel;
public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscAtc;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAtc;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAtc;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (oscillatorComponent)
};
