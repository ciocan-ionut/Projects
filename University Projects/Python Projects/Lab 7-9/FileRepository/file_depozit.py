from Domain.carte import Carte
from Repository.depozit import RepositoryCarte

class FileRepositoryCarte(RepositoryCarte):
    def __init__(self, file_name):
        """
        Functie care creeaza o lista goala pentru a retine carti si initializeaza numele fisierului cu file_name
        :param file_name: string
        """
        super().__init__()
        self.__file_name = file_name

    def __load_from_file(self):
        """
        Functie care populeaza lista de carti cu carti citite din fisier
        :return: -
        """
        with open(self.__file_name, 'r') as file:
            self._carti.clear()
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    line = line.split(", ")
                    id_carte = int(line[0])
                    titlu = line[1]
                    descriere = line[2]
                    autor = line[3]
                    carte = Carte(id_carte, titlu, descriere, autor)
                    self._carti.append(carte)

    def __store_in_file(self):
        """
        Functie care scrie atributele cartilor din lista de carti in fisier
        :return: -
        """
        with open(self.__file_name, 'w') as file:
            for carte in self._carti:
                file.write(f"{carte.get_id()}, {carte.get_titlu()}, {carte.get_descriere()}, {carte.get_autor()}\n")

    def get_carti(self):
        self.__load_from_file()
        return self._carti

    def add_carte(self, carte):
        """
        Functie care populeaza lista de carti cu carti citite din fisier, adauga o carte in carti,
        care contine carti ce pot fi identificate dupa un id int unic si scrie atributele cartilor din lista de carti in fisier
        :param carte: o carte cu un id int
        :return: -
        :raises: ValueError cu mesajul string: "Cartea exista deja!"
                    daca exista deja o carte cu acelasi id in carti
        """
        self.__load_from_file()
        super().add_carte(carte)
        self.__store_in_file()

    def update_titlu_carte(self, id, titlu):
        """
        Functie care populeaza lista de carti cu carti citite din fisier, actualizeaza titlul cartii, cu id-ul id, din carti,
        care contine carti ce pot fi identificate dupa un id int unic, cu titlul titlu si
        scrie atributele cartilor din lista de carti in fisier
        :param id: int
        :param titlu: string
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        self.__load_from_file()
        super().update_titlu_carte(id, titlu)
        self.__store_in_file()

    def update_descriere_carte(self, id, descriere):
        """
        Functie care populeaza lista de carti cu carti citite din fisier, actualizeaza descrierea cartii, cu id-ul id, din carti,
        care contine carti ce pot fi identificate dupa un id int unic, cu descrierea descriere si
        scrie atributele cartilor din lista de carti in fisier
        :param id: int
        :param descriere: string
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        self.__load_from_file()
        super().update_descriere_carte(id, descriere)
        self.__store_in_file()

    def update_autor_carte(self, id, autor):
        """
        Functie care populeaza lista de carti cu carti citite din fisier, actualizeaza autorul cartii, cu id-ul id, din carti,
        care contine carti ce pot fi identificate dupa un id int unic, cu autorul autor si
        scrie atributele cartilor din lista de carti in fisier
        :param id: int
        :param autor: string
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        self.__load_from_file()
        super().update_autor_carte(id, autor)
        self.__store_in_file()

    def remove_carte(self, id):
        """
        Functie care populeaza lista de carti cu carti citite din fisier, sterge cartea cu id-ul id din carti,
        care contine carti ce pot fi identificate dupa un id int unic si scrie atributele cartilor din lista de carti in fisier
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        self.__load_from_file()
        super().remove_carte(id)
        self.__store_in_file()

    def search_carte_by_id(self, id):
        """
        Functie care populeaza lista de carti cu carti citite din fisier si cauta o carte dupa id in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param id: int
        :return: cartea cu id-ul id, daca exista
        :raises: ValueError cu mesajul string: "Cartea nu exista!"
                    daca cartea cu id-ul id nu se afla in carti
        """
        self.__load_from_file()
        return super().search_carte_by_id(id)

    def search_carti_by_titlu(self, titlu):
        """
        Functie care populeaza lista de carti cu carti citite din fisier si cauta cartile cu titlul titlu in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param titlu: string
        :return: o lista de carti care au titlul titlu, daca exista
        :raises: ValueError cu mesajul string: "Nu exista nicio carte cu acest titlu!"
                    daca nicio carte din carti nu are titlul titlu
        """
        self.__load_from_file()
        return super().search_carti_by_titlu(titlu)

    def search_carti_by_autor(self, autor):
        """
        Functie care populeaza lista de carti cu carti citite din fisier si cauta cartile scrise de autorul autor in carti,
        care contine carti ce pot fi identificate dupa un id int unic
        :param autor: string
        :return: o lista de carti care au autorul autor, daca exista
        :raises: ValueError cu mesajul string: "Nu exista nicio carte scrisa de acest autor!"
                    daca nicio carte din carti nu este scrisa de autorul autor
        """
        self.__load_from_file()
        return super().search_carti_by_autor(autor)