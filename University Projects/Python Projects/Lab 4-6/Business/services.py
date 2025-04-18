# services.py

"""
Modulul oferă funcționalități pentru crearea, actualizarea, ștergerea și căutarea cheltuielilor.
În plus, include funcționalități de filtrare a cheltuielilor și poate obține rapoarte statistice.
"""

from Domain.cheltuiala import *

def existsCheltuiala(cheltuiala, cheltuieli):
    """
    Functia verifica daca cheltuiala cheltuiala exista in cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param cheltuiala: o cheltuiala cu un id int
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: True daca cheltuiala cu id-ul idc exista in cheltuieli
             False daca cheltuiala cu id-ul idc nu exista in cheltuieli
    """
    if getIDCheltuiala(cheltuiala) in cheltuieli:
        return True
    return False

def addCheltuiala(cheltuiala, cheltuieli):
    """
    Functia adauga cheltuiala cheltuiala, daca nu exista deja, in cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param cheltuiala: o cheltuiala cu un id int
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: True daca cheltuiala cheltuiala a fost adaugata cu succes in cheltuieli
             False daca o cheltuiala cu acelasi id exista deja in cheltuieli si nu a fost adaugata
    """
    if existsCheltuiala(cheltuiala, cheltuieli):
        return False
    cheltuieli[getIDCheltuiala(cheltuiala)] = cheltuiala
    return True

def updateCheltuiala(cheltuiala, zi, suma, tip, cheltuieli):
    """
    Functia actualizeaza datele cheltuielii cheltuiala din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic,
    cu o noua zi zi, o suma suma, si un tip tip
    :param cheltuiala: o cheltuiala cu un id int
    :param zi: int
    :param suma: float
    :param tip: string
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: -
    """
    setZiuaCheltuiala(zi, cheltuiala)
    setSumaCheltuiala(suma, cheltuiala)
    setTipCheltuiala(tip, cheltuiala)
    cheltuieli[getIDCheltuiala(cheltuiala)] = cheltuiala

def removeCheltuialaDinZi(zi, cheltuieli):
    """
    Functia cauta cheltuielile efectuate in ziua zi din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic, si le sterge
    :param zi: int
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: Numarul de cheltuieli sterse din cheltuieli
    """
    cnt = 0
    cheltuieli_copy = cheltuieli.copy()
    for idc, cheltuiala in cheltuieli_copy.items():
        if getZiuaCheltuiala(cheltuiala) == zi:
            cnt += 1
            cheltuieli.pop(idc)
    return cnt

def removeCheltuialaInterval(zi_inceput, zi_sfarsit, cheltuieli):
    """
    Functia cauta cheltuielile efectuate intre ziua zi_inceput si ziua zi_sfarsit din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic, si le sterge
    :param zi_inceput: int
    :param zi_sfarsit: int
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: Numarul de cheltuieli sterse din cheltuieli
    """
    cnt = 0
    cheltuieli_copy = cheltuieli.copy()
    for idc, cheltuiala in cheltuieli_copy.items():
        if zi_inceput <= getZiuaCheltuiala(cheltuiala) <= zi_sfarsit:
            cnt += 1
            cheltuieli.pop(idc)
    return cnt

def removeCheltuialaTip(tip, cheltuieli):
    """
    Functia cauta cheltuielile efectuate de tipul tip din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic, si le sterge
    :param tip: string
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: Numarul de cheltuieli sterse din cheltuieli
    """
    cnt = 0
    cheltuieli_copy = cheltuieli.copy()
    for idc, cheltuiala in cheltuieli_copy.items():
        if getTipCheltuiala(cheltuiala) == tip:
            cnt += 1
            cheltuieli.pop(idc)
    return cnt

def searchCheltuialaMaiMareCaSum(suma, cheltuieli):
    """
    Functia cauta cheltuielile cu o suma mai mare sau egala decat suma suma din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param suma: float
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o lista cu cheltuieli care au suma mai mare sau egala decat suma suma
    """
    solutie = []
    for idc, cheltuiala in cheltuieli.items():
        if getSumaCheltuiala(cheltuiala) >= suma:
            solutie.append(cheltuiala)
    return solutie

def searchCheltuialaZiSiSum(zi, suma, cheltuieli):
    """
    Functia cauta cheltuielile efectuate inainte de ziua zi
    si cu o suma mai mica decat suma suma din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param zi: int
    :param suma: float
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o lista cu cheltuieli care au fost efectuate inainte de ziua zi
    si cu o suma mai mica decat suma suma
    """
    solutie = []
    for idc, cheltuiala in cheltuieli.items():
        if (getZiuaCheltuiala(cheltuiala) < zi
                and getSumaCheltuiala(cheltuiala) < suma):
            solutie.append(cheltuiala)
    return solutie

def searchCheltuialaTip(tip, cheltuieli):
    """
    Functia cauta cheltuielile de tipul tip din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param tip: string
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o lista cu cheltuieli care sunt de tipul tip
    """
    solutie = []
    for idc, cheltuiala in cheltuieli.items():
        if getTipCheltuiala(cheltuiala) == tip:
            solutie.append(cheltuiala)
    return solutie

def raportSumaTotala(tip, cheltuieli):
    """
    Functia calculeaza suma totala a cheltuielilor de tipul tip din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param tip: string
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: suma float a tuturor cheltuielilor de tipul tip
    """
    suma = 0
    for idc, cheltuiala in cheltuieli.items():
        if getTipCheltuiala(cheltuiala) == tip:
            suma += getSumaCheltuiala(cheltuiala)
    return suma

def sumaZi(zi, cheltuieli):
    """
    Functia calculeaza suma totala a cheltuielilor efectuate in ziua zi din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param zi: int
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: suma float a tuturor cheltuielilor din ziua zi
    """
    suma = 0
    for idc, cheltuiala in cheltuieli.items():
        if getZiuaCheltuiala(cheltuiala) == zi:
            suma += getSumaCheltuiala(cheltuiala)
    return suma

def raportFindZiSumaMaxima(cheltuieli):
    """
    Functia gaseste ziua in care suma cheltuielilor din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic, e maxima
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: ziua int in care suma cheltuita e maxima
    """
    zi = 0
    suma_max = 0
    for idc, cheltuiala in cheltuieli.items():
        suma = sumaZi(getZiuaCheltuiala(cheltuiala), cheltuieli)
        if suma > suma_max:
            suma_max = suma
            zi = getZiuaCheltuiala(cheltuiala)
    return zi

def raportSumaSpecifica(suma, cheltuieli):
    """
    Functia cauta cheltuielile care au suma egala cu suma suma din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param suma: float
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o lista cu cheltuieli care au suma egala cu suma suma
    """
    solutie = []
    epsilon = 0.0001
    for idc, cheltuiala in cheltuieli.items():
        if abs(getSumaCheltuiala(cheltuiala) - suma) < epsilon:
            solutie.append(cheltuiala)
    return solutie

def raportCheltuieliSortate(cheltuieli):
    """
    Functia sorteaza cheltuielile din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic,
    dupa tipul cheltuielilor
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: un dictionar in care cheltuielile sunt sortate dupa tip
    """
    cheltuieli_copy = cheltuieli.copy()
    cheltuieli_copy = dict(sorted(cheltuieli_copy.items(), key=lambda x: x[1]["tip"]))
    return cheltuieli_copy

def filterByTip(tip, cheltuieli):
    """
    Functia cauta cheltuielile care nu sunt de tipul tip din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param tip: string
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o lista cu cheltuieli care nu sunt de tipul tip
    """
    solutie = []
    for idc, cheltuiala in cheltuieli.items():
        if getTipCheltuiala(cheltuiala) != tip:
            solutie.append(cheltuiala)
    return solutie

def filterBySuma(suma, cheltuieli):
    """
    Functia cauta cheltuielile care sunt mai mari decat suma suma din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic
    :param suma: float
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o lista cu cheltuieli care au suma mai mare sau egala cu suma suma
    """
    solutie = []
    for idc, cheltuiala in cheltuieli.items():
        if getSumaCheltuiala(cheltuiala) >= suma:
            solutie.append(cheltuiala)
    return solutie
    # !!!

def copiereProfunda(cheltuieli):
    """
    Functia parcurge recursiv fiecare cheie și valoare din cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic.
    Dacă găsește un sub-dicționar, îl copiază recursiv, astfel încât fiecare nivel este duplicat în întregime.
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :return: o copie profunda a dictionarului cheltuieli
    """
    copy = {}
    for key, value in cheltuieli.items():
        if isinstance(value, dict):
            copy[key] = copiereProfunda(value)
        else:
            copy[key] = value
    return copy

def saveIstoric(cheltuieli, istoric):
    """
    Functia adauga in lista istoric o copie profunda a dictionarului cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic.
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :param istoric: o lista in care se retine o copie profunda a dictionarului cheltuieli
    :return: -
    """
    istoric.append(copiereProfunda(cheltuieli))

def undoChanges(cheltuieli, istoric):
    """
    Functia elimina din lista istoric ultimul element, goleste dictionarul de cheltuieli,
    care contine cheltuieli ce pot fi identificate dupa un id int unic, si salveaza in undo ultimul element din lista istoric.
    Cheltuieli este in final actualizat cu undo.
    :param cheltuieli: un dictionar care contine chei unice care reprezinta id-urile unice ale
    cheltuielilor si valorile acestora care corespund id-ului int
    :param istoric: o lista in care sunt retinute copii profunde a dictionarului cheltuieli
    :return: -
    """
    istoric.pop()
    cheltuieli.clear()
    undo = istoric[-1]
    cheltuieli.update(undo)