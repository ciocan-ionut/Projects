from UI.clear_screen import clear_screen

class MenuRandom():
    @staticmethod
    def menu_random():
        clear_screen()
        print("~~~Random~~~")
        print("1. Creeaza X carti")
        print("2. Inapoi")

    @staticmethod
    def run_random(servicesCarte):
        while True:
            MenuRandom.menu_random()
            option = input("Alegeti optiunea: ")
            match option:
                case "1":
                    while True:
                        try:
                            X = int(input("X = "))
                            break
                        except ValueError:
                            print("X invalid!")
                    servicesCarte.generate_X_carti(X)
                    clear_screen()
                    print(f"Au fost generate {X} carti")
                    input("Apasati Enter pentru a continua...")
                case "2":
                    clear_screen()
                    break
                case _:
                    clear_screen()
                    print("Optiune invalida. Va rugam sa incercati din nou.")
                    input("Apasati Enter pentru a continua...")