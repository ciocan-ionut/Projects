class RepositoryImprumut:
    def __init__(self):
        """
        Functie care creeaza un dictionar gol pentru a retine chei unice care reprezinta
        clienti cu id-uri unice si o lista cu cartile care au id-uri unice pe care le-au imprumutat si
        un dictionar gol pentru a retine chei unice care reprezinta cartile cu id-uri unice
        si o lista cu clientii care au id-uri unice care au imprumutat cartea respectiva
        """
        self._clienti_cu_carti = {}
        self._carti_imprumutate = {}

    def get_clienti_cu_carti(self):
        """
        Functie care returneaza dictionarul cu clientii si cartile pe care le-au imprumutat
        :return: dictionarul cu clientii si cartile pe care le-au imprumutat
        """
        return self._clienti_cu_carti

    def get_carti_imprumutate(self):
        """
        Functie care returneaza dictionarul cu cartile si clientii care au imprumutat cartea respectiva
        :return: dictionarul cu cartile si clientii care au imprumutat cartea respectiva
        """
        return self._carti_imprumutate

    def add_imprumut(self, client, carte):
        """
        Functie care realizeaza operatia de imprumut a unei carti
        :param client: un client cu un id int unic
        :param carte: o carte cu un id int unic
        :return: -
        """
        if client not in self._clienti_cu_carti.keys():
            self._clienti_cu_carti[client] = [carte]
        else:
            self._clienti_cu_carti[client].append(carte)

        if carte not in self._carti_imprumutate.keys():
            self._carti_imprumutate[carte] = [client]
        else:
            self._carti_imprumutate[carte].append(client)

    def remove_imprumut(self, client, carte):
        """
        Functie care realizeaza operatia de returnare a unei carti
        :param client: un client cu un id int unic
        :param carte: o carte cu un id int unic
        :return: -
        """
        if len(self._clienti_cu_carti[client]) == 1:
            del self._clienti_cu_carti[client]
        else:
            self._clienti_cu_carti[client].remove(carte)

        if len(self._carti_imprumutate[carte]) == 1:
            del self._carti_imprumutate[carte]
        else:
            self._carti_imprumutate[carte].remove(client)

    def remove_client_cu_imprumuturi(self, client):
        """
        Functie care sterge toate imprumuturile facute de un client
        :param client: un client cu un id int unic
        :return: -
        """
        if client in self._clienti_cu_carti.keys():
            del self._clienti_cu_carti[client]
            carti_de_sters = []
            for carte, lista in self._carti_imprumutate.items():
                if client in lista:
                    if len(lista) > 1:
                        lista.remove(client)
                    else:
                        carti_de_sters.append(carte)
            for carte in carti_de_sters:
                del self._carti_imprumutate[carte]

    def remove_carte_imprumutata(self, carte):
        """
        Functie care sterge toate imprumuturile facute pentru o carte
        :param carte: o carte cu un id int unic
        :return: -
        """
        if carte in self._carti_imprumutate.keys():
            del self._carti_imprumutate[carte]
            clienti_de_sters = []
            for client, lista in self._clienti_cu_carti.items():
                if carte in lista:
                    if len(lista) > 1:
                        lista.remove(carte)
                    else:
                        clienti_de_sters.append(client)
            for client in clienti_de_sters:
                del self._clienti_cu_carti[client]