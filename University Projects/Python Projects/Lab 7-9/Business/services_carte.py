from functools import cmp_to_key

from Domain.carte import Carte
from Validare.validator_carte import ValidateCarte
import random
import string

class ServicesCarte:
    def __init__(self, repositoryCarte, repositoryImprumut):
        """
        Functie care initializeaza repository-urile clasei cu repository-ul de carti si de imprumuturi
        :param repositoryCarte: repository-ul de carti
        :param repositoryImprumut: repository-ul de imprumuturi
        """
        self.__repositoryCarte = repositoryCarte
        self.__repositoryImprumut = repositoryImprumut

    def create_validate_add_carte(self, id, titlu, descriere, autor):
        """
        Functie care creeaza o carte cu un id int, un titlu string, o descriere string si un autor string;
        verifica daca cartea are un id > 0, a fost introdus un titlu, o descriere si un autor;
        adauga cartea in carti daca nu exista deja o carte cu acelasi id in carti
        :param id: int
        :param titlu: string
        :param descriere: string
        :param autor: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Titlu invalid!\n" daca titlu este ""
            "Descriere invalida!\n" daca descriere este ""
            "Autor invalid!\n" daca autor este ""
                 ValueError cu mesajul string: "Cartea exista deja!"
                    daca exista deja o carte cu acelasi id in carti
        """
        carte = Carte(id, titlu, descriere, autor)
        ValidateCarte.validate_carte(carte)
        self.__repositoryCarte.add_carte(carte)

    def validate_update_titlu_carte(self, id, titlu):
        """
        Functie care verifica daca id > 0 si daca a fost introdus un titlu;
        actualizeaza titlul cartii, cu id-ul id, din carti, cu titlul titlu
        :param id: int
        :param titlu: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Titlu invalid!\n" daca titlu este ""
                 ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ValidateCarte.validate_id_titlu(id, titlu)
        self.__repositoryCarte.update_titlu_carte(id, titlu)

    def validate_update_descriere_carte(self, id, descriere):
        """
        Functie care verifica daca id > 0 si daca a fost introdus o descriere;
        actualizeaza descrierea cartii, cu id-ul id, din carti, cu descrierea descriere
        :param id: int
        :param descriere: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Descriere invalida!\n" daca descrierea este ""
                 ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ValidateCarte.validate_id_descriere(id, descriere)
        self.__repositoryCarte.update_descriere_carte(id, descriere)

    def validate_update_autor_carte(self, id, autor):
        """
        Functie care verifica daca id > 0 si daca a fost introdus un autor;
        actualizeaza autorul cartii, cu id-ul id, din carti, cu autorul autor
        :param id: int
        :param autor: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Autor invalid!\n" daca autor este ""
                 ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ValidateCarte.validate_id_autor(id, autor)
        self.__repositoryCarte.update_autor_carte(id, autor)

    def validate_remove_carte(self, id):
        """
        Functie care verifica daca id > 0 si sterge cartea cu id-ul id din carti
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "ID invalid!\n" daca id este <= 0
                 ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ValidateCarte.validate_id(id)
        carte = self.__repositoryCarte.search_carte_by_id(id)
        self.__repositoryImprumut.remove_carte_imprumutata(carte)
        self.__repositoryCarte.remove_carte(id)

    def validate_search_carte_by_id(self, id):
        """
        Functie care verifica daca id > 0 si cauta o carte dupa id in carti
        :param id: int
        :return: cartea cu id-ul id, daca exista
        :raises: ValueError cu mesajul string: "ID invalid!\n" daca id este <= 0
                 ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        ValidateCarte.validate_id(id)
        carte = self.__repositoryCarte.search_carte_by_id(id)
        return carte

    def validate_search_carti_by_titlu(self, titlu):
        """
        Functie care verifica daca a fost introdus un titlu si cauta cartile cu titlul titlu in carti
        :param titlu: string
        :return: o lista de carti care au titlul titlu, daca exista
        :raises: ValueError cu mesajul string: "Titlu invalid!\n" daca titlu este ""
                 ValueError cu mesajul string: "Nu exista nicio carte cu acest titlu!"
                    daca nicio carte din carti nu are titlul titlu
        """
        ValidateCarte.validate_titlu(titlu)
        lista_carti = self.__repositoryCarte.search_carti_by_titlu(titlu)
        return lista_carti

    def validate_search_carti_by_autor(self, autor):
        """
        Functie care verifica daca a fost introdus un autor si cauta cartile scrise de autorul autor in carti
        :param autor: string
        :return: o lista de carti care au autorul autor, daca exista
        :raises: ValueError cu mesajul string: "Autor invalid!\n" daca autor este ""
                 ValueError cu mesajul string: "Cartea nu exista!"
                    daca nicio carte din carti nu este scrisa de autorul autor
        """
        ValidateCarte.validate_autor(autor)
        lista_carti = self.__repositoryCarte.search_carti_by_autor(autor)
        return lista_carti

    @staticmethod
    def __compare(a, b):
        if a.get_titlu() > b.get_titlu():
            return 1
        elif a.get_titlu() == b.get_titlu() and a.get_id() > b.get_id():
            return 1
        elif a.get_titlu() == b.get_titlu() and a.get_id() == b.get_id():
            return 0
        elif a.get_titlu() == b.get_titlu() and a.get_id() < b.get_id():
            return -1
        else:
            return -1

    def carti_sorted(self):
        return sorted(self.__repositoryCarte.get_carti(), key=cmp_to_key(ServicesCarte.__compare))

    def generate_X_carti(self, X):
        i = 0
        while i < X:
            id = random.randint(1, 1000)
            titlu = "".join(random.choices(string.ascii_letters, k=6))
            descriere = "".join(random.choices(string.ascii_letters, k=8))
            autor = "".join(random.choices(string.ascii_letters, k=6))
            carte = Carte(id, titlu, descriere, autor)
            if carte not in self.__repositoryCarte.get_carti():
                ValidateCarte.validate_carte(carte)
                self.__repositoryCarte.add_carte(carte)
                i += 1