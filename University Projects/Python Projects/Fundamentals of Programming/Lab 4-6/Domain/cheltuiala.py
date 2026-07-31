# cheltuiala.py

def createCheltuiala(idc, zi, suma, tip):
    """
    Functie care creeaza o chetuiala cu un id int, o zi int, o suma float si un tip string
    :param idc: int
    :param zi: int
    :param suma: float
    :param tip: string
    :return: O cheltuiala cu id-ul idc, din ziua zi, de suma suma si de tipul tip
    """
    return{
        "idc": idc, "zi": zi, "suma": suma, "tip": tip
    }

def getIDCheltuiala(cheltuiala):
    """
    Functie care returneaza id-ul int al cheltuielii cheltuiala
    :param cheltuiala: o cheltuiala cu un id int
    :return: id-ul int al cheltuielii cheltuiala
    """
    return cheltuiala["idc"]

def getZiuaCheltuiala(cheltuiala):
    """
    Functie care returneaza ziua int a cheltuielii cheltuiala
    :param cheltuiala: o cheltuiala cu o zi int
    :return: ziua int al cheltuielii cheltuiala
    """
    return cheltuiala["zi"]

def setZiuaCheltuiala(zi, cheltuiala):
    """
    Functia seteaza ziua int a cheltuielii cheltuiala cu ziua zi
    :param zi: int
    :param cheltuiala: o cheltuiala cu o zi int
    :return: -
    """
    cheltuiala["zi"] = zi

def getSumaCheltuiala(cheltuiala):
    """
    Functie care returneaza suma float a cheltuielii cheltuiala
    :param cheltuiala: o cheltuiala cu o suma float
    :return: suma float al cheltuielii cheltuiala
    """
    return cheltuiala["suma"]

def setSumaCheltuiala(suma, cheltuiala):
    """
    Functia seteaza suma float a cheltuielii cheltuiala cu suma suma
    :param suma: float
    :param cheltuiala: o cheltuiala cu o zi int
    :return: -
    """
    cheltuiala["suma"] = suma

def getTipCheltuiala(cheltuiala):
    """
    Functie care returneaza tipul string a cheltuielii cheltuiala
    :param cheltuiala: o cheltuiala cu un tip string
    :return: tipul string al cheltuielii cheltuiala
    """
    return cheltuiala["tip"]

def setTipCheltuiala(tip, cheltuiala):
    """
    Functia seteaza tipul string a cheltuielii cheltuiala cu tipul tip
    :param tip: string
    :param cheltuiala: o cheltuiala cu o zi int
    :return: -
    """
    cheltuiala["tip"] = tip

def cheltuieliEgale(cheltuiala1, cheltuiala2):
    """
    Functie care verifica daca cheltuielile cheltuiala1 si cheltuiala2 sunt egale / au acelasi id
    :param cheltuiala1: o cheltuiala cu un id int
    :param cheltuiala2: o cheltuiala cu un id int
    :return: True daca cheltuielile cheltuiala1 si cheltuiala2 au acelasi id
             False daca cheltuielile cheltuiala1 si cheltuiala2 nu au acelasi id
    """
    return getIDCheltuiala(cheltuiala1) == getIDCheltuiala(cheltuiala2)

def printCheltuiala(cheltuiala):
    """
    Functia ajuta la afisarea mai explicita a datelor cheltuielii cheltuiala
    :param cheltuiala: o cheltuiala cu un id int, ziua zi, suma suma si tipul tip
    :return: Un sir pentru a reprezenta in detaliu fiecare atribut al cheltuielii cheltuiala
    """
    return f"Cheltuiala cu ID-ul {getIDCheltuiala(cheltuiala)}, din ziua {getZiuaCheltuiala(cheltuiala)}, de {getSumaCheltuiala(cheltuiala)} bani, pentru {getTipCheltuiala(cheltuiala)}"