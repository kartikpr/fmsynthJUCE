/*
  ==============================================================================

    oscillatorComponent.cpp
    Created: 11 Oct 2022 6:17:14pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "oscillatorComponent.h"

//==============================================================================
oscillatorComponent::oscillatorComponent(juce::AudioProcessorValueTreeState& paramTree)
{
    juce::StringArray types{ "sine", "square", "saw" };
    oscSelect.addItemList(types,1);
    addAndMakeVisible(oscSelect);
    fmFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 75, 25);
    fmFreqSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(fmFreqSlider);
    fmDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmDepthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 75, 25);
    fmDepthSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(fmDepthSlider);
    oscAtc = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(paramTree, "oscType", oscSelect);
   fmDepthAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "fmdepth", fmDepthSlider);
   fmFreqAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "fmfreq", fmFreqSlider);

   depthLabel.setText("Depth", juce::NotificationType::dontSendNotification);
   depthLabel.setSize(100, 100);
   addAndMakeVisible(depthLabel);

   freqLabel.setText("ModFreq", juce::NotificationType::dontSendNotification);
   freqLabel.setSize(100, 100);
   addAndMakeVisible(freqLabel);
}

oscillatorComponent::~oscillatorComponent()
{
}

void oscillatorComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::blueviolet);

}

void oscillatorComponent::resized()
{

    auto x = getWidth() / 10;
    auto y = getHeight() / 10;
    oscSelect.setBounds(0,0,90,20);

    fmFreqSlider.setBounds(2 * x, 3 * y, 100, 100);
    fmDepthSlider.setBounds(5 * x, 3 * y,  100, 100);

    depthLabel.setBounds(5.5 * x, 5 * y, 100, 100);
    freqLabel.setBounds(2.5 * x, 5 * y, 100, 100);






}
