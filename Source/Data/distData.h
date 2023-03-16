/*
  ==============================================================================

    distData.h
    Created: 13 Oct 2022 3:53:12pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class Distortion {
public:

    Distortion::Distortion() {
        auto& waveshaper = processorChain.template get<waveshaperIndex>();
        waveshaper.functionToUse = [](float x)
        {
            return std::tanh(x);           // [4]
        };

                             // [8]
    }

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        processorChain.process(context);
    }

    void reset() noexcept
    {
        processorChain.reset();
    };

    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        processorChain.prepare(spec);
    };

    void setDistParameters(float prgain, float pogain) {
       // preGainParam = prgain;
       // postGainParam = pogain;



        auto& preGain = processorChain.template get<preGainIndex>();   // [5]
        preGain.setGainLinear(prgain);                               // [6]

        auto& postGain = processorChain.template get<postGainIndex>(); // [7]
        postGain.setGainLinear(pogain);


    }

private:
    enum
    {
        preGainIndex,    // [2]
        waveshaperIndex,
        postGainIndex    // [3]
    };


    juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float>, juce::dsp::Gain<float>> processorChain; // [1]

    float preGainParam;
    float postGainParam;

};

   
