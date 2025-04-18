class Material:
    def __init__(self, cod, denumire, unitate_de_masura, cantitate_pe_stoc, pret_unitar):
        """
        Functie care creeaza un obiect de tip Material cu codul cod, denumirea denumire,
        unitatea de masura unitate_de_masura, de cantitatea cantitate_pe_stoc si cu pretul pret_unitar
        :param cod: int
        :param denumire: string
        :param unitate_de_masura: string
        :param cantitate_pe_stoc: int
        :param pret_unitar: float
        """
        self.__cod = cod
        self.__denumire = denumire
        self.__unitate_de_masura = unitate_de_masura
        self.__cantitate_pe_stoc = cantitate_pe_stoc
        self.__pret_unitar = pret_unitar

    def get_cod(self):
        """
        Functie care returneaza codul unic al materialului
        :return: codul unic al materialului
        """
        return self.__cod

    def get_denumire(self):
        """
        Functie care returneaza denumirea materialului
        :return: denumirea materialului
        """
        return self.__denumire

    def get_unitate_de_masura(self):
        """
        Functie care returneaza unitatea de masura in care este reprezentat materialul
        :return: unitatea de masura in care este reprezentat materialul
        """
        return self.__unitate_de_masura

    def get_cantitate_pe_stoc(self):
        """
        Functie care returneaza cantitatea pe stoc a materialului
        :return: cantitatea pe stoc a materialului
        """
        return self.__cantitate_pe_stoc

    def get_pret_unitar(self):
        """
        Functie care returneaza pretul unitar al materialului
        :return: pretul unitar al materialului
        """
        return self.__pret_unitar

    def get_valoare_stoc(self):
        """
        Functie care returneaza valoare de pe stoc a materialului
        :return: valoarea de pe stoc a materialului
        """
        return self.__cantitate_pe_stoc * self.__pret_unitar

    def set_stoc(self, cantitate):
        """
        Functie care seteaza cantitatea pe stoc a materialului la cantitate
        :param cantitate: int
        :return: -
        """
        self.__cantitate_pe_stoc = cantitate

    def __eq__(self, other):
        """
        Functie care ajuta la stabilirea daca 2 materiale sunt egale prin compararea codurilor lor unice
        :param other: obiect de tip material cu un cod unic
        :return: True daca codurile sunt identice; False in caz contrar
        """
        return self.__cod == other.__cod