# teste.py

"""
Modulul cuprinde teste dedicate fiecărei funcții din aplicație pentru a asigura buna funcționare a programului,
folosind o serie de cheltuieli cunoscute.

Prin apelarea functiei 'run_tests()' rulam toate testele.
"""

from Business.services import *
from Domain.cheltuiala import *


def test_createCheltuiala():
    epsilon = 0.0001
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    cheltuiala = createCheltuiala(idc, zi, suma, tip)
    assert idc == getIDCheltuiala(cheltuiala)
    assert zi == getZiuaCheltuiala(cheltuiala)
    assert abs(suma - getSumaCheltuiala(cheltuiala)) < epsilon
    assert tip == getTipCheltuiala(cheltuiala)

def test_addCheltuiala():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    cheltuiala = createCheltuiala(idc, zi, suma, tip)
    assert addCheltuiala(cheltuiala, cheltuieli) == True
    assert addCheltuiala(cheltuiala, cheltuieli) == False

def test_existsCheltuiala():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 7
    suma = 148
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    assert existsCheltuiala(c1, cheltuieli) == True
    assert existsCheltuiala(c2, cheltuieli) == False

def test_updateCheltuiala():
    epsilon = 0.0001
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    cheltuiala = createCheltuiala(idc, zi, suma, tip)
    new_zi = 7
    new_suma = 148
    new_tip = "Altele"
    updateCheltuiala(cheltuiala, new_zi, new_suma, new_tip, cheltuieli)
    assert getZiuaCheltuiala(cheltuiala) == new_zi
    assert abs(getSumaCheltuiala(cheltuiala) - new_suma) < epsilon
    assert getTipCheltuiala(cheltuiala) == new_tip

def test_removeCheltuialaDinZi():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 13
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 3
    zi = 13
    suma = 31
    tip = "Mancare"
    c7 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c7, cheltuieli)
    assert removeCheltuialaDinZi(13, cheltuieli) == 2
    assert cheltuieli == {1: c1}
    assert removeCheltuialaDinZi(25, cheltuieli) == 0

def test_removeCheltuialaInterval():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 21
    suma = 1207
    tip = "Intretinere"
    c4 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c4, cheltuieli)
    idc = 4
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    idc = 5
    zi = 21
    suma = 25
    tip = "Telefon"
    c6 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c6, cheltuieli)
    assert removeCheltuialaInterval(20, 25, cheltuieli) == 3
    assert cheltuieli == {1: c1, 2: c2}
    assert removeCheltuialaInterval(20, 25, cheltuieli) == 0

def test_removeCheltuialaTip():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 13
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 4
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    assert removeCheltuialaTip("Mancare", cheltuieli) == 2
    assert cheltuieli == {1: c1, 2: c2}
    assert removeCheltuialaTip("Mancare", cheltuieli) == 0

def test_searchCheltuialaMaiMareCaSum():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 21
    suma = 1207
    tip = "Intretinere"
    c4 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c4, cheltuieli)
    assert searchCheltuialaMaiMareCaSum(200, cheltuieli) == [c2, c4]
    assert searchCheltuialaMaiMareCaSum(3000, cheltuieli) == []

def test_searchCheltuialaZiSiSum():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 13
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 4
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    assert searchCheltuialaZiSiSum(14, 200, cheltuieli) == [c1, c3]
    assert searchCheltuialaZiSiSum(14, 300, cheltuieli) == [c1, c2, c3]
    assert searchCheltuialaZiSiSum(25, 300, cheltuieli) == [c1, c2, c3, c5]

def test_searchCheltuialaTip():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 13
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 4
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    assert searchCheltuialaTip("Mancare", cheltuieli) == [c3, c5]
    assert searchCheltuialaTip("Altele", cheltuieli) == [c2]
    assert searchCheltuialaTip("Intretinere", cheltuieli) == []

def test_raportSumaTotala():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 3
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    epsilon = 0.0001
    assert abs(raportSumaTotala("Mancare", cheltuieli) - 154.58) < epsilon
    assert abs(raportSumaTotala("Telefon", cheltuieli) - 150.12) < epsilon

def test_sumaZi():
    cheltuieli = {}
    idc = 1
    zi = 13
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 2
    zi = 13
    suma = 31
    tip = "Mancare"
    c7 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c7, cheltuieli)
    idc = 3
    zi = 13
    suma = 78
    tip = "Telefon"
    c8 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c8, cheltuieli)
    epsilon = 0.0001
    assert abs(sumaZi(13, cheltuieli) - 238.58) < epsilon
    assert sumaZi(1, cheltuieli) < epsilon

def test_raportFindZiSumaMaxima():
    cheltuieli = {}
    idc = 1
    zi = 13
    suma = 129.58
    tip = "Mancare"
    c3 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c3, cheltuieli)
    idc = 2
    zi = 21
    suma = 1207
    tip = "Intretinere"
    c4 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c4, cheltuieli)
    idc = 3
    zi = 13
    suma = 31
    tip = "Mancare"
    c7 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c7, cheltuieli)
    idc = 4
    zi = 13
    suma = 78
    tip = "Telefon"
    c8 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c8, cheltuieli)
    assert raportFindZiSumaMaxima(cheltuieli) == 21

def test_raportSumaSpecifica():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    idc = 4
    zi = 21
    suma = 25
    tip = "Telefon"
    c6 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c6, cheltuieli)
    assert raportSumaSpecifica(25, cheltuieli) == [c5, c6]
    assert raportSumaSpecifica(1234, cheltuieli) == []

def test_raportCheltuieliSortate():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    idc = 4
    zi = 21
    suma = 25
    tip = "Telefon"
    c6 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c6, cheltuieli)
    assert raportCheltuieliSortate(cheltuieli) == {2: c2, 3: c5, 1: c1, 4: c6}

def test_filterByTip():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    idc = 4
    zi = 21
    suma = 25
    tip = "Telefon"
    c6 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c6, cheltuieli)
    assert filterByTip("Telefon", cheltuieli) == [c2, c5]
    assert cheltuieli == {1: c1, 2: c2, 3: c5, 4: c6}

def test_filterBySuma():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    idc = 3
    zi = 24
    suma = 25
    tip = "Mancare"
    c5 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c5, cheltuieli)
    idc = 4
    zi = 21
    suma = 25
    tip = "Telefon"
    c6 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c6, cheltuieli)
    assert filterBySuma(30, cheltuieli) == [c1, c2]
    assert cheltuieli == {1: c1, 2: c2, 3: c5, 4: c6}

def test_copiereProfunda():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    copy = copiereProfunda(cheltuieli)
    assert cheltuieli == copy

def test_saveIstoric():
    cheltuieli = {}
    idc = 1
    zi = 1
    suma = 150.12
    tip = "Telefon"
    c1 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c1, cheltuieli)
    idc = 2
    zi = 2
    suma = 253.2
    tip = "Altele"
    c2 = createCheltuiala(idc, zi, suma, tip)
    addCheltuiala(c2, cheltuieli)
    istoric = []
    saveIstoric(cheltuieli, istoric)
    assert istoric[0] == cheltuieli

def run_tests():
    test_createCheltuiala()
    test_addCheltuiala()
    test_existsCheltuiala()
    test_updateCheltuiala()
    test_removeCheltuialaDinZi()
    test_removeCheltuialaInterval()
    test_removeCheltuialaTip()
    test_searchCheltuialaMaiMareCaSum()
    test_searchCheltuialaZiSiSum()
    test_searchCheltuialaTip()
    test_raportSumaTotala()
    test_sumaZi()
    test_raportFindZiSumaMaxima()
    test_raportSumaSpecifica()
    test_raportCheltuieliSortate()
    test_filterByTip()
    test_filterBySuma()
    test_copiereProfunda()
    test_saveIstoric()