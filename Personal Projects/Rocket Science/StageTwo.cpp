#include "StageTwo.h"

#include <fstream>
#include <iostream>

double StageTwo::calculateTimeToEscape(double escapeVelocity, int rocketEngines, double acceleration) {
	if (rocketEngines <= 0 || acceleration <= 0) {
		std::cerr << "Invalid rocket data!" << std::endl;
		return -1;
	}

	double totalAcceleration = rocketEngines * acceleration;
	double timeToEscape = escapeVelocity / totalAcceleration;
	return std::round(timeToEscape);
}

double StageTwo::calculateDistanceToEscape(double timeToEscape, int rocketEngines, double acceleration) {
	if (rocketEngines <= 0 || acceleration <= 0) {
		std::cerr << "Invalid rocket data!" << std::endl;
		return -1;
	}
	double totalAcceleration = rocketEngines * acceleration;
	double distanceToEscape = 0.5 * totalAcceleration * timeToEscape * timeToEscape;
	return std::round(distanceToEscape / 1000);
}