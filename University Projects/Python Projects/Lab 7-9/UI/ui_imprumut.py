from UI.clear_screen import clear_screen

class MenuImprumut:
    @staticmethod
    def menu_imprumut():
        clear_screen()
        print("~~~Imprumutati/Returnati~~~")
        print("1. Imprumuta o carte")
        print("2. Returneaza o carte")
        print("3. Inapoi")

    @staticmethod
    def run_imprumut(servicesImprumut):
        while True:
            MenuImprumut.menu_imprumut()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                id_client = int(input("Introduceti id-ul clientului: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        while True:
                            try:
                                id_carte = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        servicesImprumut.imprumuta_carte(id_client, id_carte)
                        clear_screen()
                        print("Cartea a fost imprumutata cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        while True:
                            try:
                                id_client = int(input("Introduceti id-ul clientului: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        while True:
                            try:
                                id_carte = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        servicesImprumut.returnare_carte(id_client, id_carte)
                        clear_screen()
                        print("Cartea a fost returnata cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "3":
                        clear_screen()
                        break
                    case _:
                        clear_screen()
                        print("Optiune invalida. Va rugam sa incercati din nou.")
                        input("Apasati Enter pentru a continua...")
            except ValueError as errors:
                clear_screen()
                print(errors)
                input("Apasati Enter pentru a continua...")


