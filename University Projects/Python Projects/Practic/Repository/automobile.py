from Domain.automobil import Automobil

class Automobile:
    def __init__(self, nume_fisier):
        """
        Functie care initializeaza numele fisierului de unde vor fi extrase informatiile
        :param nume_fisier: string
        """
        self.__nume_fisier = nume_fisier

    def get_automobile(self):
        """
        Functie care returneaza automobilele sub forma de lista
        :return: lista de automobile
        """
        automobile = []
        self.__load_from_file(automobile)
        return automobile

    def __load_from_file(self, automobile):
        """
        Functie care incarca din fisier atributele automobilelor si creeaza o lista de obiecte de tip automobil
        cu atributele respective
        :param automobile: lista de automobile (goala)
        :return: lista de automobile cu datele incarcate
        """
        with open(self.__nume_fisier, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    line = line.split(",")
                    id = int(line[0])
                    marca = line[1]
                    pret = float(line[2])
                    model = line[3]
                    data = line[4]
                    auto = Automobil(id, marca, pret, model, data)
                    automobile.append(auto)

    def save_to_file(self, automobile):
        """
        Functie care scrie in fisier atributele automobilelor
        :param automobile: lista de autombile
        :return: -
        """
        with open(self.__nume_fisier, 'w') as f:
            for auto in automobile:
                f.write(f"{auto.get_id()},{auto.get_marca()},{auto.get_pret()},{auto.get_model()},{auto.get_data()}\n")

    def add_auto(self, auto):
        """
        Functia incarca datele din fisier, populeaza lista, adauga automobilul auto in lista de automobile daca este
        valid si actualizeaza fisierul
        :param auto: un obiect de tip automobil
        :return: True (daca automobilul a putut fi adaugat in fisier) / False (in caz contrar)
        """
        automobile = []
        self.__load_from_file(automobile)
        for automobil in automobile:
            if automobil.get_id() == auto.get_id():
                return False
        automobile.append(auto)
        self.save_to_file(automobile)
        return True

    @staticmethod
    def __cauta_cifra(n, cifra):
        """
        Functie care verifica daca cifra cifra exista in numarul n
        :param n: int
        :param cifra: int
        :return: True (daca cifra exista) / False (in caz contrar)
        """
        while n > 0:
            c = n % 10
            if c == cifra:
                return True
            n = n // 10
        return False

    def remove_auto(self, cifra):
        """
        Functia incarca datele din fisier, populeaza lista, sterge din lista autoturismele care contin cifra cifra
        in pret si actualizeaza fisierul
        :param cifra: int
        :return: -
        """
        automobile = []
        self.__load_from_file(automobile)
        automobile = [x for x in automobile if not self.__cauta_cifra(x.get_pret(), cifra)]
        self.save_to_file(automobile)