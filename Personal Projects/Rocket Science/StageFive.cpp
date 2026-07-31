#include "StageFive.h"
#include "StageFour.h"

#include <iostream>
#include <limits>
#include <numbers>

bool StageFive::isRocketPathObstructed(Coordinates source, Coordinates destination, const Planet& planet, int startDay, int flightDuration) {
	for (int day = startDay; day < startDay + flightDuration; day++) {
		double planetAngle = StageFour::calculatePlanetAngle(planet.period, day) * std::numbers::pi / 180;
		double planetX = planet.orbRadius * cos(planetAngle);
		double planetY = planet.orbRadius * sin(planetAngle);

		double t = static_cast<double>(day - startDay) / flightDuration;
		double rocketX = source.x + t * (destination.x - source.x);
		double rocketY = source.y + t * (destination.y - source.y);
		double distanceFromRocketToPlanet = std::sqrt(std::pow(rocketX - planetX, 2) + std::pow(rocketY - planetY, 2));

		if (distanceFromRocketToPlanet <= planet.diameter / 2000) {
			return true;
		}
	}
	return false;
}

void StageFive::calculateCoordinates(const std::unordered_map<std::string, Planet>& planetMap) {
	for (const auto& [name, planet] : planetMap) {
		double angle = StageFour::calculatePlanetAngle(planet.period, 100 * 365) * std::numbers::pi / 180;
		double x = planet.orbRadius * cos(angle);
		double y = planet.orbRadius * sin(angle);
		planetCoordinates[name] = { x, y };
	}
}

void StageFive::determinePlanetOrder(const std::vector<std::string>& planetOrder) {
	bool sourceFound = false, destinationFound = false;
	for (int i = 0; i < planetOrder.size(); i++) {
		if (planetOrder[i] == destination.name && !sourceFound) {
			std::swap(source, destination);
		}
		if (planetOrder[i] == source.name) {
			sourceFound = true;
			while (!destinationFound) {
				planetsInOrder.push_back(planetMap.at(planetOrder[i]));
				if (planetOrder[i] == destination.name) {
					destinationFound = true;
				}
				i++;
			}
		}
	}
}

bool StageFive::isPlanetObstructingPath(Coordinates sourceCoords, Coordinates destCoords, Coordinates planetCoords, double planetDiameter) {	
	double lineEcuation = (destCoords.x - sourceCoords.x) * (planetCoords.y - sourceCoords.y) - 
		(destCoords.y - sourceCoords.y) * (planetCoords.x - sourceCoords.x);
	double distanceFromSourceToDest = std::sqrt(std::pow(destCoords.x - sourceCoords.x, 2) + std::pow(destCoords.y - sourceCoords.y, 2));
	double distanceFromPlanetToLine = std::abs(lineEcuation) / distanceFromSourceToDest;
	return distanceFromPlanetToLine <= planetDiameter / 2000;
}

void StageFive::calculateOptimalStartDayAndDistanceV(Planet source, Planet destination) {
	constexpr double MAX_DISTANCE = std::numeric_limits<double>::max();
	double minDistance = MAX_DISTANCE;
	int optimalStartDay = 0;
	for (int day = 100 * 365; day < 110 * 365; ++day) {
		double sourceAngle = StageFour::calculatePlanetAngle(source.period, day) * std::numbers::pi / 180;
		double destAngle = StageFour::calculatePlanetAngle(destination.period, day) * std::numbers::pi / 180;
		
		double sourceX = source.orbRadius * cos(sourceAngle);
		double sourceY = source.orbRadius * sin(sourceAngle);
		double destX = destination.orbRadius * cos(destAngle);
		double destY = destination.orbRadius * sin(destAngle);
		
		bool pathObstructed = false;
		for (const auto& planet : planetsInOrder) {
			if (planet.name != source.name && planet.name != destination.name) {
				double planetAngle = StageFour::calculatePlanetAngle(planet.period, day) * std::numbers::pi / 180;
				double planetX = planet.orbRadius * cos(planetAngle);
				double planetY = planet.orbRadius * sin(planetAngle);

				if (isPlanetObstructingPath({ sourceX, sourceY }, { destX, destY }, { planetX, planetY }, planet.diameter)) {
					pathObstructed = true;
					break;
				}
			}
		}

		if (pathObstructed) {
			continue;
		}

		double distance = std::sqrt(std::pow(destX - sourceX, 2) + std::pow(destY - sourceY, 2));
		
		if (distance < minDistance) {
			minDistance = distance;
			optimalStartDay = day;
		}
	}

	FlightStats stats = FlightStatsCalculator::calculateFlightStats(source, destination, minDistance);
	displayTravelInformation(optimalStartDay, minDistance, stats);
}

void StageFive::calculateOptimalStartDayAndDistanceVI(Planet source, Planet destination) {
	constexpr double MAX_DISTANCE = std::numeric_limits<double>::max();
	double minDistance = MAX_DISTANCE;
	int optimalStartDay = 0;
	for (int day = 100 * 365; day < 110 * 365; ++day) {
		double sourceAngle = StageFour::calculatePlanetAngle(source.period, day) * std::numbers::pi / 180;
		double destAngle = StageFour::calculatePlanetAngle(destination.period, day) * std::numbers::pi / 180;

		double sourceX = source.orbRadius * cos(sourceAngle);
		double sourceY = source.orbRadius * sin(sourceAngle);
		double destX = destination.orbRadius * cos(destAngle);
		double destY = destination.orbRadius * sin(destAngle);

		double distance = std::sqrt(std::pow(destX - sourceX, 2) + std::pow(destY - sourceY, 2));

		FlightStats stats = FlightStatsCalculator::calculateFlightStats(source, destination, distance);

		bool pathObstructed = false;
		for (const auto& planet : planetsInOrder) {
			if (planet.name != source.name && planet.name != destination.name) {
				if (isRocketPathObstructed({ sourceX, sourceY }, { destX, destY }, planet, day, stats.days)) {
					pathObstructed = true;
					break;
				}
			}
		}

		if (pathObstructed) {
			continue;
		}

		if (distance < minDistance) {
			minDistance = distance;
			optimalStartDay = day;
		}
	}

	FlightStats stats = FlightStatsCalculator::calculateFlightStats(source, destination, minDistance);
	displayTravelInformation(optimalStartDay, minDistance, stats);
}

void StageFive::displayTravelInformation(int startDay, double distance, FlightStats stats) {
	if (distance == std::numeric_limits<double>::max()) {
		std::cout << "No valid path found within the given time frame." << std::endl;
		return;
	}

	int hours = static_cast<int>((stats.totalTime - stats.days * 60 * 60 * 24) / (60 * 60));
	int minutes = static_cast<int>((stats.totalTime - stats.days * 60 * 60 * 24 - hours * 60 * 60) / 60);
	double seconds = stats.totalTime - stats.days * 60 * 60 * 24 - hours * 60 * 60 - minutes * 60;

	std::cout << "It will take " << stats.timeToCruise << " seconds to reach cruising velocity" << std::endl;
	std::cout << "It will reach that velocity at a distance of " << stats.distanceToCruise << " km from the surface of the starting planet" << std::endl;
	std::cout << "It will cruise for " << stats.timeCruising << " seconds" << std::endl;
	std::cout << "It will start decelerating at a distance of " << stats.distanceToCruise << " km from the surface of the destination planet" << std::endl;
	std::cout << "It will take " << stats.timeToCruise << " seconds to decelerate to zero" << std::endl;
	std::cout << "Total travel time: " << stats.days << " days, " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds" << std::endl;
	std::cout << "------------------------------" << std::endl;

	displayPlanetAngles(startDay);
	std::cout << "------------------------------" << std::endl;

	std::cout << "The optimal start window is year " << startDay / 365 << " and day " << startDay % 365 << " with the distance " << distance << std::endl;
}

void StageFive::displayPlanetAngles(int day) {
	for (const auto& [name, planet] : planetMap) {
		double angle = StageFour::calculatePlanetAngle(planet.period, day);
		std::cout << name << "'s angular position on day " << day << " is " << angle << " degrees" << std::endl;
	}
}