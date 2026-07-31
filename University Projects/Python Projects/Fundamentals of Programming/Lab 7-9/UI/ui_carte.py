from UI.clear_screen import clear_screen

class MenuCarte:
    @staticmethod
    def menu_books():
        clear_screen()
        print("~~~Carti~~~")
        print("1. Adauga")
        print("2. Modifica")
        print("3. Sterge")
        print("4. Cauta")
        print("5. Inapoi")
        print("6. Cerinta: Carti sortate")

    @staticmethod
    def run_books(servicesCarte):
        while True:
            MenuCarte.menu_books()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        titlu = input("Introduceti titlul cartii: ")
                        descriere = input("Introduceti descrierea cartii: ")
                        autor = input("Introduceti autorul cartii: ")
                        servicesCarte.create_validate_add_carte(id, titlu, descriere, autor)
                        clear_screen()
                        print("Cartea a fost adaugata cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        MenuCarte.run_update_carte(servicesCarte)
                    case "3":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        servicesCarte.validate_remove_carte(id)
                        clear_screen()
                        print("Cartea a fost stearsa cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "4":
                        MenuCarte.run_search_carte(servicesCarte)
                    case "5":
                        clear_screen()
                        break
                    case "6":
                        carti = servicesCarte.carti_sorted()
                        for carte in carti:
                            print(carte)
                        input("Apasati Enter pentru a continua...")
                    case _:
                        clear_screen()
                        print("Optiune invalida. Va rugam sa incercati din nou.")
                        input("Apasati Enter pentru a continua...")
            except ValueError as errors:
                clear_screen()
                print(errors)
                input("Apasati Enter pentru a continua...")

    @staticmethod
    def menu_update_carte():
        clear_screen()
        print("Actualizati:")
        print("1. Titlul unei carti")
        print("2. Descrierea unei carti")
        print("3. Autorul unei carti")
        print("4. Inapoi")

    @staticmethod
    def run_update_carte(servicesCarte):
        while True:
            MenuCarte.menu_update_carte()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        titlu = input("Introduceti noul titlu al cartii: ")
                        servicesCarte.validate_update_titlu_carte(id, titlu)
                        clear_screen()
                        print("Titlul a fost actualizat cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        descriere = input("Introduceti noua descriere a cartii: ")
                        servicesCarte.validate_update_descriere_carte(id, descriere)
                        clear_screen()
                        print("Descrierea a fost actualizata cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "3":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        autor = input("Introduceti noul autor al cartii: ")
                        servicesCarte.validate_update_autor_carte(id, autor)
                        clear_screen()
                        print("Autorul a fost actualizat cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "4":
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

    @staticmethod
    def menu_search_carte():
        clear_screen()
        print("Cautati:")
        print("1. Dupa ID")
        print("2. Dupa titlu")
        print("3. Dupa autor")
        print("4. Inapoi")

    @staticmethod
    def run_search_carte(servicesCarte):
        while True:
            MenuCarte.menu_search_carte()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul cartii: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        carte = servicesCarte.validate_search_carte_by_id(id)
                        clear_screen()
                        print(carte)
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        titlu = input("Introduceti titlul cartilor: ")
                        lista_carti = servicesCarte.validate_search_carti_by_titlu(titlu)
                        clear_screen()
                        for carte in lista_carti:
                            print(carte)
                        input("Apasati Enter pentru a continua...")
                    case "3":
                        autor = input("Introduceti autorul cartilor: ")
                        lista_carti = servicesCarte.validate_search_carti_by_autor(autor)
                        clear_screen()
                        for carte in lista_carti:
                            print(carte)
                        input("Apasati Enter pentru a continua...")
                    case "4":
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