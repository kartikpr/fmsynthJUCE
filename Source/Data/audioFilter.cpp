/*
  ==============================================================================

    audioFilter.cpp
    Created: 26 Oct 2022 4:42:44pm
    Author:  user

  ==============================================================================
*/

#include "audioFilter.h"
#define _USE_MATH_DEFINES
#include <memory>
#include <math.h>
#include <cmath>
#include <iostream>
#include<numbers>
using namespace std;

void audioFilter::setSampleRate(double sampleRate) {
	filterSampleRate = sampleRate;
}

void audioFilter::setParameters(double fc, double fb, double gain, std::string type) {
	centerFrequency = fc;
	bandwidthFrequency = fb;
	filterGain = gain;
	filterAlgorithm = type;
	calculateFilterCoeffs();
}

void audioFilter::calculateFilterCoeffs() {
	memset(&coeffArray[0], 0, sizeof(double) * 7);
	double V;



	if (filterAlgorithm == "lowshelf") {
		V = pow(10, filterGain / 20);
		coeffArray[0] = V - 1;
		if (filterGain > 0)
			coeffArray[1] = (tan(M_PI * (centerFrequency / filterSampleRate) / 2) - 1) / (tan(M_PI * (centerFrequency / filterSampleRate) / 2) + 1);
		else if (filterGain < 0)
			coeffArray[1] = (tan(M_PI * (centerFrequency / filterSampleRate) / 2) - V) / (tan(M_PI * (centerFrequency / filterSampleRate) / 2) + V);
	}
	else if (filterAlgorithm == "highshelf")
	{
		V = pow(10, filterGain / 20);
		coeffArray[0] = V - 1;
		if (filterGain > 0)
			coeffArray[1] = (tan(M_PI * (centerFrequency / filterSampleRate) / 2) - 1) / (tan(M_PI * (centerFrequency / filterSampleRate) / 2) + 1);
		else if (filterGain < 0)
			coeffArray[1] = (V * tan(M_PI * (centerFrequency / filterSampleRate) / 2) - 1) / (V * tan(M_PI * (centerFrequency / filterSampleRate) / 2) + 1);


	}
	else if (filterAlgorithm == "lowpass") {
		coeffArray[1] = (tan(M_PI * (centerFrequency / filterSampleRate) / 2) - 1) / (tan(M_PI * (centerFrequency / filterSampleRate) / 2) + 1);

	}
	else if (filterAlgorithm == "highpass") {

		coeffArray[1] = (tan(M_PI * (centerFrequency / filterSampleRate) / 2) - 1) / (tan(M_PI * (centerFrequency / filterSampleRate) / 2) + 1);

	}
	else if (filterAlgorithm == "peak") {

		V = pow(10, filterGain / 20);
		coeffArray[0] = V - 1;
		coeffArray[2] = -cos(M_PI * (centerFrequency / filterSampleRate));

		if (filterGain > 0)
			coeffArray[1] = (tan(M_PI * (bandwidthFrequency / filterSampleRate) / 2) - 1) / (tan(M_PI * (bandwidthFrequency / filterSampleRate) / 2) + 1);
		else if (filterGain < 0)
			coeffArray[1] = (tan(M_PI * (bandwidthFrequency / filterSampleRate) / 2) - V) / (tan(M_PI * (bandwidthFrequency / filterSampleRate) / 2) + V);

	}
}


double audioFilter::processAudioSample(double x) {
	double xh;
	double y;
	double y1;
	if (filterAlgorithm == "lowshelf") {

		xh = x - coeffArray[1] * xh_old;
		y1 = coeffArray[1] * xh + xh_old;
		y = coeffArray[0] / 2 * (x + y1) + x;
		xh_old = xh;


	}
	else if (filterAlgorithm == "highshelf")
	{

		xh = x - coeffArray[1] * xh_old;
		y1 = coeffArray[1] * xh + xh_old;
		y = coeffArray[0] / 2 * (x - y1) + x;
		xh_old = xh;

	}
	else if (filterAlgorithm == "lowpass") {
		xh = x - (coeffArray[1] * xh_old);
		y1 = coeffArray[1] * xh + (xh_old);
		y = 0.5 * (x + y1);
		xh_old = xh;

	}
	else if (filterAlgorithm == "highpass") {
		xh = x - coeffArray[1] * xh_old;
		y1 = coeffArray[1] * xh + xh_old;
		y = 0.5 * (x - y1);
		xh_old = xh;

	}
	else if (filterAlgorithm == "peak") {

		xh = x - coeffArray[2] * (1 - coeffArray[1]) * xh_old + (coeffArray[1]) * xh_old_old;
		y1 = (-1 * coeffArray[1]) * xh + coeffArray[2] * (1 - coeffArray[1]) * xh_old + xh_old_old;
		y = coeffArray[0] / 2 * (x - y1) + x;
		xh_old_old = xh_old;
		xh_old = xh;


	}

	return y;

}