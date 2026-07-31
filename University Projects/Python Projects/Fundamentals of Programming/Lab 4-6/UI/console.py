# menu.py

"""
Modulul permite utilizatorului să adauge, să șteargă, să caute și să genereze rapoarte
privind cheltuielile unei familii. În plus, include și funcționalități pentru filtrare și undo.

Prin apelarea functiei 'run()' se pornește aplicația.
"""

import os
from Domain.cheltuiala import createCheltuiala, printCheltuiala
from Business.services import addCheltuiala, existsCheltuiala, updateCheltuiala, saveIstoric, undoChanges
from Business.services import removeCheltuialaDinZi, removeCheltuialaInterval, removeCheltuialaTip
from Business.services import searchCheltuialaMaiMareCaSum, searchCheltuialaZiSiSum, searchCheltuialaTip
from Business.services import raportSumaTotala, raportFindZiSumaMaxima, raportSumaSpecifica, raportCheltuieliSortate
from Business.services import filterByTip, filterBySuma
from UI.commands_2 import run_commands


def clearScreen():
    # Functia goleste consola aplicatiei
    os.system('cls' if os.name == 'nt' else 'clear')

def MainMenu():
    # Functie care afiseaza meniul principal al aplicatiei
    clearScreen()
    print("Cheltuieli de familie")
    print("1. Adauga cheltuiala")
    print("2. Stergere")
    print("3. Cautari")
    print("4. Rapoarte")
    print("5. Filtrare")
    print("6. Undo")
    print("7. Iesire")

def ChoiceMenu():
    print("Bine ati venit!")
    print("Alegeti tipul de meniu:")
    print("1. Meniul clasic")
    print("2. Meniul cu comenzi")

def run():
    ChoiceMenu()
    option = input()
    match option:
        case "1":
            MainMenu_run()
        case "2":
            run_commands()
        case _:
            clearScreen()
            print("Optiune invalida. Va rugam sa incercati din nou.")
            input("Apasati Enter pentru a continua...")

def MainMenu_run():
    # Functia dirijeaza functionalitatea meniului principal
    # cheltuieli = []
    cheltuieli = {}
    istoric = [{}]
    while True:
        MainMenu()
        option = input("Alegeti o optiune de la 1 la 7: ")
        match option:
            case "1":
                AddMenu_run(cheltuieli, istoric)
            case "2":
                RemoveMenu_run(cheltuieli, istoric)
            case "3":
                SearchMenu_run(cheltuieli)
            case "4":
                RaportMenu_run(cheltuieli)
            case "5":
                FilterMenu_run(cheltuieli)
            case "6":
                Undo(cheltuieli, istoric)
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
            idc = int(input("Introduceti id (valoare strict pozitiva): "))
            if idc <= 0:
                raise ValueError
            break
        except ValueError:
            print("Optiune invalida. Va rugam sa incercati din nou.")
    return idc

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

def AddMenu_run(cheltuieli, istoric):
    # Functia dirijeaza functionalitatea meniului "Adauga cheltuiala"
    while True:
        AddMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                idc = getIDUser()
                zi = getZiUser()
                suma = getSumaUser()
                tip = getTipUser()
                cheltuiala = createCheltuiala(idc, zi, suma, tip)
                clearScreen()
                if addCheltuiala(cheltuiala, cheltuieli):
                    saveIstoric(cheltuieli, istoric)
                    print("Cheltuiala adaugata cu succes!")
                else:
                    print("Cheltuiala exista deja!")
                input("Apasati Enter pentru a continua...")
            case "2":
                print("Introduceti datele cheltuielii pe care vreti sa o actualizati:")
                idc = getIDUser()
                zi = getZiUser()
                suma = getSumaUser()
                tip = getTipUser()
                old_cheltuiala = createCheltuiala(idc, zi, suma, tip)
                if not existsCheltuiala(old_cheltuiala, cheltuieli):
                    clearScreen()
                    print("Cheltuiala nu exista!")
                else:
                    print("Introduceti noile date:")
                    zi = getZiUser()
                    suma = getSumaUser()
                    tip = getTipUser()
                    saveIstoric(cheltuieli, istoric)
                    updateCheltuiala(old_cheltuiala, zi, suma, tip, cheltuieli)
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

def RemoveMenu_run(cheltuieli, istoric):
    # Functia dirijeaza functionalitatea meniului "Stergere"
    while True:
        RemoveMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                zi = getZiUser()
                saveIstoric(cheltuieli, istoric)
                cnt = removeCheltuialaDinZi(zi, cheltuieli)
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
                saveIstoric(cheltuieli, istoric)
                cnt = removeCheltuialaInterval(zi_inceput, zi_sfarsit, cheltuieli)
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
                saveIstoric(cheltuieli, istoric)
                cnt = removeCheltuialaTip(tip, cheltuieli)
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

def SearchMenu_run(cheltuieli):
    # Functia dirijeaza functionalitatea meniului "Cautare"
    while True:
        SearchMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                suma = getSumaUser()
                solutie = searchCheltuialaMaiMareCaSum(suma, cheltuieli)
                clearScreen()
                if len(solutie) == 0:
                    print("Nu exista nicio cheltuiala mai mare decat suma data!")
                else:
                    for cheltuiala in solutie:
                        print(printCheltuiala(cheltuiala))
                input("Apasati Enter pentru a continua...")
            case "2":
                zi = getZiUser()
                suma = getSumaUser()
                solutie = searchCheltuialaZiSiSum(zi, suma, cheltuieli)
                clearScreen()
                if len(solutie) == 0:
                    print("Nu exista nicio cheltuiala conform cerintei!")
                else:
                    for cheltuiala in solutie:
                        print(printCheltuiala(cheltuiala))
                input("Apasati Enter pentru a continua...")
            case "3":
                tip = getTipUser()
                solutie = searchCheltuialaTip(tip, cheltuieli)
                clearScreen()
                if len(solutie) == 0:
                    print("Nu exista nicio cheltuiala de tipul dat!")
                else:
                    for cheltuiala in solutie:
                        print(printCheltuiala(cheltuiala))
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

def RaportMenu_run(cheltuieli):
    # Functie dirijeaza functionalitatea meniului "Rapoarte"
    while True:
        RaportMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                tip = getTipUser()
                suma = raportSumaTotala(tip, cheltuieli)
                clearScreen()
                if suma == 0:
                    print("Nu exista nicio cheltuiala de tipul dat!")
                else:
                    print(f"Suma totala este de {suma} bani!")
                input("Apasati Enter pentru a continua...")
            case "2":
                zi = raportFindZiSumaMaxima(cheltuieli)
                clearScreen()
                if zi == 0:
                    print("Nu ati introdus nicio cheltuiala!")
                else:
                    print(f"Ziua in care suma cheltuita e maxima este {zi}!")
                input("Apasati Enter pentru a continua...")
            case "3":
                suma = getSumaUser()
                raport = raportSumaSpecifica(suma, cheltuieli)
                clearScreen()
                if len(raport) == 0:
                    print("Nu exista nicio cheltuiala cu suma data!")
                else:
                    for cheltuiala in raport:
                        print(printCheltuiala(cheltuiala))
                input("Apasati Enter pentru a continua...")
            case "4":
                raport = raportCheltuieliSortate(cheltuieli)
                clearScreen()
                if len(raport) == 0:
                    print("Nu ati introdus nicio cheltuiala!")
                else:
                    for idc, cheltuiala in raport.items():
                        print(printCheltuiala(cheltuiala))
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

def FilterMenu_run(cheltuieli):
    # Functia dirijeaza functionalitatea meniului "Filtrare"
    while True:
        FilterMenu()
        option = input("Alegeti o optiune: ")
        match option:
            case "1":
                tip = getTipUser()
                filtru = filterByTip(tip, cheltuieli)
                clearScreen()
                if len(filtru) == 0:
                    print("Toate cheltuielile sunt de tipul dat!")
                else:
                    for cheltuiala in filtru:
                        print(printCheltuiala(cheltuiala))
                input("Apasati Enter pentru a continua...")
            case "2":
                suma = getSumaUser()
                filtru = filterBySuma(suma, cheltuieli)
                clearScreen()
                if len(filtru) == 0:
                    print("Toate cheltuielile sunt mai mari decat suma data!")
                else:
                    for cheltuiala in filtru:
                        print(printCheltuiala(cheltuiala))
                input("Apasati Enter pentru a continua...")
            case "3":
                clearScreen()
                break
            case _:
                clearScreen()
                print("Optiune invalida. Va rugam sa incercati din nou.")
                input("Apasati Enter pentru a continua...")

def Undo(cheltuieli, istoric):
    if len(istoric) == 0:
        clearScreen()
        print("Operatia nu a putut fi efectuata! Nu exista instante precedente pentru lista de cheltuieli!")
        input("Apasati Enter pentru a continua...")
    else:
        undoChanges(cheltuieli, istoric)
        clearScreen()
        """
        for dcheltuieli in istoric:
            for idc, cheltuiala in dcheltuieli.items():
                print(printCheltuiala(cheltuiala))
            print("-----------------------")
        """
        print("Modificarile au fost anulate!")
        input("Apasati Enter pentru a continua...")