# cheltuiala.py

"""
class Cheltuiala:
    #Clasa defineste o cheltuiala
    def __init__(self, zi, suma, tip):
        Constructorul clasei
        input: - zi (numar natural din intervalul [1, 31])
               - suma (numar real > 0)
               - tip (mancare, intretinere, imbracaminte, telefon, altele)
        output: - o cheltuiala facuta in ziua 'zi', de 'suma' bani, pentru 'tip'
        self.zi = zi
        self.suma = suma
        self.tip = tip

    def getZi(self):
        # Functie care returneaza ziua unei cheltuieli
        return self.zi

    def getSuma(self):
        # Functie care returneaza suma unei cheltuieli
        return self.suma

    def getTip(self):
        # Functie care returneaza tipul unei cheltuieli
        return self.tip

    def __str__(self):
        # Suprascrierea functiei de tiparire a unei cheltuieli
        return f"Cheltuiala din ziua {self.zi}, de {self.suma} bani, pentru {self.tip}"

    def __eq__(self, other):
        # Suprascrierea functiei care stabileste daca doua cheltuieli sunt egale
        return self.zi == other.zi and self.suma == other.suma and self.tip == other.tip
"""

"""
def createCheltuiala(zi, suma, tip):
    Functia creeaza o cheltuiala facuta in ziua 'zi', de 'suma' bani, pentru 'tip'
    input: - zi (numar natural din intervalul [1, 31]
           - suma (numar real > 0)
           - tip (mancare, intretinere, imbracaminte, telefon, altele)
    output: - cheltuiala creata
    return Cheltuiala(zi, suma, tip)
"""

def createCheltuiala(id, zi, suma, tip):
    return{
        "id": id, "zi": zi, "suma": suma, "tip": tip
    }

def getIDCheltuiala(cheltuiala):
    return cheltuiala["id"]

def getZiuaCheltuiala(cheltuiala):
    return cheltuiala["zi"]

def getSumaCheltuiala(cheltuiala):
    return cheltuiala["suma"]

def getTipCheltuiala(cheltuiala):
    return cheltuiala["tip"]

def cheltuieliEgale(cheltuiala1, cheltuiala2):
    return getIDCheltuiala(cheltuiala1) == getIDCheltuiala(cheltuiala2)

def printCheltuiala(cheltuiala):
    return f"Cheltuiala cu ID-ul {getIDCheltuiala(cheltuiala)}, din ziua {getZiuaCheltuiala(cheltuiala)}, de {getSumaCheltuiala(cheltuiala)} bani, pentru {getTipCheltuiala(cheltuiala)}"