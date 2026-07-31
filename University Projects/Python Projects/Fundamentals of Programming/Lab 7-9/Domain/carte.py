class Carte:
    def __init__(self, id, titlu, descriere, autor):
        """
        Functie care creeaza o carte cu un id int, un titlu string, o descriere string si un autor string
        :param id: int
        :param titlu: string
        :param descriere: string
        :param autor: string
        """
        self.__id = id
        self.__titlu = titlu
        self.__descriere = descriere
        self.__autor = autor

    def get_id(self):
        """
        Functie care returneaza id-ul int al unei carti
        :return: id-ul int al unei carti
        """
        return self.__id

    def get_titlu(self):
        """
        Functie care returneaza titlul string al unei carti
        :return: titlul string al unei carti
        """
        return self.__titlu

    def get_descriere(self):
        """
        Functie care returneaza descrierea string a unei carti
        :return: descriere string a unei carti
        """
        return self.__descriere

    def get_autor(self):
        """
        Functie care returneaza autorul string al unei carti
        :return: autorul string al unei carti
        """
        return self.__autor

    def set_titlu(self, titlu):
        """
        Functie care seteaza titlul string al unei carti cu titlul titlu
        :param titlu: string
        :return: -
        """
        self.__titlu = titlu

    def set_descriere(self, descriere):
        """
        Functie care seteaza descrierea string a unei carti cu descrierea descriere
        :param descriere: string
        :return: -
        """
        self.__descriere = descriere

    def set_autor(self, autor):
        """
        Functie care seteaza autorul string al unei carti cu autorul autor
        :param autor: string
        :return: -
        """
        self.__autor = autor

    def __str__(self):
        """
        Functie care ajuta la afisarea explicita a unei carti
        :return: un sir care ajuta la afisarea corespunzatoare a atributelor unei carti
        """
        return f"{self.__id}. Cartea '{self.__titlu}', scrisa de {self.__autor}, {self.__descriere}"

    def __hash__(self):
        """
        Functie care ajuta ca obiectul Carte sa fie utilizat ca si cheie intr-un dictionar
        :return: hash-ul pentru un obiect de tip Carte, adica id-ul cartii
        """
        return hash(self.__id)

    def __eq__(self, other):
        """
        Functie care ajuta la compararea mai usoara a 2 obiecte de tip carte
        :param other: un obiect de tip carte
        :return: rezultatul logic dintre compararea id-urilor, titlurilor, descrierilor si autorilor celor 2 obiecte
        """
        return self.__id == other.__id