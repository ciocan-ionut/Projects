#include "CosActivitati.h"
#include <random>
#include <fstream>

void CosActivitati::deleteCos()
{
	cos.clear();
}

void CosActivitati::addActivitateInCos(const Activitate& a)
{
	cos.push_back(a);
}

void CosActivitati::exportCSV(const string& numeFisier) const
{
	ofstream fout(numeFisier);
	for(const auto& a : cos)
		fout << a.getTitlu() << "," << a.getDescriere() << "," << a.getTip() << "," << a.getDurata() << "\n";
	fout.close();
}

const vector<Activitate>& CosActivitati::getActivitatiCos() const
{
	return cos;
}