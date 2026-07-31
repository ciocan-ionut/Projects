from UI.clear_screen import clear_screen
from UI.ui_carte import MenuCarte
from UI.ui_client import MenuClient
from UI.ui_imprumut import MenuImprumut
from UI.ui_random import MenuRandom
from UI.ui_rapoarte import MenuRapoarte

class ConsoleMenu:
    @staticmethod
    def menu():
        clear_screen()
        print("~~~Biblioteca (console)~~~")
        print("1. Accesati lista de carti")
        print("2. Accesati lista de clienti")
        print("3. Imprumutati o carte")
        print("4. Accesati raporturile")
        print("5. Inapoi")
        print("6. Cerinta: Random")

    @staticmethod
    def run(servicesCarte, servicesClient, servicesImprumut):
        while True:
            ConsoleMenu.menu()
            option = input("Alegeti optiunea: ")
            match option:
                case "1":
                    MenuCarte.run_books(servicesCarte)
                case "2":
                    MenuClient.run_clients(servicesClient)
                case "3":
                    MenuImprumut.run_imprumut(servicesImprumut)
                case "4":
                    MenuRapoarte.run_rapoarte(servicesImprumut)
                case "5":
                    clear_screen()
                    break
                case "6":
                    MenuRandom.run_random(servicesCarte)
                case _:
                    clear_screen()
                    print("Optiune invalida. Va rugam sa incercati din nou.")
                    input("Apasati Enter pentru a continua...")