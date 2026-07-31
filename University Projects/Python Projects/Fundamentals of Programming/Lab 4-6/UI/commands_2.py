import os
from Business.services import addCheltuiala, existsCheltuiala, updateCheltuiala, undoChanges, saveIstoric, \
    raportCheltuieliSortate
from Domain.cheltuiala import createCheltuiala, printCheltuiala

def clearScreen():
    # Functia goleste consola aplicatiei
    os.system('cls' if os.name == 'nt' else 'clear')

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

def add(idc, zi, suma, tip, cheltuieli, istoric):
    cheltuiala = createCheltuiala(idc, zi, suma, tip)
    clearScreen()
    if addCheltuiala(cheltuiala, cheltuieli):
        saveIstoric(cheltuieli, istoric)
        print("Cheltuiala adaugata cu succes!")
    else:
        print("Cheltuiala exista deja!")
    input("Apasati Enter pentru a continua...")

def update(idc, zi, suma, tip, zi_new, suma_new, tip_new, cheltuieli, istoric):
    # print("Introduceti datele cheltuielii pe care vreti sa o actualizati:")
    old_cheltuiala = createCheltuiala(idc, zi, suma, tip)
    if not existsCheltuiala(old_cheltuiala, cheltuieli):
        clearScreen()
        print("Cheltuiala nu exista!")
    else:
        # print("Introduceti noile date:")
        zi = getZiUser()
        suma = getSumaUser()
        tip = getTipUser()
        saveIstoric(cheltuieli, istoric)
        updateCheltuiala(old_cheltuiala, zi_new, suma_new, tip_new, cheltuieli)
        clearScreen()
        print("Cheltuiala a fost actualizata!")
    input("Apasati Enter pentru a continua...")

def raport(cheltuieli):
    raport = raportCheltuieliSortate(cheltuieli)
    clearScreen()
    if len(raport) == 0:
        print("Nu ati introdus nicio cheltuiala!")
    else:
        for idc, cheltuiala in raport.items():
            print(printCheltuiala(cheltuiala))
    input("Apasati Enter pentru a continua...")

def undo(cheltuieli, istoric):
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

def run_commands():
    cheltuieli = {}
    istoric = [{}]
    commands = {
        "add": add,
        "update": update,
        "raport": raport,
        "undo": undo
    }
    ok = True
    while ok:
        clearScreen()
        command_name = input(">>>")
        command_name = command_name.lower()
        command_name = command_name.strip()
        option = command_name.split()
        i = 0
        while i < len(option):
            if option[i] == "":
                i += 1
                continue
            if option[i] == "quit":
                ok = False
                break
            if option[i] in commands:
                try:
                    if option[i] == "add":
                        if i + 4 < len(option):
                            try:
                                idc = int(option[i+1])
                                zi = int(option[i+2])
                                suma = float(option[i+3])
                                tip = option[i+4]
                                commands["add"](idc, zi, suma, tip, cheltuieli, istoric)
                                i += 5
                            except ValueError:
                                print("Nu merge!")
                                i += 1
                        else:
                            i += 1
                    if option[i] == "update":
                        if i + 7 < len(option):
                            try:
                                idc = int(option[i + 1])
                                zi = int(option[i + 2])
                                suma = float(option[i + 3])
                                tip = option[i + 4]
                                zi_new = int(option[i + 5])
                                suma_new = float(option[i + 6])
                                tip_new = option[i + 7]
                                commands["update"](idc, zi, suma, tip, zi_new, suma_new, tip_new, cheltuieli, istoric)
                                i += 8
                            except ValueError:
                                print("Nu merge!")
                                i += 1
                        else:
                            i += 1
                    if option[i] == "raport":
                        commands["raport"](cheltuieli)
                        i += 1
                    if option[i] == "undo":
                        commands["undo"](cheltuieli, istoric)
                        i += 1
                except ValueError as e:
                    print(e)
                except IndexError as e:
                    print(e)
            else:
                i += 1