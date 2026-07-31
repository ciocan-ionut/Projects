#pragma once

#include <string>

struct Planet {
	std::string name;
	double diameter; // m
	double mass; // kg
	double velocity; // km/s
	double timeToEscape; // s
	double distanceToEscape; // km
	double period; // days
	double orbRadius; // km
};