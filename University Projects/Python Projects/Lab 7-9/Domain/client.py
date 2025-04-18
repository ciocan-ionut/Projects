class Client():
    def __init__(self, id, nume):
        """
        Functie care creeaza un client cu un id int si un nume string
        :param id: int
        :param nume: string
        """
        self.__id = id
        self.__nume = nume

    def get_id(self):
        """
        Functie care returneaza id-ul int al unui client
        :return: id-ul int al unui client
        """
        return self.__id

    def get_nume(self):
        """
        Functie care returneaza numele string al unui client
        :return: numele string al unui client
        """
        return self.__nume

    def set_nume(self, nume):
        """
        Functie care seteaza numele string al unui client cu numele nume
        :param nume: string
        :return: -
        """
        self.__nume = nume

    def __str__(self):
        """
        Functie care ajuta la afisarea explicita a unui client
        :return: un sir care ajuta la afisarea corespunzatoare a atributelor unui client
        """
        return f"{self.__id}. Clientul {self.__nume}"

    def __hash__(self):
        """
        Functie care ajuta ca obiectul Client sa fie utilizat ca si cheie intr-un dictionar
        :return: hash-ul pentru un obiect de tip Client, adica id-ul clientului
        """
        return hash(self.__id)

    def __eq__(self, other):
        """
        Functie care ajuta la compararea mai usoara a 2 obiecte de tip client
        :param other: un obiect de tip client
        :return: rezultatul logic dintre compararea numelor si a id-urilor celor 2 obiecte
        """
        return self.__id == other.__id