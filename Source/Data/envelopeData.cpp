/*
  ==============================================================================

    envelopeData.cpp
    Created: 11 Oct 2022 3:30:20pm
    Author:  user

  ==============================================================================
*/

#include "envelopeData.h"

void envData::updateEnvelope(const float a, const float d, const float s, const float r) {
    envelopeParameters.attack = a;
    envelopeParameters.decay = d;
    envelopeParameters.sustain = s;
    envelopeParameters.release = r;
    setParameters(envelopeParameters);
}
