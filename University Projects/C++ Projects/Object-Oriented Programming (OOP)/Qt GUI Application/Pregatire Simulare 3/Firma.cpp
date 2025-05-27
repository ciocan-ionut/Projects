#include "Firma.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Firma::loadFromFile()
{
	devices.clear();
	ifstream fin(numeFisier);
	while (fin)
	{
		string line;
		getline(fin, line);
		if (line.empty())
			break;
		stringstream ss(line);
		string tip, model, culoare, anString, pretString;
		int an;
		double pret;
		getline(ss, tip, ',');
		getline(ss, model, ',');
		getline(ss, anString, ',');
		getline(ss, culoare, ',');
		getline(ss, pretString, ',');
		an = stoi(anString);
		pret = stod(pretString);
		Device device(tip, model, an, culoare, pret);
		devices.push_back(device);
	}
	fin.close();
}

vector<Device> Firma::getDevices()
{
	return devices;
}

vector<Device> Firma::sortModel()
{
	auto devicesSorted = devices;
	sort(devicesSorted.begin(), devicesSorted.end(), [](const Device& a, const Device& b) {
		return a.getModel() < b.getModel();
		});
	return devicesSorted;
}

vector<Device> Firma::sortAn()
{
	auto devicesSorted = devices;
	sort(devicesSorted.begin(), devicesSorted.end(), [](const Device& a, const Device& b) {
		return a.getAn() < b.getAn();
		});
	return devicesSorted;
}