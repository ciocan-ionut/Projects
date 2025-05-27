#pragma once

#include <string>

using namespace std;

class Device
{
private:
	string tip, model, culoare;
	int an;
	double pret;

public:
	Device(string tip, string model, int an, string culoare, double pret) : tip{ tip }, model{ model }, an{ an }, culoare{ culoare }, pret{ pret } {}
	string getTip() const;
	string getModel() const;
	int getAn() const;
	string getCuloare() const;
	double getPret() const;
};

