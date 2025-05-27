#include "Service.h"
#include <random>
#include <fstream>
#include <sstream>

bool Service::addService(const string& titlu, const string& descriere, const string& tip, const int& durata)
{
	Activitate a{ titlu, descriere, tip, durata };
	Validator::validateActivitate(a);
	repo.addActivitate(a);
	undoActions.push_back(make_unique<UndoAdauga>(repo));
	return true;
}

bool Service::deleteService(const int& index)
{
	if (index < 0 || index >= (int)repo.getActivitati().size())
		throw ServiceException("Index invalid!\n");
	Activitate a = repo.getActivitateByIndex(index);
	repo.deleteActivitateByIndex(index);
	undoActions.push_back(make_unique<UndoSterge>(repo, a));
	return true;
}

bool Service::modifyService(const int& index, string titlu, string descriere, string tip, int durata)
{
	if (index < 0 || index >= (int)repo.getActivitati().size())
		throw ServiceException("Index invalid!\n");
	int nemodificat = 0;
	if (titlu == "")
	{
		titlu = repo.getActivitateByIndex(index).getTitlu();
		nemodificat++;
	}
	if (descriere == "")
	{
		descriere = repo.getActivitateByIndex(index).getDescriere();
		nemodificat++;
	}
	if (tip == "")
	{
		tip = repo.getActivitateByIndex(index).getTip();
		nemodificat++;
	}
	if (durata <= 0)
	{
		durata = repo.getActivitateByIndex(index).getDurata();
		nemodificat++;
	}
	if (nemodificat != 4)
	{
		Activitate a{ titlu, descriere, tip, durata };
		Activitate act = repo.getActivitateByIndex(index);
		repo.modifyActivitateByIndex(index, a);
		undoActions.push_back(make_unique<UndoModifica>(repo, act, index));
	}
	else
		throw ServiceException("Activitatea nu a fost modificata!\n");
	return true;
}

const vector<Activitate>& Service::getActivitatiService() const
{
	if (repo.getActivitati().size() == 0)
		throw ServiceException("Nu exista activitati in lista ta!\n");
	return repo.getActivitati();
}

vector<Activitate> Service::filterService(function<string(const Activitate&)> getter, const string& filtru) const
{
	Validator::validateString(filtru);
	vector<Activitate> listaFiltrata;
	copy_if(repo.getActivitati().begin(), repo.getActivitati().end(), back_inserter(listaFiltrata), [getter, filtru](const Activitate& a)
		{
			return getter(a) == filtru;
		});
	if (listaFiltrata.size() == 0)
		throw ServiceException("Nu exista activitati care iti respecta criteriile!\n");
	return listaFiltrata;
}

vector<Activitate> Service::sortedService(function<bool(const Activitate&, const Activitate&, const bool&)> compare, const bool& ascending) const
{
	auto listaSortata = repo.getActivitati();
	sort(listaSortata.begin(), listaSortata.end(), [compare, ascending](const Activitate& a, const Activitate& b)
		{
			return compare(a, b, ascending);
		});
	return listaSortata;
}

void Service::emptyCos()
{
	cos.deleteCos();
	notifyObservers();
}

void Service::addInCos(const string& titlu)
{
	Validator::validateString(titlu);

	const auto& activitati = repo.getActivitati();
	auto it = find_if(activitati.begin(), activitati.end(), [&titlu](const Activitate& a)
		{
			return a.getTitlu() == titlu;
		});

	if (it == activitati.end())
		throw ServiceException("Nu exista activitate cu titlul dat!\n");

	cos.addActivitateInCos(*it);
	notifyObservers();
}

void Service::generateActivitati(int nr)
{
	if (nr <= 0)
		throw ServiceException("Introduceti un numar strict pozitiv!\n");

	while (repo.getActivitati().size() != 0)
		repo.deleteActivitateByIndex(0);

	vector<string> titluri = { "Curs", "Sport", "Citit", "Muzica", "Curatenie", "Proiect", "Film", "Gatit" };
	vector<string> descrieri = { "Activitate relaxanta", "Foarte important", "Timp liber", "Deadline urgent", "Cu prietenii" };
	vector<string> tipuri = { "educatie", "recreativ", "munca", "familie", "dezvoltare" };

	default_random_engine gen(random_device{}());
	uniform_int_distribution<int> distTitlu(0, (int)titluri.size() - 1);
	uniform_int_distribution<int> distDescriere(0, (int)descrieri.size() - 1);
	uniform_int_distribution<int> distTip(0, (int)tipuri.size() - 1);
	uniform_int_distribution<int> distDurata(1, 200);

	for (int i = 0; i < nr; i++)
	{
		string titlu = titluri[distTitlu(gen)] + to_string(i);
		string descriere = descrieri[distDescriere(gen)];
		string tip = tipuri[distTip(gen)];
		int durata = distDurata(gen);

		repo.addActivitate(Activitate{ titlu, descriere, tip, durata });
	}
	notifyObservers();
}

void Service::exportCosCSV(const string& fisier) const
{
	if (cos.getActivitatiCos().size() == 0)
		throw ServiceException("Nu exista activitati in cosul tau!\n");
	cos.exportCSV(fisier);
}

const vector<Activitate>& Service::getActivitatiCosService() const
{
	if (cos.getActivitatiCos().size() == 0)
		throw ServiceException("Nu exista activitati in cosul tau!\n");
	return cos.getActivitatiCos();
}

map<string, DTO> Service::createMap()
{
	if (repo.getActivitati().size() == 0)
		throw ServiceException("Nu exista activitati in lista ta!\n");

	raport.clear();
	for (const auto& a : repo.getActivitati())
	{
		string tip = a.getTip();
		auto it = raport.find(tip);
		if (it != raport.end())
			it->second.add();
		else
			raport.insert({ tip, DTO{ tip } });
	}

	return raport;
}

void Service::saveToFile()
{
	ofstream fout("repository.txt");
	const auto& activitati = repo.getActivitati();
	for (const auto& a : activitati)
		fout << a.getTitlu() << ',' << a.getDescriere() << ',' << a.getTip() << ',' << a.getDurata() << endl;
	fout.close();
}

void Service::loadFromFile()
{
	ifstream fin("repository.txt");
	string line, titlu, descriere, tip, duratastring;
	int durata;
	while (getline(fin, line))
	{
		stringstream ss(line);
		getline(ss, titlu, ',');
		getline(ss, descriere, ',');
		getline(ss, tip, ',');
		getline(ss, duratastring, ',');
		durata = stoi(duratastring);
		Activitate a{ titlu, descriere, tip, durata };
		repo.addActivitate(a);
	}
}

void Service::undo()
{
	if (undoActions.empty())
		throw ServiceException("Nu mai exista operatii pentru undo!\n");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}