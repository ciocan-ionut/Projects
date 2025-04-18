from Business.services import addCheltuiala, existsCheltuiala, updateCheltuiala, undoChanges, saveIstoric, \
    raportCheltuieliSortate
from Domain.cheltuiala import createCheltuiala, printCheltuiala
from UI.console import getIDUser, getZiUser, getSumaUser, getTipUser, \
    clearScreen

def add(cheltuieli, istoric):
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

def update(cheltuieli, istoric):
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

def raport(cheltuieli, istoric):
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
    istoric = []
    commands = {
        "add_1": add,
        "add_2": update,
        "raport_4": raport,
        "undo": undo
    }
    while True:
        clearScreen()
        command_name = input(">>>")
        command_name = command_name.lower()
        command_name = command_name.strip()
        if command_name == "":
            continue
        if command_name == "quit":
            break
        if command_name in commands:
            try:
                commands[command_name](cheltuieli, istoric)
            except ValueError as ve:
                print(ve)
        else:
            print("invalid command!")