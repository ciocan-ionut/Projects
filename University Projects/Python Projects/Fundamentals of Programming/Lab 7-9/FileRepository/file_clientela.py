from Domain.client import Client
from Repository.clientela import RepositoryClient

class FileRepositoryClient(RepositoryClient):
    def __init__(self, file_name):
        """
        Functie care creeza un dictionar gol pentru a retine chei unice care reprezinta
        id-urile unice ale clientilor si valorile acestora care corespund id-ului int
        si initializeaza numele fisierului cu file_name
        :param file_name: string
        """
        super().__init__()
        self.__file_name = file_name

    def __load_from_file(self):
        """
        Functie care populeaza dictionarul de clienti cu clienti cititi din fisier
        :return: -
        """
        with open(self.__file_name, 'r') as file:
            self._clienti.clear()
            lines = file.readlines()
            i = 0
            while i < len(lines)-1:
                lines[i] = lines[i].strip()
                lines[i+1] = lines[i+1].strip()
                if lines[i] != "" and lines[i+1] != "":
                    id_client = int(lines[i])
                    nume = lines[i+1]
                    client = Client(id_client, nume)
                    self._clienti[id_client] = client
                i += 2

    def __store_in_file(self):
        """
        Functie care scrie atributele clientilor din dictionarul de clienti in fisier
        :return: -
        """
        with open(self.__file_name, 'w') as file:
            for id_client, client in self._clienti.items():
                file.write(f"{id_client}\n{client.get_nume()}\n")

    def add_client(self, client):
        """
        Functie care populeaza dictionarul de clienti cu clienti cititi din fisier, adauga un client in clienti,
        care contine clienti ce pot fi identificati dupa un id int unic si
        scrie atributele clientilor din dictionarul de clienti in fisier
        :param client: un client cu un id int
        :return: -
        :raises: ValueError cu mesajul string: "Clientul exista deja!"
                    daca exista deja un client cu acelasi id in clienti
        """
        self.__load_from_file()
        super().add_client(client)
        self.__store_in_file()

    def update_client(self, id, nume):
        """
        Functie care populeaza dictionarul de clienti cu clienti cititi din fisier,
        actualizeaza numele clientului, cu id-ul id, din clienti,
        care contine clienti ce pot fi identificati dupa un id int unic si
        scrie atributele clientilor din dictionarul de clienti in fisier
        :param id: int
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        self.__load_from_file()
        super().update_client(id, nume)
        self.__store_in_file()

    def remove_client(self, id):
        """
        Functie care populeaza dictionarul de clienti cu clienti cititi din fisier, sterge clientul cu id-ul id din clienti,
        care contine clienti ce pot fi identificati dupa un id int unic si
        scrie atributele clientilor din dictionarul de clienti in fisier
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        self.__load_from_file()
        super().remove_client(id)
        self.__store_in_file()

    def search_client_by_id(self, id):
        """
        Functie care populeaza dictionarul de clienti cu clienti cititi din fisier si cauta un client dupa id in clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        self.__load_from_file()
        return super().search_client_by_id(id)

    def search_clienti_by_nume(self, nume, chei, solutie):
        """
        Functie care populeaza dictionarul de clienti cu clienti cititi din fisier si cauta clientii cu numele nume in clienti,
        care contine clienti ce pot fi identificati dupa un id int unic
        :param nume: string
        :param chei: lista cheilor din dicționarul de clienți (folosită pentru recursivitate)
        :param solutie: lista în care vor fi stocați clienții găsiți
        :return: lista de clienti care corespund numelui dat
        :raises: ValueError cu mesajul string: "Nu exista niciun client cu acest nume!"
                    daca niciun client din clienti nu are numele nume
        """
        self.__load_from_file()
        return super().search_clienti_by_nume(nume, chei, solutie)