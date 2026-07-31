#include "FlightStats.h"

FlightStats FlightStatsCalculator::calculateFlightStats(const Planet& source, const Planet& destination, double distance) {
	double timeToCruise, distanceToCruise, maxVelocity;
	if (source.velocity > destination.velocity) {
		timeToCruise = source.timeToEscape;
		distanceToCruise = source.distanceToEscape;
		maxVelocity = source.velocity;
	}
	else {
		timeToCruise = destination.timeToEscape;
		distanceToCruise = destination.distanceToEscape;
		maxVelocity = destination.velocity;
	}
	double totalDistance = distance - 2 * distanceToCruise - (source.diameter + destination.diameter) / 2000;
	double timeCruising = 1000 * totalDistance / maxVelocity;
	double totalTime = 2 * timeToCruise + timeCruising;
	int days = static_cast<int>(totalTime / (60 * 60 * 24));
	return { timeToCruise, distanceToCruise, maxVelocity, timeCruising, totalDistance, totalTime, days };
}