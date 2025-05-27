#include "Jocuri.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Jocuri::loadFromFile()
{
	ifstream fin(numeFisier);
	while (fin)
	{
		string line;
		getline(fin, line);
		if (line.empty())
			break;
		stringstream ss(line);
		string titlu, platforma, pretString, ratingString;
		double pret;
		int rating;
		getline(ss, titlu, ',');
		getline(ss, pretString, ',');
		getline(ss, platforma, ',');
		getline(ss, ratingString, ',');
		pret = stod(pretString);
		rating = stoi(ratingString);
		Joc joc(titlu, platforma, pret, rating);
		jocuri.push_back(joc);
	}
	fin.close();
}

vector<Joc> Jocuri::getJocuri()
{
	return jocuri;
}

vector<Joc> Jocuri::sortJocuri()
{
	auto jocuriSorted = jocuri;
	sort(jocuriSorted.begin(), jocuriSorted.end(), [](const Joc& a, const Joc& b) {
		return a.getPret() < b.getPret();
		});
	return jocuriSorted;
}

vector<Joc> Jocuri::filterJocuri()
{
	auto jocuriFiltered = jocuri;
	jocuriFiltered.erase(remove_if(jocuriFiltered.begin(), jocuriFiltered.end(), [](const Joc& joc) {
		return joc.getRating() >= 12;
		}), jocuriFiltered.end());
	return jocuriFiltered;
}