/*
  ==============================================================================

    effectComponent.cpp
    Created: 13 Oct 2022 5:31:57pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "effectComponent.h"

//==============================================================================
effectComponent::effectComponent(juce::AudioProcessorValueTreeState& paramTree)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.


    preGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    preGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 25);
    preGainSlider.setTextValueSuffix(" Units");
    addAndMakeVisible(preGainSlider);
    preGainAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "pregain", preGainSlider);


    postGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    postGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 25);
    postGainSlider.setTextValueSuffix(" Units");
    addAndMakeVisible(postGainSlider);
    postGainAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "postgain", postGainSlider);

    LPFCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LPFCutoffSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    LPFCutoffSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(LPFCutoffSlider);
    LPFCutoffAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "lpfcutoff", LPFCutoffSlider);

    HPFCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    HPFCutoffSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    HPFCutoffSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(HPFCutoffSlider);
    HPFCutoffAtc = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(paramTree, "hpfcutoff", HPFCutoffSlider);


    addAndMakeVisible(Reverb);
    reverbAtc = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(paramTree, "reverb", Reverb);


    addAndMakeVisible(DistToggle);
    distToggleAtc = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(paramTree, "disttoggle", DistToggle);


    addAndMakeVisible(FilterToggle);
    FilterToggleAtc = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(paramTree, "filtertoggle", FilterToggle);

    addAndMakeVisible(FilterToggleHp);
    FilterToggleHpAtc = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(paramTree, "filtertogglehp", FilterToggleHp);



    lpfLabel.setText("Low Pass", juce::NotificationType::dontSendNotification);
    lpfLabel.setSize(100, 100);
    addAndMakeVisible(lpfLabel);

    hpfLabel.setText("High Pass", juce::NotificationType::dontSendNotification);
    hpfLabel.setSize(100, 100);
    addAndMakeVisible(hpfLabel);

    reverbLabel.setText("Reverb", juce::NotificationType::dontSendNotification);
    reverbLabel.setSize(100, 100);
    addAndMakeVisible(reverbLabel);

    distLabel.setText("Distortion", juce::NotificationType::dontSendNotification);
    distLabel.setSize(100, 100);
    addAndMakeVisible(distLabel);
}

effectComponent::~effectComponent()
{
}

void effectComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::rebeccapurple);
}

void effectComponent::resized()
{
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;

    preGainSlider.setBounds(  x, 2.5 * y, 100, 100);
    postGainSlider.setBounds(2 * x, 2.5 * y, 100, 100);
    LPFCutoffSlider.setBounds(4 * x, 2.5 * y, 100, 100);
    HPFCutoffSlider.setBounds(6 * x, 2.5 * y, 100, 100);


    Reverb.setBounds(8.5 * x, 1 * y, 100, 100);
    DistToggle.setBounds(2 * x, 1 * y, 100, 100);
    FilterToggle.setBounds(4.5 * x, 1 * y, 100, 100);
    FilterToggleHp.setBounds(6.5 * x, 1 * y, 100, 100);


    reverbLabel.setBounds(8.25 * x, 0.15 * y, 100, 100);
    distLabel.setBounds(1.75 * x, 0.15 * y, 100, 100);
    lpfLabel.setBounds(4.25 * x, 0.15 * y, 100, 100);
    hpfLabel.setBounds(6.25 * x, 0.15 * y, 100, 100);

 




}
