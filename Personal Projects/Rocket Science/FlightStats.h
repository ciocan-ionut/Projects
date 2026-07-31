#pragma once

#include "Planet.h"

struct FlightStats {
	double timeToCruise;
	double distanceToCruise;
	double maxVelocity;
	double timeCruising;
	double totalDistance;
	double totalTime;
	int days;
};

class FlightStatsCalculator {
public:
	static FlightStats calculateFlightStats(const Planet& source, const Planet& destination, double distance);
};