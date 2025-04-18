from UI.clear_screen import clear_screen
from UI.ui_console import ConsoleMenu
from UI.ui_file import FileMenu


class MainMenu:
    @staticmethod
    def main_menu():
        clear_screen()
        print("Bine ati venit!")
        print("1. Citire de la tastatura")
        print("2. Citire din fisier")
        print("3. Iesire")

    @staticmethod
    def run_main_menu(servicesCarte, servicesClient, servicesImprumut, servicesFileCarte, servicesFileClient, servicesFileImprumut):
        while True:
            MainMenu.main_menu()
            option = input("Alegeti optiunea: ")
            match option:
                case "1":
                    ConsoleMenu.run(servicesCarte, servicesClient, servicesImprumut)
                case "2":
                    FileMenu.run(servicesFileCarte, servicesFileClient, servicesFileImprumut)
                case "3":
                    print("La revedere!")
                    break
                case _:
                    clear_screen()
                    print("Optiune invalida. Va rugam sa incercati din nou.")
                    input("Apasati Enter pentru a continua...")