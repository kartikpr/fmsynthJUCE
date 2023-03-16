/*
  ==============================================================================

    audioFilter.h
    Created: 26 Oct 2022 4:42:44pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <string>

class audioFilter
{

public:
	audioFilter() {};
	~audioFilter() {};
	audioFilter(const audioFilter& audioFilter) = default;

	void setSampleRate(double sampleRate);
	void setParameters(double fc, double fb, double gain, std::string type);
	double processAudioSample(double sample);
	void calculateFilterCoeffs();


protected:
	double centerFrequency;
	double bandwidthFrequency;
	double filterGain;
	double filterSampleRate;
	std::string filterAlgorithm;
	double xh_old = 0;
	double xh_old_old = 0;
	double coeffArray[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; ///< our local copy of biquad coeffs

};
