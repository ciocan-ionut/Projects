from UI.clear_screen import clear_screen

class MenuRapoarte:
    @staticmethod
    def menu_rapoarte():
        clear_screen()
        print("~~~Raporturi~~~")
        print("1. Top 3 carti imprumutate")
        print("2. Lista clientilor ordonata")
        print("3. Primii 20% cei mai activi clienti")
        print("4. Inapoi")
        print("5. Cerinta: Lista cartilor ordonata")

    @staticmethod
    def run_rapoarte(servicesImprumut):
        while True:
            MenuRapoarte.menu_rapoarte()
            option = input("Alegeti optiunea: ")
            try:
                match option:
                    case "1":
                        top = servicesImprumut.top_carti_imprumutate()
                        clear_screen()
                        if len(top) == 0:
                            print("Nu au fost realizate imprumuturi!")
                        else:
                            for carte, lista in top:
                                print(f"{carte}, a fost imprumutata de {len(lista)} ori")
                        input("Apasati Enter pentru a continua...")
                    case "2":
                        lista_clienti = servicesImprumut.clienti_cu_carti_sorted()
                        clear_screen()
                        if len(lista_clienti) == 0:
                            print("Nu au fost realizate imprumuturi!")
                        else:
                            for client, lista in lista_clienti:
                                print(f"{client}, a imprumutat {len(lista)} carti")
                        input("Apasati Enter pentru a continua...")
                    case "3":
                        top = servicesImprumut.top_clienti_cu_carti()
                        clear_screen()
                        if len(top) == 0:
                            print("Nu au fost realizate suficiente imprumuturi!")
                        else:
                            for client, lista in top:
                                print(f"{client}, a imprumutat {len(lista)} carti")
                        input("Apasati Enter pentru a continua...")
                    case "4":
                        clear_screen()
                        break
                    case "5":
                        lista_carti = servicesImprumut.carti_imprumutate_sorted()
                        clear_screen()
                        if len(lista_carti) == 0:
                            print("Nu au fost realizate imprumuturi!")
                        else:
                            for carte, lista in lista_carti:
                                print(f"{carte.get_titlu()}, a fost imprumutata de {len(lista)} ori")
                        input("Apasati Enter pentru a continua...")
                    case _:
                        clear_screen()
                        print("Optiune invalida. Va rugam sa incercati din nou.")
                        input("Apasati Enter pentru a continua...")
            except ValueError as errors:
                clear_screen()
                print(errors)
                input("Apasati Enter pentru a continua...")