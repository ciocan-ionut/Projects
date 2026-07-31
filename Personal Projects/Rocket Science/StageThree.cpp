#include "StageThree.h"
#include "FlightStats.h"

#include <iostream>

void StageThree::displayTravelInformation(Planet planet1, Planet planet2) {
	FlightStats stats = FlightStatsCalculator::calculateFlightStats(planet1, planet2, std::abs(planet1.orbRadius - planet2.orbRadius));
	int hours = static_cast<int>((stats.totalTime - stats.days * 60 * 60 * 24) / (60 * 60));
	int minutes = static_cast<int>((stats.totalTime - stats.days * 60 * 60 * 24 - hours * 60 * 60) / 60);
	double seconds = stats.totalTime - stats.days * 60 * 60 * 24 - hours * 60 * 60 - minutes * 60;

	std::cout << "It will take " << stats.timeToCruise << " seconds to reach cruising velocity" << std::endl;
	std::cout << "It will reach that velocity at a distance of " << stats.distanceToCruise << " km from the surface of the starting planet" << std::endl;
	std::cout << "It will cruise for " << stats.timeCruising << " seconds" << std::endl;
	std::cout << "It will start decelerating at a distance of " << stats.distanceToCruise << " km from the surface of the destination planet" << std::endl;
	std::cout << "It will take " << stats.timeToCruise << " seconds to decelerate to zero" << std::endl;
	std::cout << "Total travel time: " << stats.days << " days, " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds" << std::endl;
}