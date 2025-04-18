class RepositoryClient:
    def __init__(self):
        """
        Functie care creeza un dictionar gol pentru a retine chei unice care reprezinta
        id-urile unice ale clientilor si valorile acestora care corespund id-ului int
        """
        self._clienti = {}

    def get_clienti(self):
        """
        Functie care returneaza clientii sub forma de lista
        :return: lista de clienti
        """
        return [self._clienti[id] for id in self._clienti]

    def add_client(self, client):
        """
        Functie care adauga un client in clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param client: un client cu un id int
        :return: -
        :raises: ValueError cu mesajul string: "Clientul exista deja!"
                    daca exista deja un client cu acelasi id in clienti
        """
        if client.get_id() in self._clienti:
            raise ValueError("Clientul exista deja!")
        self._clienti[client.get_id()] = client

    def update_client(self, id, nume):
        """
        Functie care actualizeaza numele clientului, cu id-ul id, din clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param id: int
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        if id in self._clienti:
            self._clienti[id].set_nume(nume)
        else:
            raise ValueError("Clientul nu exista!")

    def remove_client(self, id):
        """
        Functie care sterge clientul cu id-ul id din clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        if id in self._clienti:
            del self._clienti[id]
        else:
            raise ValueError("Clientul nu exista!")

    def search_client_by_id(self, id):
        """
        Functie care cauta un client dupa id in clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param id: int
        :return: clientul cu id-ul id
        :raises: ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        if id in self._clienti:
            return self._clienti[id]
        else:
            raise ValueError("Clientul nu exista!")

    def search_clienti_by_nume(self, nume, chei, solutie):
        """
        Functie care cauta clientii cu numele nume in clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param nume: string
        :param chei: lista cheilor din dicționarul de clienți (folosită pentru recursivitate)
        :param solutie: lista în care vor fi stocați clienții găsiți
        :return: lista de clienti care corespund numelui dat
        :raises: ValueError cu mesajul string: "Nu exista niciun client cu acest nume!"
                    daca niciun client din clienti nu are numele nume
        """
        # Complexitate O(n)
        """     
        solutie = []
        for id in self._clienti:
            if nume == self._clienti[id].get_nume():
                solutie.append(self._clienti[id])
        if len(solutie) == 0:
            raise ValueError("Nu exista niciun client cu acest nume!")
        return solutie
        """

        if solutie is None:
            solutie = []
        if chei is None:
            chei = list(self._clienti.keys())

        if not chei:
            if not solutie:
                raise ValueError("Nu exista niciun client cu acest nume!")
            return solutie

        id_curent = chei[0]
        if self._clienti[id_curent].get_nume() == nume:
            solutie.append(self._clienti[id_curent])

        return self.search_clienti_by_nume(nume, chei[1:], solutie)