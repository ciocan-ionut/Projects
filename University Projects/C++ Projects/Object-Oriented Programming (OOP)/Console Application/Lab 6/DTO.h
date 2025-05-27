#pragma once

#include <string>
#include "Activitate.h"
using namespace std;

class DTO
{
private:
	string tip;
	int cantitate;

public:
	DTO(const string& tip) : tip{ tip }, cantitate{ 1 } {}

	/// Functie care returneaza tipul unui obiect DTO
	/// @returns tipul obiectului DTO
	const string& getTip() const
	{
		return tip;
	}

	/// Functie care returneaza cantitatea unui obiect DTO
	/// @returns cantitatea obiectului DTO
	int getCantitate() const
	{
		return cantitate;
	}

	/// Functie care creste cantitatea unui obiect DTO
	void add()
	{
		cantitate++;
	}
};

