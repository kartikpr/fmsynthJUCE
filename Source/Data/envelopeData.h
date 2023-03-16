/*
  ==============================================================================

    envelopeData.h
    Created: 11 Oct 2022 3:30:20pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class envData : public juce::ADSR {
private:
    juce::ADSR::Parameters envelopeParameters;
    

public:
   void updateEnvelope(const float a, const float d, const float s, const float r);


};
