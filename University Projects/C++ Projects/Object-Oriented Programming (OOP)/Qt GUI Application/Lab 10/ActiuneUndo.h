#pragma once

#include "RepositoryAbstract.h"

/// Clasa abstracta ActiuneUndo
class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo
{
private:
	RepositoryAbstract& repo;

public:
	UndoAdauga(RepositoryAbstract& repo) : repo{ repo } {}

	/// Functie care executa operatia de undo pentru adaugarea unei activitati
	void doUndo() override
	{
		repo.deleteActivitateByIndex((int)repo.getActivitati().size() - 1);
	}
};

class UndoSterge : public ActiuneUndo
{
private:
	RepositoryAbstract& repo;
	Activitate deletedActivity;

public:
	UndoSterge(RepositoryAbstract& repo, const Activitate& a) : repo{ repo }, deletedActivity{ a } {}

	/// Functie care executa operatia de undo pentru stergerea unei activitati
	void doUndo() override
	{
		repo.addActivitate(deletedActivity);
	}
};

class UndoModifica : public ActiuneUndo
{
private:
	RepositoryAbstract& repo;
	Activitate modifiedActivity;
	int index;

public:
	UndoModifica(RepositoryAbstract& repo, const Activitate& a, int index) : repo{ repo }, modifiedActivity{ a }, index{ index } {}

	/// Functie care executa operatia de undo pentru modificarea unei activitati
	void doUndo() override
	{
		repo.modifyActivitateByIndex(index, modifiedActivity);
	}
};