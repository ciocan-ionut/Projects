#pragma once

#include <vector>

using namespace std;

class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() = default;
};

class Observable
{
	vector<Observer*> observers;
public:

	/// Functie care adauga un observator in lista de observatori
	/// @param obs este observatorul care va fi adaugat
	void addObserver(Observer* obs) 
	{
		observers.push_back(obs);
	}

	/// Functie care sterge un observator din lista de observatori
	/// @param obs este observatorul care va fi sters
	void removeObserver(Observer* obs) 
	{
		auto it = std::remove(observers.begin(), observers.end(), obs);
		observers.erase(it, observers.end());
	}
protected:

	/// Functie care notifica toti observatorii ca s-a schimbat starea
	void notifyObservers() 
	{
		for (auto& obs : observers)
			obs->update();
	}
};