#include "StageOne.h"

#include <cmath>

double StageOne::calculateVelocity(double diameter, double mass) {
	double velocity = std::sqrt(4 * (G * mass * earthMass) / diameter);
	return std::round(velocity);
}