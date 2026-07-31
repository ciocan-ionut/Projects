#include "StageFour.h"

#include <cmath>

double StageFour::calculatePlanetAngle(double fullRotationTime, double day) {
	double angle = (360 / fullRotationTime) * day;
	return std::fmod(angle, 360);
}