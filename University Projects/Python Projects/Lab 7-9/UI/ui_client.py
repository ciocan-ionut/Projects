from UI.clear_screen import clear_screen

class MenuClient:
    @staticmethod
    def menu_clients():
        clear_screen()
        print("~~~Clienti~~~")
        print("1. Adauga")
        print("2. Modifica (nume)")
        print("3. Sterge")
        print("4. Cauta")
        print("5. Inapoi")

    @staticmethod
    def run_clients(servicesClient):
        while True:
            MenuClient.menu_clients()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul clientului: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        nume = input("Introduceti numele clientului: ")
                        servicesClient.create_validate_add_client(id, nume)
                        clear_screen()
                        print("Clientul a fost adaugat cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul clientului: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        nume = input("Introduceti noul nume al clientului: ")
                        servicesClient.validate_update_client(id, nume)
                        clear_screen()
                        print("Numele clientului a fost modificat cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "3":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul clientului: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        servicesClient.validate_remove_client(id)
                        clear_screen()
                        print("Clientul a fost sters cu succes!")
                        input("Apasati Enter pentru a continua...")
                    case "4":
                        MenuClient.run_search_client(servicesClient)
                    case "5":
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
    def menu_search_client():
        clear_screen()
        print("Cautati:")
        print("1. Dupa ID")
        print("2. Dupa nume")
        print("3. Inapoi")

    @staticmethod
    def run_search_client(servicesClient):
        while True:
            MenuClient.menu_search_client()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        while True:
                            try:
                                id = int(input("Introduceti id-ul clientului: "))
                                break
                            except ValueError:
                                print("ID invalid!")
                        client = servicesClient.validate_search_client_by_id(id)
                        clear_screen()
                        print(client)
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        nume = input("Introduceti numele clientului: ")
                        lista_clienti = servicesClient.validate_search_clienti_by_nume(nume)
                        clear_screen()
                        for client in lista_clienti:
                            print(client)
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