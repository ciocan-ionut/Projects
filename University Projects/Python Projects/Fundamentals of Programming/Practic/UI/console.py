class Console:
    @staticmethod
    def menu():
        # Functie pentru a afisa meniul aplicatiei
        print("1. Adaugare de automobil")
        print("2. Stergerea automobilelor")
        print("3. Filtrare")
        print("4. Undo")
        print("5. Iesire")

    @staticmethod
    def run(services):
        """
        Functie prin care facem legatura intre utilizator si program
        :param services: clasa de servicii a programului
        :return: -
        """
        Console.menu()
        while True:
            option = input("Alegeti optiunea: ")
            match option:
                case "1":
                    while True:
                        try:
                            id = int(input("Introduceti un id valid: "))
                            break
                        except ValueError:
                            print("El valor debe ser un numero")
                    marca = input("Introduceti marca masinii: ")
                    while True:
                        try:
                            pret = float(input("Introduceti pretul masinii: "))
                            break
                        except ValueError:
                            print("El valor debe ser un numero")
                    model = input("Introduceti modelul masinii: ")
                    data = input("Introduceti data la care expira ITP-ul: ")
                    if services.adauga_automobil(id, marca, pret, model, data):
                        print("Adaugare cu succes!")
                    else: print("ID-ul exista deja!")
                case "2":
                    while True:
                        try:
                            cifra = int(input("Introduceti cifra: "))
                            break
                        except ValueError:
                            print("El valor debe ser un numero")
                    services.sterge_automobile(cifra)
                case "3":
                    filtru_marca = input("Introduceti marca: ")
                    while True:
                        try:
                            filtru_pret = float(input("Introduceti pretul: "))
                            break
                        except ValueError:
                            print("El valor debe ser un numero")
                    lista_filtrata = services.filtrare_automobile(filtru_marca, filtru_pret)
                    for auto in lista_filtrata:
                        print(auto)
                case "4":
                    services.undo_operatie()
                case "5":
                    break
                case _:
                    print("Optiune invalida!")