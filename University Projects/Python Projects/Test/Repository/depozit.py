class RepositoryMateriale:
    def __init__(self):
        """
        Functie care initializeaza variabila depozit cu un dictionar gol in vederea retinerii materialelor
        dupa codul lor unic, folosit ca si cheie unica
        """
        self.__depozit = {}

    def get_materiale(self):
        """
        Functie care returneaza materialele din dictionar sub forma de lista
        :return: lista cu materialele din dictionar
        """
        return [m for m in self.__depozit.values()]

    def add_material(self, material):
        """
        Functie care adauga un material in depozit, care este un dictionar cu chei unice
        :param material: un obiect de tipul Material
        :return: -
        :raises: ValueError cu mesajul string:
            "Materialul exista deja in depozit!" daca materialul cu codul unic al acestuia exista deja in depozit
        """
        if material.get_cod() in self.__depozit:
            raise ValueError("Materialul exista deja in depozit!")
        self.__depozit[material.get_cod()] = material

    def search_material_by_cod(self, cod):
        """
        Functie care cauta in depozit, care este un dictonar cu chei unice, daca exista materialul cu codul unic cod
        :param cod: int
        :return: materialul cu codul unic cod daca exista
        :raises: ValueError cu mesajul string:
            "Materialul nu exista in depozit!" daca materialul cu codul cod nu exista in depozit
        """
        if cod in self.__depozit:
            return self.__depozit[cod]
        else:
            raise ValueError("Materialul nu exista in depozit!")