from Domain.material import Material
import random

class ServicesMaterial:
    def __init__(self, repositoryMateriale):
        """
        Functie care initializeaza repository-ul clasei cu repository-ul de materiale
        :param repositoryMateriale: repository-ul de materiale
        """
        self.__repositoryMateriale = repositoryMateriale

    def create_and_add_material(self, cod, denumire, um, cantitate, pret):
        """
        Functie care creeaza un obiect de tip Material cu codul cod, denumirea denumire,
        unitatea de masura unitate_de_masura, de cantitatea cantitate_pe_stoc si cu pretul pret_unitar;
        si il adauga in depozit, care este un dictionar cu chei unice
        :param cod: int
        :param denumire: string
        :param um: string
        :param cantitate: int
        :param pret: float
        :return: -
        :raises: ValueError cu mesajul string:
            "Materialul exista deja in depozit!" daca materialul cu codul unic al acestuia exista deja in depozit
        """
        material = Material(cod, denumire, um, cantitate, pret)
        self.__repositoryMateriale.add_material(material)

    def valoare_pe_stoc_mai_mare_decat_val(self, val):
        """
        Functie care scrie in fisier materialele ale caror valoare de pe stoc este mai mare decat valoarea val
        :param val: float
        :return: -
        """
        with open("materiale.txt", "w") as file:
            for material in self.__repositoryMateriale.get_materiale():
                if material.get_valoare_stoc() > val:
                    file.write(f"{material.get_cod()},{material.get_denumire()},{material.get_cantitate_pe_stoc()},{material.get_pret_unitar()}\n")

    @staticmethod
    def __get_vanzari():
        """
        Functie care citeste din fisier toate vanzarile si populeaza lista de vanzari cu id-urile vanzarilor
        :return: lista de id-uri de vanzari
        """
        with open("vanzari.txt", "r") as file:
            vanzari = []
            lines = file.readlines()
            i = 0
            for line in lines:
                if line != "":
                    vanzari[i] = line[0]
                    i += 1
            return vanzari

    def vanzare(self, cod, cantitate):
        """
        Functie care efectueaza o vanzare
        :param cod: int
        :param cantitate: int
        :return: -
        """
        vanzari = ServicesMaterial.__get_vanzari()
        with open("vanzari.txt", "w") as file:
            material = self.__repositoryMateriale.search_material_by_id(cod)
            if material.get_cantitate_pe_stoc() <= cantitate:
                return False
            id_vanzare = random.randrange(0, 100)
            while id_vanzare in vanzari:
                id_vanzare = random.randrange(0, 100)
            material.set_stoc(material.get_cantitate_pe_stoc()-cantitate)
            file.write(f"{id_vanzare},{material.get_denumire()},{cantitate},{cantitate*material.get_pret_unitar()}")