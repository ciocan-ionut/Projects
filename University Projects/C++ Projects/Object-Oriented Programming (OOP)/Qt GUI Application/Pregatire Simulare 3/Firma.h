#pragma once

#include <vector>
#include "Device.h"

class Firma
{
private:
	vector<Device> devices;
	string numeFisier;

public:
	Firma(string numeFisier) : numeFisier{ numeFisier } 
	{
		loadFromFile();
	}
	void loadFromFile();
	vector<Device> getDevices();
	vector<Device> sortModel();
	vector<Device> sortAn();
};

