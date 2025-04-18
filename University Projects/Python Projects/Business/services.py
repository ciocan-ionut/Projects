# services.py

"""
Modulul oferă funcționalități pentru crearea, actualizarea, ștergerea și căutarea cheltuielilor.
În plus, include funcționalități de filtrare a cheltuielilor și poate obține rapoarte statistice.
"""
from Domain.cheltuiala import getIDCheltuiala, getZiuaCheltuiala, getTipCheltuiala, getSumaCheltuiala


def getIndexCheltuiala(lista_cheltuieli, cheltuiala):
    """
    Functia returneaza (daca exista) pozitia cheltuielii in lista de cheltuieli
    input: - lista de cheltuieli
           - cheltuiala
    output: - indicele / -1 (dupa caz)
    """
    for cheltuiala_curenta in lista_cheltuieli:
        if cheltuiala == cheltuiala_curenta:
            return lista_cheltuieli.index(cheltuiala)
    return -1

def existsCheltuiala(dictionar_cheltuieli, cheltuiala):
    """
    Functia verifica daca o cheltuiala exista deja in lista de cheltuieli
    input: - lista de cheltuieli
           - cheltuiala
    output: - True / False (dupa caz)
    """
    if getIDCheltuiala(cheltuiala) in dictionar_cheltuieli:
        return True
    return False

def addCheltuiala(dictionar_cheltuiala, cheltuiala):
    """
    Functia adauga (daca nu exista deja) o cheltuiala in lista de cheltuieli
    input: - lista de cheltuieli
           - cheltuiala
    output: - False (daca cheltuiala exista deja)
    """
    if existsCheltuiala(dictionar_cheltuiala, cheltuiala):
        return False
    dictionar_cheltuiala[getIDCheltuiala(cheltuiala)] = cheltuiala
    return True

def updateCheltuiala(dictionar_cheltuieli, old_cheltuiala, new_cheltuiala):
    """
    Functia actualizeaza o cheltuiala din lista de cheltuieli
    input: - lista de cheltuieli
           - cheltuiala care este actualizata
           - cheltuiala cu care se va actualiza
    """
    dictionar_cheltuieli[getIDCheltuiala(old_cheltuiala)] = new_cheltuiala

def removeCheltuialaDinZi(dictionar_cheltuieli, zi):
    """
    Functia sterge toate cheltuielile dintr-o zi data
    input: - lista de cheltuieli
           - ziua (numar natural)
    output: - numarul de cheltuieli sterse (numar natural)
    """
    cnt = 0
    copy = dict(dictionar_cheltuieli)
    for cheltuiala in copy:
        if getZiuaCheltuiala(dictionar_cheltuieli[cheltuiala]) == zi:
            cnt += 1
            dictionar_cheltuieli.pop(cheltuiala)
    return cnt

def removeCheltuialaInterval(dictionar_cheltuieli, zi_inceput, zi_sfarsit):
    """
    Functia sterge toate cheltuielile efectuate intre doua zile date
    input: - lista de cheltuieli
           - ziua de inceput (numar natural, zi_inceput <= zi_sfarsit)
           - ziua de sfarsit (numar natural)
    output: - numarul de cheltuieli sterse (numar natural)
    """
    cnt = 0
    copy = dict(dictionar_cheltuieli)
    for cheltuiala in copy:
        if zi_inceput <= getZiuaCheltuiala(dictionar_cheltuieli[cheltuiala]) <= zi_sfarsit:
            cnt += 1
            dictionar_cheltuieli.pop(cheltuiala)
    return cnt

def removeCheltuialaTip(dictionar_cheltuieli, tip):
    """
    Functia sterge toate cheltuielile de un anumit tip dat
    input: - lista de cheltuieli
           - tipul cheltuielii
    output: - numarul de cheltuieli sterse (numar natural)
    """
    cnt = 0
    copy = dict(dictionar_cheltuieli)
    for cheltuiala in copy:
        if getTipCheltuiala(dictionar_cheltuieli[cheltuiala]) == tip:
            cnt += 1
            dictionar_cheltuieli.pop(cheltuiala)
    return cnt

def searchCheltuialaMaiMareCaSum(dictionar_cheltuieli, suma):
    """
    Functia cauta cheltuielile cu suma mai mare decat o suma data
    input: - lista de cheltuieli
           - suma (numar real)
    output: - lista de cheltuieli care respecta conditia
    """
    solutie = {}
    for cheltuiala in dictionar_cheltuieli:
        if getSumaCheltuiala(cheltuiala) >= suma:
            solutie[getIDCheltuiala(cheltuiala)] = cheltuiala
    return solutie

def searchCheltuialaZiSiSum(dictionar_cheltuieli, zi, suma):
    """
    Functia cauta cheltuielile facute inainte de o zi data si mai mici decat o suma data
    input: - lista de cheltuieli
           - zi (numar natural)
           - suma (numar real)
    output: - lista de cheltuieli care respecta conditia
    """
    solutie = {}
    for cheltuiala in dictionar_cheltuieli:
        if getZiuaCheltuiala(dictionar_cheltuieli[cheltuiala]) < zi and getSumaCheltuiala(dictionar_cheltuieli[cheltuiala]) < suma:
            solutie[getIDCheltuiala(dictionar_cheltuieli[cheltuiala])] = cheltuiala
    return solutie

def searchCheltuialaTip(dictionar_cheltuieli, tip):
    """
    Functia cauta cheltuielile de un anumit tip dat
    input: - lista de cheltuieli
           - tip (tipul cheltuielii)
    output: - lista de cheltuieli care respecta conditia
    """
    solutie = {}
    for cheltuiala in dictionar_cheltuieli:
        if getTipCheltuiala(dictionar_cheltuieli[cheltuiala]) == tip:
            solutie[getIDCheltuiala(cheltuiala)] = cheltuiala
    return solutie

def raportSumaTotala(dictionar_cheltuieli, tip):
    """
    Functia calculeaza suma totala pentru un anumit tip de cheltuiala
    input: - lista de cheltuieli
           - tipul
    output: - suma totala pentru tipul de cheltuiala specificat
    """
    suma = 0
    for cheltuiala in dictionar_cheltuieli:
        if getTipCheltuiala(dictionar_cheltuieli[cheltuiala]) == tip:
            suma += getSumaCheltuiala(dictionar_cheltuieli[cheltuiala])
    return suma

def sumaZi(dictionar_cheltuieli, zi):
    """
    Functia calculeaza suma tuturor cheltuielilor dintr-o zi data
    input: - lista de cheltuieli
           - zi
    output: - suma tuturor cheltuielilor din ziua specificata /
              0 in cazul in care nu exista cheltuieli in lista
    """
    suma = 0
    for cheltuiala in dictionar_cheltuieli:
        if getZiuaCheltuiala(dictionar_cheltuieli[cheltuiala]) == zi:
            suma += getSumaCheltuiala(dictionar_cheltuieli[cheltuiala])
    return suma

def raportFindZiSumaMaxima(dictionar_cheltuieli):
    """
    Functia cauta ziua in care suma cheltuita e maxima
    input: - lista de cheltuieli
    output: - ziua in care suma cheltuita e maxima /
              0 in cazul in care nu exista cheltuieli in lista
    """
    zi = 0
    suma_max = 0
    for cheltuiala in dictionar_cheltuieli:
        suma = sumaZi(dictionar_cheltuieli, getZiuaCheltuiala(dictionar_cheltuieli[cheltuiala]))
        if suma > suma_max:
            suma_max = suma
            zi = getZiuaCheltuiala(dictionar_cheltuieli[cheltuiala])
    return zi

def raportSumaSpecifica(dictionar_cheltuieli, suma):
    """
    Functia cauta cheltuielile ce au suma egala cu suma data
    input: - lista de cheltuieli
           - suma
    output: - lista de cheltuieli care respecta conditia
    """
    solutie = {}
    for cheltuiala in dictionar_cheltuieli:
        if getSumaCheltuiala(dictionar_cheltuieli[cheltuiala]) == suma:
            solutie[getIDCheltuiala(dictionar_cheltuieli[cheltuiala])] = dictionar_cheltuieli[cheltuiala]
    return solutie

def sortareTip(cheltuiala):
    """
    Functia returneaza tipul unei cheltuieli.
    Specifica functiei raportCheltuieliSortate criteriul dupa care se va sorta lista de cheltuieli
    input: - cheltuiala
    output: - tipul cheltuielii
    """
    return cheltuiala.getTip()

def raportCheltuieliSortate(dictionar_cheltuieli):
    """
    Functia sorteaza lista de cheltuieli dupa tip
    input: - lista de cheltuieli
    output: - lista de cheltuieli sortata
    """
    dictionar_cheltuieli.sort(key=getTipCheltuiala)
    return dictionar_cheltuieli

def filterByTip(dictionar_cheltuieli, tip):
    """
    Functia elimina cheltuielile de un anumit tip dat
    input: - lista de cheltuieli
           - tipul
    output: - lista de cheltuieli care respecta conditia
    """
    solutie = []
    for cheltuiala in dictionar_cheltuieli:
        if getTipCheltuiala(cheltuiala) != tip:
            solutie[getIDCheltuiala(dictionar_cheltuieli[cheltuiala])] = cheltuiala
    return solutie

def filterBySuma(dictionar_cheltuieli, suma):
    """
    Functia elimina cheltuielile mai mici decat o suma data
    input: - lista de cheltuieli
           - suma (numar real)
    output: - lista de cheltuieli care respecta conditia
    """
    solutie = {}
    for cheltuiala in dictionar_cheltuieli:
        if getSumaCheltuiala(dictionar_cheltuieli[cheltuiala]) >= suma:
            solutie[getIDCheltuiala(dictionar_cheltuieli[cheltuiala])] = cheltuiala
    return solutie