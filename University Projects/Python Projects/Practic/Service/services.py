import datetime
from Domain.automobil import Automobil

class ServicesAutomobile:
    def __init__(self, repository):
        self.__repo = repository
        self.__undo = []

    def adauga_automobil(self, id, marca, pret, model, data):
        """
        Functia salveaza o copie a listei inainte de operatie, creeaza un automobil cu id-ul id, marca marca,
        pretul pret, modelul model si data data, ca mai apoi sa il adauge in lista de automobile
        :param id: int
        :param marca: string
        :param pret: float
        :param model: string
        :param data: string
        :return: True (daca automobilul a putut fi adaugat in fisier) / False (in caz contrar)
        """
        self.__undo.append(self.__repo.get_automobile().copy())
        auto = Automobil(id, marca, pret, model, data)
        return self.__repo.add_auto(auto)

    def sterge_automobile(self, cifra):
        """
        Functia salveaza o copie a listei inainte de operatie si sterge din lista autoturismele care contin
        cifra cifra in pret
        :param cifra: int
        :return: -
        """
        self.__undo.append(self.__repo.get_automobile().copy())
        self.__repo.remove_auto(cifra)

    def __itp_expirat(self):
        """
        Functia verifica daca automobilele au itp-ul expirat si actualizeaza marca cu caracterul "*" in fata
        :return: lista de automobile modificata
        """
        automobile = self.__repo.get_automobile()
        data_azi = datetime.datetime.now()
        for auto in automobile:
            ok = False
            zi, luna, an = auto.get_data().split(":")
            if int(an) < data_azi.year:
                ok = True
            elif int(an) == data_azi.year:
                if int(luna) < data_azi.month:
                    ok = True
                elif int(luna) == data_azi.month:
                    if int(zi) < data_azi.day:
                        ok = True
            if ok:
                auto.set_marca("*" + auto.get_marca())
        return automobile

    def filtrare_automobile(self, filtru_marca, filtru_pret):
        """
        Functia afiseaza automobilele in functie de filtrele introduse de utilizator
        :param filtru_marca: string
        :param filtru_pret: float
        :return: lista de automobile filtrata
        """
        automobile = self.__itp_expirat()
        if filtru_marca == "" and filtru_pret == -1:
            return automobile
        elif filtru_marca == "":
            automobile = [x for x in automobile if x.get_pret() < filtru_pret]
        elif filtru_pret == -1:
            automobile = [x for x in automobile if x.get_marca() == filtru_marca or x.get_marca() == "*" + filtru_marca]
        else: automobile = [x for x in automobile if x.get_pret() < filtru_pret and (x.get_marca() == filtru_marca or x.get_marca() == "*" + filtru_marca)]
        return automobile

    def undo_operatie(self):
        """
        Functia actualizeaza lista de automobile cu lista de dinainte de ultima operatie efectuata
        :return: -
        """
        automobile = self.__undo.pop()
        self.__repo.save_to_file(automobile)