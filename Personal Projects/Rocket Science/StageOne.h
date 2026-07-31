#pragma once

class StageOne {
private:
	static constexpr double G = 6.67e-11;
	static constexpr double earthMass = 6e24;
public:
	static double calculateVelocity(double diameter, double mass);
};