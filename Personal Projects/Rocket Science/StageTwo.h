#pragma once

class StageTwo {
public:
	static double calculateTimeToEscape(double escapeVelocity, int rocketEngines, double acceleration);

	static double calculateDistanceToEscape(double timeToEscape, int rocketEngines, double acceleration);
};