class Automobil:
    def __init__(self, id, marca, pret, model, data):
        """
        Functia creeaza un obiect automobil cu id-ul int id, marca string marca, pretul float pret, modelul string
        model si data string data
        :param id: int
        :param marca: string
        :param pret: float
        :param model: string
        :param data: string
        """
        self.__id = id
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data = data

    def get_id(self):
        """
        Functie care returneaza id-ul int al unui automobil
        :return: id-ul int
        """
        return self.__id

    def get_marca(self):
        """
        Functia care returneaza marca string a unui automobil
        :return: marca string
        """
        return self.__marca

    def get_pret(self):
        """
        Functie care returneaza pretul float al unui automobil
        :return: pretul float
        """
        return self.__pret

    def get_model(self):
        """
        Functie care returneaza modelul string al unui automobil
        :return: modelul string
        """
        return self.__model

    def get_data(self):
        """
        Functie care returneaza data string a unui automobil
        :return: data string
        """
        return self.__data

    def set_marca(self, marca):
        """
        Functia seteaza marca automobilului la marca string
        :param marca: string
        :return: -
        """
        self.__marca = marca

    def __str__(self):
        """
        Functia ajuta la afisarea mai explicita a atributelor unui automobil
        :return: un sir prin care putem afisa atributele unui automobil
        """
        return f'Automobil {self.__marca}, {self.__pret}, {self.__model} {self.__data}'