# menu.py

"""
Modulul permite utilizatorului să adauge, să șteargă, să caute și să genereze rapoarte
privind cheltuielile unei familii. În plus, include și funcționalități pentru filtrare și undo.

Prin apelarea functiei 'run()' se pornește aplicația.
"""

import os
from Domain.cheltuiala import createCheltuiala, printCheltuiala
from Business.services import addCheltuiala, existsCheltuiala, updateCheltuiala
from Business.services import removeCheltuialaDinZi, removeCheltuialaInterval, removeCheltuialaTip
from Business.services import searchCheltuialaMaiMareCaSum, searchCheltuialaZiSiSum, searchCheltuialaTip
from Business.services import raportSumaTotala, raportFindZiSumaMaxima, raportSumaSpecifica, raportCheltuieliSortate
from Business.services import filterByTip, filterBySuma

def clearScreen():
    # Functia goleste consola aplicatiei
    os.system('cls' if os.name == 'nt' else 'clear')

def MainMenu():
    # Functie care afiseaza meniul principal al aplicatiei
    print("Cheltuieli de familie")
    print("1. Adauga cheltuiala")
    print("2. Stergere")
    print("3. Cautari")
    print("4. Rapoarte")
    print("5. Filtrare")
    print("6. Undo")
    print("7. Iesire")

def run():
    # Functia dirijeaza functionalitatea meniului principal
    # lista_cheltuieli = []
    dictionar_cheltuieli = {}
    while True:
        MainMenu()
        option = input("Alegeti o optiune de la 1 la 7: ")
        match option:
            case "1":
                AddMenu_run(dictionar_cheltuieli)
            case "2":
                RemoveMenu_run(dictionar_cheltuieli)
            case "3":
                SearchMenu_run(dictionar_cheltuieli)
            case "4":
                RaportMenu_run(dictionar_cheltuieli)
            case "5":
                FilterMenu_run(dictionar_cheltuieli)
            case "7":
                print("Iesire din aplicatie. La revedere!")
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

def getIDUser():
    while True:
        try:
            id = int(input("Introduceti id (valoare strict pozitiva): "))
            if id <= 0:
                raise ValueError
            break
        except ValueError:
            print("Optiune invalida. Va rugam sa incercati din nou.")
    return id

def getZiUser():
    """
    Functia preia de la utilizator o anumita zi din luna unui an
    output: - ziua (numar natural din intervalul [1, 31])
    """
    while True:
        try:
            zi = int(input("Introduceti ziua (valoare de la 1 la 31): "))
            if zi < 1 or zi > 31:
                raise ValueError
            break
        except ValueError:
            print("Optiune invalida. Va rugam sa incercati din nou.")
    return zi

def getSumaUser():
    """
    Functia preia de la utilizator o anumita suma
    output: - suma (numar real > 0)
    """
    while True:
        try:
            suma = float(input("Introduceti suma (valoare strict pozitiva): "))
            if suma <= 0:
                raise ValueError
            break
        except ValueError:
            print("Optiune invalida. Va rugam sa incercati din nou.")
    return suma

def getTipUser():
    """
    Functia preia de la utilizator tipul unei cheltuieli
    output: - tipul cheltuielii
    """
    print("Introduceti tipul cheltuielii:")
    print("1. Mancare")
    print("2. Intretinere")
    print("3. Imbracaminte")
    print("4. Telefon")
    print("5. Altele")
    while True:
        try:
            option = int(input("Alegeti o optiune de la 1 la 5: "))
            match option:
                case 1:
                    tip = "mancare"
                    break
                case 2:
                    tip = "intretinere"
                    break
                case 3:
                    tip = "imbracaminte"
                    break
                case 4:
                    tip = "telefon"
                    break
                case 5:
                    tip = "altele"
                    break
                case _:
                    raise ValueError
        except ValueError:
            print("Optiune invalida. Va rugam sa incercati din nou.")
    return tip

def AddMenu():
    # Functie care afiseaza optiunile din meniul "Adauga cheltuiala"
    clearScreen()
    print("Adauga cheltuiala:")
    print("1. Adauga o cheltuiala")
    print("2. Actualizeaza o cheltuiala")
    print("3. Inapoi")

def AddMenu_run(dictionar_cheltuieli):
    # Functia dirijeaza functionalitatea meniului "Adauga cheltuiala"
    while True:
        AddMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                id = getIDUser()
                zi = getZiUser()
                suma = getSumaUser()
                tip = getTipUser()
                cheltuiala = createCheltuiala(id, zi, suma, tip)
                clearScreen()
                if addCheltuiala(dictionar_cheltuieli, cheltuiala):
                    print("Cheltuiala adaugata cu succes!")
                else:
                    print("Cheltuiala exista deja!")
                input("Apasati Enter pentru a continua...")
            case "2":
                print("Introduceti datele cheltuielii actualizate:")
                id = getIDUser()
                zi = getZiUser()
                suma = getSumaUser()
                tip = getTipUser()
                old_cheltuiala = createCheltuiala(id, zi, suma, tip)
                if not existsCheltuiala(dictionar_cheltuieli, old_cheltuiala):
                    clearScreen()
                    print("Cheltuiala nu exista!")
                else:
                    print("Introduceti noile date:")
                    id = getIDUser()
                    zi = getZiUser()
                    suma = getSumaUser()
                    tip = getTipUser()
                    new_cheltuiala = createCheltuiala(id, zi, suma, tip)
                    updateCheltuiala(dictionar_cheltuieli, old_cheltuiala, new_cheltuiala)
                    clearScreen()
                    print("Cheltuiala a fost actualizata!")
                input("Apasati Enter pentru a continua...")
            case "3":
                clearScreen()
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

def RemoveMenu():
    # Functie care afiseaza optiunile din meniul "Stergere"
    clearScreen()
    print("Stergere:")
    print("1. Sterge toate cheltuielile din ziua data")
    print("2. Sterge cheltuielile pentru un interval de timp")
    print("3. Sterge toate cheltuielile de un anumit tip")
    print("4. Inapoi")

def RemoveMenu_run(dictionar_cheltuieli):
    # Functia dirijeaza functionalitatea meniului "Stergere"
    while True:
        RemoveMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                zi = getZiUser()
                cnt = removeCheltuialaDinZi(dictionar_cheltuieli, zi)
                clearScreen()
                if cnt == 0:
                    print("Nu a fost stearsa nicio cheltuiala!")
                elif cnt == 1:
                    print("A fost stearsa o cheltuiala!")
                else:
                    print (f"Au fost sterse {cnt} cheltuieli!")
                input("Apasati Enter pentru a continua...")
            case "2":
                print("Introduceti capetele intervalului de timp:")
                print("Intervalul curent: [1, 31]")
                zi_inceput = getZiUser()
                print(f"Intervalul curent: [{zi_inceput}, 31]")
                zi_sfarsit = getZiUser()
                cnt = removeCheltuialaInterval(dictionar_cheltuieli, zi_inceput, zi_sfarsit)
                clearScreen()
                print(f"Intervalul final: [{zi_inceput}, {zi_sfarsit}]")
                if cnt == 0:
                    print("Nu a fost stearsa nicio cheltuiala!")
                elif cnt == 1:
                    print("A fost stearsa o cheltuiala!")
                else:
                    print (f"Au fost sterse {cnt} cheltuieli!")
                input("Apasati Enter pentru a continua...")
            case "3":
                tip = getTipUser()
                cnt = removeCheltuialaTip(dictionar_cheltuieli, tip)
                clearScreen()
                if cnt == 0:
                    print("Nu a fost stearsa nicio cheltuiala!")
                elif cnt == 1:
                    print("A fost stearsa o cheltuiala!")
                else:
                    print(f"Au fost sterse {cnt} cheltuieli!")
                input("Apasati Enter pentru a continua...")
            case "4":
                clearScreen()
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

def SearchMenu():
    # Functie care afiseaza optiunile din meniul "Cautare"
    clearScreen()
    print("Cautare:")
    print("1. Tipareste toate cheltuielile mai mari decat o suma data")
    print("2. Tipareste toate cheltuielile efectuate inainte de o zi data si mai mici decat o suma")
    print("3. Tipareste toate cheltuielile de un anumit tip")
    print("4. Inapoi")

def SearchMenu_run(dictionar_cheltuieli):
    # Functia dirijeaza functionalitatea meniului "Cautare"
    while True:
        SearchMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                suma = getSumaUser()
                solutie = searchCheltuialaMaiMareCaSum(dictionar_cheltuieli, suma)
                clearScreen()
                if len(solutie) == 0:
                    print("Nu exista nicio cheltuiala mai mare decat suma data!")
                else:
                    for cheltuiala in solutie:
                        printCheltuiala(solutie[cheltuiala])
                input("Apasati Enter pentru a continua...")
            case "2":
                zi = getZiUser()
                suma = getSumaUser()
                solutie = searchCheltuialaZiSiSum(dictionar_cheltuieli, zi, suma)
                clearScreen()
                if len(solutie) == 0:
                    print("Nu exista nicio cheltuiala conform cerintei!")
                else:
                    for cheltuiala in solutie:
                        printCheltuiala(solutie[cheltuiala])
                input("Apasati Enter pentru a continua...")
            case "3":
                tip = getTipUser()
                solutie = searchCheltuialaTip(dictionar_cheltuieli, tip)
                clearScreen()
                if len(solutie) == 0:
                    print("Nu exista nicio cheltuiala de tipul dat!")
                else:
                    for cheltuiala in solutie:
                        printCheltuiala(cheltuiala)
                input("Apasati Enter pentru a continua...")
            case "4":
                clearScreen()
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

def RaportMenu():
    # Functie care afiseaza optiunile din meniul "Rapoarte"
    clearScreen()
    print("Rapoarte:")
    print("1. Tipareste suma totala pentru un anumit tip de cheltuiala")
    print("2. Gaseste ziua in care suma cheltuita e maxima")
    print("3. Tipareste toate cheltuielile ce au o anumita suma")
    print("4. Tiparește cheltuielile sortate dupa tip")
    print("5. Inapoi")

def RaportMenu_run(dictionar_cheltuieli):
    # Functie dirijeaza functionalitatea meniului "Rapoarte"
    while True:
        RaportMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                tip = getTipUser()
                suma = raportSumaTotala(dictionar_cheltuieli, tip)
                clearScreen()
                if suma == 0:
                    print("Nu exista nicio cheltuiala de tipul dat!")
                else:
                    print(f"Suma totala este de {suma} bani!")
                input("Apasati Enter pentru a continua...")
            case "2":
                zi = raportFindZiSumaMaxima(dictionar_cheltuieli)
                clearScreen()
                if zi == 0:
                    print("Nu ati introdus nicio cheltuiala!")
                else:
                    print(f"Ziua in care suma cheltuita e maxima este {zi}!")
                input("Apasati Enter pentru a continua...")
            case "3":
                suma = getSumaUser()
                raport = raportSumaSpecifica(dictionar_cheltuieli, suma)
                clearScreen()
                if len(raport) == 0:
                    print("Nu exista nicio cheltuiala cu suma data!")
                else:
                    for cheltuiala in raport:
                        printCheltuiala(cheltuiala)
                input("Apasati Enter pentru a continua...")
            case "4":
                raport = raportCheltuieliSortate(dictionar_cheltuieli)
                clearScreen()
                if len(raport) == 0:
                    print("Nu ati introdus nicio cheltuiala!")
                else:
                    for cheltuiala in raport:
                        printCheltuiala(cheltuiala)
                input("Apasati Enter pentru a continua...")
            case "5":
                clearScreen()
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

def FilterMenu():
    # Functie care afiseaza optiunile din meniul "Filtrare"
    clearScreen()
    print("Filtrare:")
    print("1. Elimina toate cheltuielile de un anumit tip")
    print("2. Elimina toate cheltuielile mai mici decât o suma data")
    print("3. Inapoi")

def FilterMenu_run(dictionar_cheltuieli):
    # Functia dirijeaza functionalitatea meniului "Filtrare"
    while True:
        FilterMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                tip = getTipUser()
                filtru = filterByTip(dictionar_cheltuieli, tip)
                clearScreen()
                if len(filtru) == 0:
                    print("Toate cheltuielile sunt de tipul dat!")
                else:
                    for cheltuiala in filtru:
                        printCheltuiala(cheltuiala)
                input("Apasati Enter pentru a continua...")
            case "2":
                suma = getSumaUser()
                filtru = filterBySuma(dictionar_cheltuieli, suma)
                clearScreen()
                if len(filtru) == 0:
                    print("Toate cheltuielile sunt mai mari decat suma data!")
                else:
                    for cheltuiala in filtru:
                        printCheltuiala(cheltuiala)
                input("Apasati Enter pentru a continua...")
            case "3":
                clearScreen()
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

# Citire + validare / combinare functii / domain vs infrastructure