class RepositoryCarte:
    def __init__(self):
        """
        Functie care creeaza o lista goala pentru a retine carti
        """
        self._carti = []

    def get_carti(self):
        """
        Functie care returneaza lista de carti
        :return: lista de carti
        """
        return self._carti

    def add_carte(self, carte):
        """
        Functie care adauga o carte in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param carte: o carte cu un id int
        :return: -
        :raises: ValueError cu mesajul string: "Cartea exista deja!"
                    daca exista deja o carte cu acelasi id in carti
        """
        if carte in self._carti:
            raise ValueError("Cartea exista deja!")
        self._carti.append(carte)

    def update_titlu_carte(self, id, titlu):
        """
        Functie care actualizeaza titlul cartii, cu id-ul id, din carti,
        care contine carti ce pot fi identificate dupa un id int unic, cu titlul titlu
        :param id: int
        :param titlu: string
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ok = False
        for carte in self._carti:
            if carte.get_id() == id:
                carte.set_titlu(titlu)
                ok = True
        if not ok:
            raise ValueError("Cartea nu exista!")

    def update_descriere_carte(self, id, descriere):
        """
        Functie care actualizeaza descrierea cartii, cu id-ul id, din carti,
        care contine carti ce pot fi identificate dupa un id int unic, cu descrierea descriere
        :param id: int
        :param descriere: string
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ok = False
        for carte in self._carti:
            if carte.get_id() == id:
                carte.set_descriere(descriere)
                ok = True
        if not ok:
            raise ValueError("Cartea nu exista!")

    def update_autor_carte(self, id, autor):
        """
        Functie care actualizeaza autorul cartii, cu id-ul id, din carti,
        care contine carti ce pot fi identificate dupa un id int unic, cu autorul autor
        :param id: int
        :param autor: string
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ok = False
        for carte in self._carti:
            if carte.get_id() == id:
                carte.set_autor(autor)
                ok = True
        if not ok:
            raise ValueError("Cartea nu exista!")

    def remove_carte(self, id):
        """
        Functie care sterge cartea cu id-ul id din carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ok = False
        for carte in self._carti:
            if carte.get_id() == id:
                self._carti.remove(carte)
                ok = True
        if not ok:
            raise ValueError("Cartea nu exista!")

    def search_carte_by_id(self, id):
        """
        Functie care cauta o carte dupa id in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param id: int
        :return: cartea cu id-ul id, daca exista
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        for carte in self._carti:
            if carte.get_id() == id:
                return carte
        raise ValueError("Cartea nu exista!")

    def search_carti_by_titlu(self, titlu):
        """
        Functie care cauta cartile cu titlul titlu in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param titlu: string
        :return: o lista de carti care au titlul titlu, daca exista
        :raises: ValueError cu mesajul string: "Nu exista nicio carte cu acest titlu!"
                    daca nicio carte din carti nu are titlul titlu
        """
        solutie = []
        for carte in self._carti:
            if titlu == carte.get_titlu():
                solutie.append(carte)
        if len(solutie) == 0:
            raise ValueError("Nu exista nicio carte cu acest titlu!")
        return solutie

    def search_carti_by_autor(self, autor):
        """
        Functie care cauta cartile scrise de autorul autor in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param autor: string
        :return: o lista de carti care au autorul autor, daca exista
        :raises: ValueError cu mesajul string: "Nu exista nicio carte scrisa de acest autor!"
                    daca nicio carte din carti nu este scrisa de autorul autor
        """
        solutie = []
        for carte in self._carti:
            if autor == carte.get_autor():
                solutie.append(carte)
        if len(solutie) == 0:
            raise ValueError("Nu exista nicio carte scrisa de acest autor!")
        return solutie