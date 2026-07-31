#pragma once

#include "Planet.h"
#include "Coordinates.h"
#include "FlightStats.h"

#include <string>
#include <unordered_map>
#include <vector>

class StageFive {
private:
	Planet source, destination;
	std::unordered_map<std::string, Planet> planetMap;
	std::unordered_map<std::string, Coordinates> planetCoordinates;
	std::vector<Planet> planetsInOrder;

	void calculateCoordinates(const std::unordered_map<std::string, Planet>& planetMap);

	void determinePlanetOrder(const std::vector<std::string>& planetOrder);

	bool isPlanetObstructingPath(Coordinates sourceCoords, Coordinates destCoords, Coordinates planetCoords, double planetDiameter);

	void displayTravelInformation(int startDay, double distance, FlightStats stats);

	void displayPlanetAngles(int day);

	bool isRocketPathObstructed(Coordinates source, Coordinates destination, const Planet& planet, int startDay, int flightDuration);
public:
	StageFive(Planet source, Planet destination, std::unordered_map<std::string, Planet> planetMap, std::vector<std::string> planetOrder) : source(source), destination(destination), planetMap(planetMap) {
		calculateCoordinates(planetMap);
		determinePlanetOrder(planetOrder);
	}

	void calculateOptimalStartDayAndDistanceV(Planet source, Planet destination);

	void calculateOptimalStartDayAndDistanceVI(Planet source, Planet destination);
};