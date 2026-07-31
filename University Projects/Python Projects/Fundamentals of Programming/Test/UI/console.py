class Console:
    @staticmethod
    def menu():
        print("~~~Bine ati venit!~~~")
        print("1. Adaugati un material")
        print("2. Valorile de pe stoc")
        print("3. Efectuati o vanzare")
        print("4. Iesire")

    @staticmethod
    def run_menu(servicesMateriale):
        while True:
            Console.menu()
            option = input("Introduceti cifra optiunii pe care o doriti: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                cod = int(input("Introduceti codul materialului: "))
                                break
                            except ValueError:
                                print("Cod invalid! Introduceti un numar!")
                        denumire = input("Introduceti denumirea materialului: ")
                        um = input("Introduceti unitatea de masura a materialului: ")
                        while True:
                            try:
                                cantitate = int(input("Introduceti cantitatea pe stoc a materialului: "))
                                break
                            except ValueError:
                                print("Cantitate invalida! Introduceti un numar!")
                        while True:
                            try:
                                pret = float(input("Introduceti pretul unitar al materialului: "))
                                break
                            except ValueError:
                                print("Pret invalid! Introduceti un numar!")
                        servicesMateriale.create_and_add_material(cod, denumire, um, cantitate, pret)
                        print("Operatia s-a efectuat cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        while True:
                            try:
                                val = float(input("Introduceti valoarea: "))
                                break
                            except ValueError:
                                print("Valoare invalida! Introduceti un numar!")
                        servicesMateriale.valoare_pe_stoc_mai_mare_decat_val(val)
                        print("Operatia s-a efectuat cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "4":
                        print("La revedere!")
                        break
                    case _:
                        print("Optiune invalida! Va rugam incercati din nou!")
                        input("Apasati Enter pentru a continua...")
            except ValueError as errors:
                print(errors)
                input("Apasati Enter pentru a continua...")