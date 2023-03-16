/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthJUCEAudioProcessor::SynthJUCEAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    ,paramTree(*this,nullptr, "parameters" , createParameters())
#endif
{
  
    synth.addSound(new synthSound());
    synth.addVoice(new synthVoice());
}

SynthJUCEAudioProcessor::~SynthJUCEAudioProcessor()
{
}

//==============================================================================
const juce::String SynthJUCEAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthJUCEAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthJUCEAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthJUCEAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthJUCEAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthJUCEAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthJUCEAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthJUCEAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthJUCEAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthJUCEAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthJUCEAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sampleGlobalRate = sampleRate;
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto castedVoice = dynamic_cast<synthVoice*>(synth.getVoice(i))) {
            castedVoice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    dist.prepare(spec);

    lowPassFilter.prepare(spec);
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 200.0f, 7.0f);

    highPassFilter.prepare(spec);
    *highPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 2000.0f, 2.0f);


    reverbParams.roomSize = 0.5f;
    reverbParams.width = 1.0f;
    reverbParams.damping = 0.5f;
    reverbParams.freezeMode = 0.0f;
    reverbParams.dryLevel = 0.0f;
    reverbParams.wetLevel = 1.0f;

    reverb.setParameters(reverbParams);

}

void SynthJUCEAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthJUCEAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthJUCEAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto& pregain = *paramTree.getRawParameterValue("pregain");
    auto& postgain = *paramTree.getRawParameterValue("postgain");
    dist.setDistParameters(pregain, postgain);

    auto& cutoff = *paramTree.getRawParameterValue("lpfcutoff");
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleGlobalRate, cutoff, 7.0f);

    auto& cutoffhp = *paramTree.getRawParameterValue("hpfcutoff");
    *highPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleGlobalRate, cutoffhp, 2.0f);

   

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


    for (uint32_t i = 0; i < buffer.getNumChannels(); i++) {
        {
            auto* channelData = buffer.getWritePointer(i);

            }
    }



    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<synthVoice*>(synth.getVoice(i))) {

            auto& attack = *paramTree.getRawParameterValue("attack");
            auto& decay = *paramTree.getRawParameterValue("decay");
            auto& sustain = *paramTree.getRawParameterValue("sustain");
            auto& release = *paramTree.getRawParameterValue("release");
            auto& osctype = *paramTree.getRawParameterValue("oscType");
            auto& fmdepth = *paramTree.getRawParameterValue("fmdepth");
            auto& fmfreq = *paramTree.getRawParameterValue("fmfreq");


            // should this be here ?
            voice->updateParams(attack.load(), decay.load(), sustain.load() , release.load());
            voice->getOsicalltor().setOscType(osctype);
            voice->getOsicalltor().setFmParams(fmdepth, fmfreq);
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    juce::dsp::AudioBlock<float> audioBlock{ buffer };

    auto& reverbSelect = *paramTree.getRawParameterValue("reverb");
    auto& distSelect = *paramTree.getRawParameterValue("disttoggle");
    auto& filterSelect = *paramTree.getRawParameterValue("filtertoggle");
    auto& filterSelectHp = *paramTree.getRawParameterValue("filtertogglehp");



    if (distSelect == 1) {
        dist.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }
    if (filterSelect == 1) {
        lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }

    if (filterSelectHp == 1) {
        highPassFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }
    
    if (reverbSelect == 1) {
        reverb.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }

 


}

juce::AudioProcessorValueTreeState::ParameterLayout SynthJUCEAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>("oscType", "Oscillator", juce::StringArray{ "sine" , "square","saw" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.1f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.1f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float>{ 0.1f, 3.0f, 0.1f }, 0.4f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("fmdepth", "Fmdepth", juce::NormalisableRange<float>{ 10.0f, 500.0f, 1.0f }, 250.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("fmfreq", "Fmfreq", juce::NormalisableRange<float>{ 0.0f, 2000.0f, 1.0f }, 10.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("pregain", "PreGain", juce::NormalisableRange<float>{ 0.0f, 2.0f, 0.01f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("postgain", "PostGain", juce::NormalisableRange<float>{  0.0f, 2.0f, 0.01f }, 1.0f));


    params.push_back(std::make_unique<juce::AudioParameterFloat>("lpfcutoff", "LPFCutOff", juce::NormalisableRange<float>{ 100, 20000, 10 }, 200));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("hpfcutoff", "HPFCutOff", juce::NormalisableRange<float>{ 100, 10000, 10 }, 2000));



    auto attributes = juce::AudioParameterBoolAttributes().withStringFromValueFunction([](auto x, auto) { return x ? "On" : "Off"; }).withLabel("enabled");
    params.push_back(std::make_unique<juce::AudioParameterBool>("reverb", "Reverb", false, attributes));


    auto attributesdist = juce::AudioParameterBoolAttributes().withStringFromValueFunction([](auto x, auto) { return x ? "On" : "Off"; }).withLabel("enabled");
    params.push_back(std::make_unique<juce::AudioParameterBool>("disttoggle", "Disttoggle", false, attributesdist));



    auto attributesfilt = juce::AudioParameterBoolAttributes().withStringFromValueFunction([](auto x, auto) { return x ? "On" : "Off"; }).withLabel("enabled");
    params.push_back(std::make_unique<juce::AudioParameterBool>("filtertoggle", "FilterToggle", false, attributesfilt));

    auto attributesfilthp = juce::AudioParameterBoolAttributes().withStringFromValueFunction([](auto x, auto) { return x ? "On" : "Off"; }).withLabel("enabled");
    params.push_back(std::make_unique<juce::AudioParameterBool>("filtertogglehp", "FilterToggleHP", false, attributesfilthp));




    return { params.begin(), params.end() };
}

//==============================================================================
bool SynthJUCEAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthJUCEAudioProcessor::createEditor()
{
    return new SynthJUCEAudioProcessorEditor (*this);
}

//==============================================================================
void SynthJUCEAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthJUCEAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthJUCEAudioProcessor();
}
