#pragma once

#include "Activitate.h"
#include "BaseException.h"
#include <string>
using std::string;

class ValidatorException : public BaseException
{
public:
	explicit ValidatorException(string msg) : BaseException(msg) {}
};

class Validator
{
public:
	/// Functie care verifica daca o activitate este valida (titlu != "" / descriere != "" / tip != "" / durata > 0)
	/// @param activity este activitatea verificata
	/// @returns True (daca activitatea este valida)
	/// @throw ValidatorException cu unul sau mai multe dintre mesajele:
	/// @throw "Nu ati introdus niciun titlu!" (titlul este un sir gol)
	/// @throw "Nu ati introdus nicio descriere!" (descrierea este un sir gol)
	/// @throw "Nu ati introdus niciun tip!" (tipul este un sir gol)
	/// @throw "Durata trebuie sa fie un numar strict pozitiv!" (durata este un numar mai mic sau egal cu 0)
	bool static validateActivitate(const Activitate& activity);

	/// Functie care verifica daca un string este valid (string != "")
	/// @param string este sirul de caractere verificat
	/// @returns True (daca string-ul este valid)
	/// @throw ValidatorException cu mesajul "Nu ati introdus nimic!" (string-ul este un sir gol)
	bool static validateString(const string& string);
};

