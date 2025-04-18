# test.py

"""
Modulul cuprinde teste dedicate fiecărei funcții din aplicație pentru a asigura buna funcționare a programului,
folosind o serie de cheltuieli cunoscute.

Prin apelarea functiei 'run_tests()' rulam toate testele.
"""

from Business.services import *
# from Domain.cheltuiala import Cheltuiala, createCheltuiala

def setup():
    # Functia initializeaza lista de cheltuieli si cheltuielile de test
    lista_test = []
    c1 = Cheltuiala(1, 150.12, "Telefon")
    c2 = Cheltuiala(2, 253.2, "Altele")
    c3 = Cheltuiala(13, 129.58, "Mancare")
    c4 = Cheltuiala(21, 1207, "Intretinere")
    c5 = Cheltuiala(24, 25, "Mancare")
    c6 = Cheltuiala(21, 25, "Telefon")
    c7 = Cheltuiala(13, 31, "Mancare")
    c8 = Cheltuiala(13, 78, "Telefon")
    return lista_test, c1, c2, c3, c4, c5, c6, c7, c8

def test_createCheltuiala():
    # Functia testeaza functia 'createCheltuiala'
    lista_teste, c1, _, _, _, _, _, _, _ = setup()
    assert createCheltuiala(1, 150.12, "Telefon") == c1

def test_addCheltuiala():
    # Functia testeaza functia 'addCheltuiala'
    lista_teste, c1, _, _, _, _, _, _, _ = setup()
    assert addCheltuiala(lista_teste, c1) == True

def test_updateCheltuiala():
    # Functia testeaza functia 'updateCheltuiala'
    lista_teste, c1, c2, _, _, _, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    updateCheltuiala(lista_teste, c1, c2)
    assert existsCheltuiala(lista_teste, c2) == True

def test_existsCheltuiala():
    # Functia testeaza functia 'existsCheltuiala'
    lista_teste, c1, c2, _, _, _, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    assert existsCheltuiala(lista_teste, c1) == True
    assert existsCheltuiala(lista_teste, c2) == False

def test_getIndexCheltuiala():
    # Functia testeaza functia 'getIndexCheltuiala'
    lista_teste, c1, c2, _, _, _, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    assert getIndexCheltuiala(lista_teste, c1) == 0
    assert getIndexCheltuiala(lista_teste, c2) == -1

def test_removeCheltuialaDinZi():
    # Functia testeaza functia 'removeCheltuialaDinZi'
    lista_teste, c1, _, c3, _, _, _, c7, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c7)
    assert removeCheltuialaDinZi(lista_teste, 13) == 2
    assert lista_teste == [c1]
    assert removeCheltuialaDinZi(lista_teste, 25) == 0

def test_removeCheltuialaInterval():
    # Functia testeaza functia 'removeCheltuialaInterval'
    lista_teste, c1, c2, _, c4, c5, c6, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c4)
    addCheltuiala(lista_teste, c5)
    addCheltuiala(lista_teste, c6)
    assert removeCheltuialaInterval(lista_teste, 20, 25) == 3
    assert lista_teste == [c1, c2]
    assert removeCheltuialaInterval(lista_teste, 20, 25) == 0

def test_removeCheltuialaTip():
    # Functia testeaza functia 'removeCheltuialaTip'
    lista_teste, c1, c2, c3, _, c5, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c5)
    assert removeCheltuialaTip(lista_teste, "Mancare") == 2
    assert lista_teste == [c1, c2]
    assert removeCheltuialaTip(lista_teste, "Mancare") == 0

def test_searchCheltuialaMaiMareCaSum():
    # Functia testeaza functia 'searchCheltuialaMaiMareCaSum'
    lista_teste, c1, c2, _, c4, _, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c4)
    assert searchCheltuialaMaiMareCaSum(lista_teste, 200) == [c2, c4]
    assert searchCheltuialaMaiMareCaSum(lista_teste, 3000) == []

def test_searchCheltuialaZiSiSum():
    # Functia testeaza functia 'searchCheltuialaZiSiSum'
    lista_teste, c1, c2, c3, _, c5, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c5)
    assert searchCheltuialaZiSiSum(lista_teste,14,200) == [c1, c3]
    assert searchCheltuialaZiSiSum(lista_teste,14,300) == [c1, c2, c3]
    assert searchCheltuialaZiSiSum(lista_teste, 25, 300) == [c1, c2, c3, c5]

def test_searchCheltuialaTip():
    # Functia testeaza functia 'searchCheltuialaTip'
    lista_teste, c1, c2, c3, _, c5, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c5)
    assert searchCheltuialaTip(lista_teste, "Mancare") == [c3, c5]
    assert searchCheltuialaTip(lista_teste, "Altele") == [c2]
    assert searchCheltuialaTip(lista_teste, "Intretinere") == []

def test_raportSumaTotala():
    # Functia testeaza functia 'raportSumaTotala'
    lista_teste, c1, _, c3, _, c5, _, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c5)
    assert raportSumaTotala(lista_teste, "Mancare") == 154.58
    assert raportSumaTotala(lista_teste, "Telefon") == 150.12

def test_sumaZi():
    # Functia testeaza functia 'sumaZi'
    lista_teste, _, _, c3, _, _, _, c7, c8 = setup()
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c7)
    addCheltuiala(lista_teste, c8)
    assert sumaZi(lista_teste, 13) == 238.58
    assert sumaZi(lista_teste, 1) == 0

def test_raportFindZiSumaMaxima():
    # Functia testeaza functia 'raportFindZiSumaMaxima'
    lista_teste, _, _, c3, c4, _, _, c7, c8 = setup()
    addCheltuiala(lista_teste, c3)
    addCheltuiala(lista_teste, c4)
    addCheltuiala(lista_teste, c7)
    addCheltuiala(lista_teste, c8)
    assert raportFindZiSumaMaxima(lista_teste) == 21

def test_raportSumaSpecifica():
    # Functia testeaza functia 'raportSumaSpecifica'
    lista_teste, c1, c2, _, _, c5, c6, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c5)
    addCheltuiala(lista_teste, c6)
    assert raportSumaSpecifica(lista_teste,25) == [c5,c6]
    assert raportSumaSpecifica(lista_teste,1234) == []

def test_sortareTip():
    # Functia testeaza functia 'sortareTip'
    _, c1, _, _, _, _, _, _, _ = setup()
    assert sortareTip(c1) == "Telefon"

def test_raportCheltuieliSortate():
    # Functia testeaza functia 'raportCheltuieliSortate'
    lista_teste, c1, c2, _, _, c5, c6, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c5)
    addCheltuiala(lista_teste, c6)
    assert raportCheltuieliSortate(lista_teste) == [c2, c5, c1, c6]

def test_filterByTip():
    # Functia testeaza functia 'filterByTip'
    lista_teste, c1, c2, _, _, c5, c6, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c5)
    addCheltuiala(lista_teste, c6)
    assert filterByTip(lista_teste, "Telefon") == [c2, c5]
    assert lista_teste == [c1, c2, c5, c6]

def test_filterBySuma():
    # Functia testeaza functia 'filterBySuma'
    lista_teste, c1, c2, _, _, c5, c6, _, _ = setup()
    addCheltuiala(lista_teste, c1)
    addCheltuiala(lista_teste, c2)
    addCheltuiala(lista_teste, c5)
    addCheltuiala(lista_teste, c6)
    assert filterBySuma(lista_teste, 30) == [c1, c2]
    assert lista_teste == [c1, c2, c5, c6]

def run_tests():
    # Functia apeleaza toate testele
    test_createCheltuiala()
    test_addCheltuiala()
    test_updateCheltuiala()
    test_existsCheltuiala()
    test_getIndexCheltuiala()
    test_removeCheltuialaDinZi()
    test_removeCheltuialaInterval()
    test_removeCheltuialaTip()
    test_searchCheltuialaMaiMareCaSum()
    test_searchCheltuialaZiSiSum()
    test_searchCheltuialaTip()
    test_raportSumaTotala()
    test_sumaZi()
    test_raportFindZiSumaMaxima()
    test_raportCheltuieliSortate()
    test_sortareTip()
    test_raportCheltuieliSortate()
    test_filterByTip()
    test_filterBySuma()

if __name__ == '__main__':
    run_tests()