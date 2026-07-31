from Repository.imprumut import RepositoryImprumut
from Repository.depozit import RepositoryCarte
from Repository.clientela import RepositoryClient

class FileRepositoryImprumut(RepositoryImprumut):
    def __init__(self, repositoryFileCarte, repositoryFileClient, file_name):
        """
        Functie care creeaza un dictionar gol pentru a retine chei unice care reprezinta
        clienti cu id-uri unice si o lista cu cartile care au id-uri unice pe care le-au imprumutat si
        un dictionar gol pentru a retine chei unice care reprezinta cartile cu id-uri unice
        si o lista cu clientii care au id-uri unice care au imprumutat cartea respectiva
        si initializeaza numele fisierului cu file_name
        """
        super().__init__()
        self.__repositoryFileCarte = repositoryFileCarte
        self.__repositoryFileClient = repositoryFileClient
        self.__file_name = file_name

    def __load_from_file(self):
        """
        Functie care populeaza dictionarele cu imprumuturile efectuate
        :return: -
        """
        with open(self.__file_name) as file:
            self._clienti_cu_carti.clear()
            self._carti_imprumutate.clear()
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    line = line.split(", ")
                    id_client = int(line[0])
                    id_carte = int(line[1])
                    client = self.__repositoryFileClient.search_client_by_id(id_client)
                    carte = self.__repositoryFileCarte.search_carte_by_id(id_carte)
                    if client not in self._clienti_cu_carti.keys():
                        self._clienti_cu_carti[client] = [carte]
                    else:
                        self._clienti_cu_carti[client].append(carte)
                    if carte not in self._carti_imprumutate.keys():
                        self._carti_imprumutate[carte] = [client]
                    else:
                        self._carti_imprumutate[carte].append(client)

    def __store_in_file(self):
        """
        Functie care scrie id-ul clientului care a imprumutat cartea si id-ul cartii pe care a imprumutat-o in fisier
        :return: -
        """
        with open(self.__file_name, 'w') as file:
            for client in self._clienti_cu_carti:
                for carte in self._clienti_cu_carti[client]:
                    file.write(f"{client.get_id()}, {carte.get_id()}\n")

    def get_clienti_cu_carti(self):
        """
        Functie care returneaza dictionarul cu clientii si cartile pe care le-au imprumutat
        :return: dictionarul cu clientii si cartile pe care le-au imprumutat
        """
        self.__load_from_file()
        return self._clienti_cu_carti

    def get_carti_imprumutate(self):
        """
        Functie care returneaza dictionarul cu cartile si clientii care au imprumutat cartea respectiva
        :return: dictionarul cu cartile si clientii care au imprumutat cartea respectiva
        """
        self.__load_from_file()
        return self._carti_imprumutate

    def add_imprumut(self, client, carte):
        """
        Functie care populeaza dictionarele cu imprumuturile efectuate, realizeaza operatia de imprumut a unei carti si
        scrie id-ul clientului care a imprumutat cartea si id-ul cartii pe care a imprumutat-o in fisier
        :param client: un client cu un id int unic
        :param carte: o carte cu un id int unic
        :return: -
        """
        self.__load_from_file()
        super().add_imprumut(client, carte)
        self.__store_in_file()

    def remove_imprumut(self, client, carte):
        """
        Functie care populeaza dictionarele cu imprumuturile efectuate, realizeaza operatia de returnare a unei carti si
        scrie id-ul clientului care a imprumutat cartea si id-ul cartii pe care a imprumutat-o in fisier
        :param client: un client cu un id int unic
        :param carte: o carte cu un id int unic
        :return: -
        """
        self.__load_from_file()
        super().remove_imprumut(client, carte)
        self.__store_in_file()

    def remove_client_cu_imprumuturi(self, client):
        """
        Functie care populeaza dictionarele cu imprumuturile efectuate, sterge toate imprumuturile facute de un client si
        scrie id-ul clientului care a imprumutat cartea si id-ul cartii pe care a imprumutat-o in fisier
        :param client: un client cu un id int unic
        :return: -
        """
        self.__load_from_file()
        super().remove_client_cu_imprumuturi(client)
        self.__store_in_file()

    def remove_carte_imprumutata(self, carte):
        """
        Functie care populeaza dictionarele cu imprumuturile efectuate, sterge toate imprumuturile facute pentru o carte si
        scrie id-ul clientului care a imprumutat cartea si id-ul cartii pe care a imprumutat-o in fisier
        :param carte: o carte cu un id int unic
        :return: -
        """
        self.__load_from_file()
        super().remove_carte_imprumutata(carte)
        self.__store_in_file()