from Domain.client import Client
from Validare.validator_client import ValidateClient

class ServicesClient:
    def __init__(self, repositoryClient, repositoryImprumut):
        """
        Functie care initializeaza repository-urile clasei cu repository-ul de clienti si de imprumuturi
        :param repositoryClient: repository-ul de clienti
        :param repositoryImprumut: repository-ul de imprumuturi
        """
        self.__repositoryClient = repositoryClient
        self.__repositoryImprumut = repositoryImprumut

    def create_validate_add_client(self, id, nume):
        """
        Functie care creeaza un client cu un id int si un nume string;
        verifica daca clientul are un id > 0 si a fost introdus un nume;
        adauga clientul in clienti daca nu exista deja un client cu acelasi id in clienti
        :param id: int
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id <= 0
            "Nume invalid!\n" daca titlu este ""
                 ValueError cu mesajul string: "Clientul exista deja!"
                    daca exista deja un client cu acelasi id in clienti
        """
        client = Client(id, nume)
        ValidateClient.validate_client(client)
        self.__repositoryClient.add_client(client)

    def validate_update_client(self, id, nume):
        """
        Functie care verifica daca id > 0 si daca a fost introdus un nume;
        actualizeaza numele clientului, cu id-ul id, din clienti, cu numele nume
        :param id: int
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id <= 0
            "Nume invalid!\n" daca titlu este ""
                 ValueError cu mesajul string: "Clientul nu exista!"

        """
        ValidateClient.validate_id_nume(id, nume)
        self.__repositoryClient.update_client(id, nume)

    def validate_remove_client(self, id):
        """
        Functie care verifica daca id > 0 si sterge clientul cu id-ul id din clienti
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "ID invalid!\n" daca id <= 0
                 ValueError cu mesajul string: "Clientul nu exista!"
        """
        ValidateClient.validate_id(id)
        client = self.__repositoryClient.search_client_by_id(id)
        self.__repositoryImprumut.remove_client_cu_imprumuturi(client)
        self.__repositoryClient.remove_client(id)

    def validate_search_client_by_id(self, id):
        """
        Functie care verifica daca id > 0 si cauta un client dupa id in clienti
        :param id: int
        :return: clientul cu id-ul id, daca exista
        :raises: ValueError cu mesajul string: "ID invalid!\n" daca id este <= 0
                 ValueError cu mesajul string: "Clientul nu exista!"
                    daca clientul cu id-ul id nu se afla in clienti
        """
        ValidateClient.validate_id(id)
        client = self.__repositoryClient.search_client_by_id(id)
        return client

    def validate_search_clienti_by_nume(self, nume):
        """
        Functie care verifica daca a fost introdus un nume si cauta clientii cu numele nume in clienti
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string: "Nume invalid!\n" daca nume este ""
                 ValueError cu mesajul string: "Nu exista niciun client cu acest nume!"
                    daca niciun client din clienti nu are numele nume
        """
        ValidateClient.validate_nume(nume)
        lista_clienti = self.__repositoryClient.search_clienti_by_nume(nume, None, None)
        return lista_clienti