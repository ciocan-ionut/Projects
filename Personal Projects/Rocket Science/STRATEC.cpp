#include "StageOne.h"
#include "StageTwo.h"
#include "StageThree.h"
#include "StageFour.h"
#include "StageFive.h"
#include "Planet.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <unordered_map>

struct Rocket {
	int rocketEngines;
	double acceleration;
};

std::vector<std::string> planetOrder;
std::unordered_map<std::string, Planet> planetMap;
Rocket rocket;

void readPlanetData(const std::string& planetFile, const std::string& solarSystemFile) {
	std::ifstream planetFin(planetFile);
	if (!planetFin.is_open()) {
		std::cerr << "Error opening file: " << planetFile << std::endl;
		return;
	}

	std::ifstream solarSystemFin(solarSystemFile);
	if (!solarSystemFin.is_open()) {
		std::cerr << "Error opening file: " << solarSystemFile << std::endl;
		return;
	}

	std::regex planetPattern(R"(^([a-zA-Z]+): diameter = ([0-9]+) km, mass = ([0-9]*\.?[0-9]+).*)");
	std::regex solarSystPattern(R"(^([a-zA-Z]+): period = ([0-9]+) days, orbital radius = ([0-9]*\.?[0-9]+) AU)");

	std::string planetFileLine, solarSystFileLine;
	while (std::getline(planetFin, planetFileLine) && std::getline(solarSystemFin, solarSystFileLine)) {
		std::smatch planetMatches, solarSystMatches;
		if (std::regex_match(planetFileLine, planetMatches, planetPattern) && 
			std::regex_match(solarSystFileLine, solarSystMatches, solarSystPattern)) {
			std::string name = planetMatches[1];
			double diameter = std::stod(planetMatches[2]) * 1000; // Convert km to m
			double mass = std::stod(planetMatches[3]);
			double period = std::stod(solarSystMatches[2]);
			double orbRadius = std::stod(solarSystMatches[3]) * 149597870.7; // Convert AU to km
			if (name == "Earth") {
				mass = 1;
			}
			planetOrder.push_back(name);
			planetMap[name] = { name, diameter, mass, 0.0, 0.0, 0.0, period, orbRadius };
		}
		else {
			std::cerr << "Line format is incorrect: " << planetFileLine << std::endl;
		}
	}

	planetFin.close();
}

void readRocketData(const std::string& filename) {
	std::ifstream fin(filename);

	if (!fin.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::regex pattern(R"(Number of rocket engines: ([0-9]+)\nAcceleration per engine: ([0-9]*\.?[0-9]+) m/s\^2)");

	std::stringstream buffer;
	buffer << fin.rdbuf();
	std::string text = buffer.str();
	std::smatch matches;
	if (std::regex_search(text, matches, pattern)) {
		rocket.rocketEngines = std::stoi(matches[1]);
		rocket.acceleration = std::stod(matches[2]);
	}
	else {
		std::cerr << "File format is incorrect: " << filename << std::endl;
	}

	fin.close();
}

void calculatePlanetData() {
	for (auto& [name, planet] : planetMap) {
		planet.velocity = StageOne::calculateVelocity(planet.diameter, planet.mass);
		planet.timeToEscape = StageTwo::calculateTimeToEscape(planet.velocity, rocket.rocketEngines, rocket.acceleration);
		planet.distanceToEscape = StageTwo::calculateDistanceToEscape(planet.timeToEscape, rocket.rocketEngines, rocket.acceleration);
	}
}

void displayMenu() {
	std::cout << "Choose your options:" << std::endl;
	std::cout << "1. Display all planets data" << std::endl;
	std::cout << "2. Choose planets to calculate distance" << std::endl;
	std::cout << "3. Choose a day to calculate planet angles" << std::endl;
	std::cout << "4. Choose planets to calculate distance after 100 years" << std::endl;
	std::cout << "5. Choose planets to calculate distance after 100 years with movement" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void displayPlanetData() {
	for (auto& [name, planet] : planetMap) {
		std::cout << "Planet: " << planet.name << std::endl;
		std::cout << "Escape Velocity: " << planet.velocity << " m/s" << std::endl;
		std::cout << "Time to Escape: " << planet.timeToEscape << " seconds" << std::endl;
		std::cout << "Distance to Escape: " << planet.distanceToEscape << " km" << std::endl;
		std::cout << "-----------------------------" << std::endl;
	}
}

void displayDistanceBetweenPlanets() {
	std::string planet1, planet2;
	while (true) {
		std::cout << "Enter the names of two planets, separated by space (ex. Earth Mars): ";
		std::cin >> planet1 >> planet2;
		if (planetMap.contains(planet1) && planetMap.contains(planet2))
			break;
	}
	StageThree::displayTravelInformation(planetMap[planet1], planetMap[planet2]);
}

void displayPlanetAnglesOnSpecificDay() {
	int day;
	while (true) {
		std::cout << "Enter a valid day: ";
		std::cin >> day;
		if (day >= 1)
			break;
	}

	for (const auto& [name, planet] : planetMap) {
		double angle = StageFour::calculatePlanetAngle(planet.period, day);
		std::cout << name << "'s angular position on day " << day << " is " << angle << " degrees" << std::endl;
	}
}

void displayDistanceBetweenAngledPlanets() {
	std::string planet1, planet2;
	while (true) {
		std::cout << "Enter the names of two planets, separated by space (ex. Earth Mars): ";
		std::cin >> planet1 >> planet2;
		if (planetMap.contains(planet1) && planetMap.contains(planet2))
			break;
	}
	StageFive stageFive(planetMap[planet1], planetMap[planet2], planetMap, planetOrder);
	stageFive.calculateOptimalStartDayAndDistanceV(planetMap[planet1], planetMap[planet2]);
}

void displayDistanceBetweenAngledPlanetsMoving() {
	std::string planet1, planet2;
	while (true) {
		std::cout << "Enter the names of two planets, separated by space (ex. Earth Mars): ";
		std::cin >> planet1 >> planet2;
		if (planetMap.contains(planet1) && planetMap.contains(planet2))
			break;
	}
	StageFive stageFive(planetMap[planet1], planetMap[planet2], planetMap, planetOrder);
	stageFive.calculateOptimalStartDayAndDistanceVI(planetMap[planet1], planetMap[planet2]);
}

int main()
{
	std::string planetDataFile = "Planetary_Data.txt";
	std::string rocketDataFile = "Rocket_Data.txt";
	std::string solarSystemDataFile = "Solar_System_Data.txt";

	readPlanetData(planetDataFile, solarSystemDataFile);
	readRocketData(rocketDataFile);
	calculatePlanetData();

	while (true) {
		displayMenu();
		int choice;
		std::cout << ">> ";
		std::cin >> choice;
		switch (choice) {
		case 0:
			std::cout << "Exiting program." << std::endl;
			return 0;
		case 1:
			displayPlanetData();
			break;
		case 2:
			displayDistanceBetweenPlanets();
			break;
		case 3:
			displayPlanetAnglesOnSpecificDay();
			break;
		case 4:
			displayDistanceBetweenAngledPlanets();
			break;
		case 5:
			displayDistanceBetweenAngledPlanetsMoving();
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
			break;
		}
	}
}
