from Validare.validator_imprumut import ValidateImprumut

class ServicesImprumut:
    def __init__(self, repositoryCarte, repositoryClient, repositoryImprumut):
        """
        Functie care initializeaza repository-urile clasei cu repository-ul de carti, de clienti
        si respectiv de imprumuturi
        :param repositoryCarte: repository-ul de carti
        :param repositoryClient: repository-ul de clienti
        :param repositoryImprumut: repository-ul de imprumuturi
        """
        self.__repositoryCarte = repositoryCarte
        self.__repositoryClient = repositoryClient
        self.__repositoryImprumut = repositoryImprumut

    def imprumuta_carte(self, id_client, id_carte):
        """
        Functie care verifica daca id_client > 0 si id_carte > 0;
        realizeaza operatia de imprumut a unei carti doar daca clientul cu id_client
        si cartea cu id_carte exista
        :param id_client: int
        :param id_carte: int
        :return: -
        :raises: ValueError cu mesajul string:
            "ID-ul clientului este invalid!\n" daca id_client este <= 0
            "ID-ul cartii este invalid!" daca id_carte <= 0
                 ValueError cu mesajul string:
            "Clientul nu exista!\n" daca clientul cu id_client nu exista
            "Cartea nu exista!" daca cartea cu id_carte nu exista
            "Clientul a imprumutat deja cartea!" daca clientul a imprumutat deja cartea
        """
        ValidateImprumut.validate_imprumut(id_client, id_carte)
        client = self.__repositoryClient.search_client_by_id(id_client)
        carte = self.__repositoryCarte.search_carte_by_id(id_carte)
        if client in self.__repositoryImprumut.get_clienti_cu_carti().keys():
            if carte in self.__repositoryImprumut.get_clienti_cu_carti()[client]:
                raise ValueError("Clientul a imprumutat deja cartea!")
        self.__repositoryImprumut.add_imprumut(client, carte)

    def returnare_carte(self, id_client, id_carte):
        """
        Functie care verifica daca id_client > 0 si id_carte > 0;
        realizeaza operatia de returnare a unei carti doar daca clientul cu id_client
        si cartea cu id_carte exista, iar clientul a imprumutat cartea cu id_carte
        :param id_client: int
        :param id_carte: int
        :return: -
        :raises: ValueError cu mesajul string:
            "ID-ul clientului este invalid!\n" daca id_client este <= 0
            "ID-ul cartii este invalid!" daca id_carte <= 0
                 ValueError cu mesajul string:
            "Clientul nu exista!\n" daca clientul cu id_client nu exista
            "Cartea nu exista!" daca cartea cu id_carte nu exista
                 ValueError cu mesajul string:
            "Clientul nu a imprumutat aceasta carte!" daca clientul nu a imprumutat nicio carte
            "Cartea nu a fost imprumutata!" daca cartea nu a fost imprumutata de niciun client
        """
        ValidateImprumut.validate_imprumut(id_client, id_carte)
        client = self.__repositoryClient.search_client_by_id(id_client)
        carte = self.__repositoryCarte.search_carte_by_id(id_carte)
        if client not in self.__repositoryImprumut.get_clienti_cu_carti().keys():
            raise ValueError("Clientul nu a imprumutat nicio carte!")
        if carte not in self.__repositoryImprumut.get_carti_imprumutate().keys():
            raise ValueError("Cartea nu a fost imprumutata!")
        self.__repositoryImprumut.remove_imprumut(client, carte)

    @staticmethod
    def __QuickSort(var, key = lambda x:x, reverse=False):
        """
        Functie care sorteaza colectia de date var dupa cheia key, in functie de reverse
        :param var: colectia de date ce trebuie sortata
        :param key: parametrul (parametrii) dupa care se face sortarea
        :param reverse: False / True
        :return: colectia de date var sortata dupa cheia key, in functie de reverse
        """
        # Complexitate O(n*log(n))
        var = list(var)
        if len(var) <= 1:
            return var
        else:
            pivot = var[0]
            pivot_key = key(pivot)
            if not reverse:
                st = [x for x in var[1:] if key(x) < pivot_key]
                dr = [x for x in var[1:] if key(x) >= pivot_key]
            else:
                st = [x for x in var[1:] if key(x) >= pivot_key]
                dr = [x for x in var[1:] if key(x) < pivot_key]
            return ServicesImprumut.__QuickSort(st, key=key, reverse=reverse) + [pivot] + ServicesImprumut.__QuickSort(dr, key=key, reverse=reverse)

    @staticmethod
    def __GnomeSort(var, key = lambda x:x, reverse=False):
        """
        Functie care sorteaza colectia de date var dupa cheia key, in functie de reverse
        :param var: colectia de date ce trebuie sortata
        :param key: parametrul (parametrii) dupa care se face sortarea
        :param reverse: False / True
        :return: colectia de date var sortata dupa cheia key, in functie de reverse
        """
        # Complexitate O(n^2)
        var = list(var)
        index = 0
        while index < len(var):
            if index == 0:
                index += 1
            elif (key(var[index]) >= key(var[index-1]) and not reverse) or (key(var[index]) <= key(var[index-1]) and reverse):
                index += 1
            else:
                var[index], var[index-1] = var[index-1], var[index]
                index -= 1
        return var

    def top_carti_imprumutate(self):
        """
        Functie care sorteaza cartile descrescator dupa numarul de clienti care le-au imprumutat
        :return: primele 3 carti cele mai imprumutate
        """
        # top = sorted(self.__repositoryImprumut.get_carti_imprumutate().items(), key=lambda x: len(x[1]), reverse=True)
        # top = ServicesImprumut.__QuickSort(self.__repositoryImprumut.get_carti_imprumutate().items(), key=lambda x: len(x[1]), reverse=True)
        top = ServicesImprumut.__GnomeSort(self.__repositoryImprumut.get_carti_imprumutate().items(), key=lambda x: len(x[1]), reverse=True)
        return top[:3]

    def clienti_cu_carti_sorted(self):
        """
        Functie care sorteaza clientii descrescator dupa numarul de carti pe care le-au imprumutat
        :return: lista cu clientii si cartile pe care le-au imprumutat ordonata
        """
        # return sorted(self.__repositoryImprumut.get_clienti_cu_carti().items(), key=lambda x: (-len(x[1]), x[0].get_nume()))
        return ServicesImprumut.__QuickSort(self.__repositoryImprumut.get_clienti_cu_carti().items(), key=lambda x: (-len(x[1]), x[0].get_nume()))

    def top_clienti_cu_carti(self):
        """
        Functie care sorteaza clientii descrescator dupa numarul de carti pe care le-au imprumutat si crescator dupa nume
        :return: primii 20% clienti cu cele mai multe carti imprumutate
        """
        top = self.clienti_cu_carti_sorted()
        cnt = 0
        clienti = self.__repositoryImprumut.get_clienti_cu_carti()
        if len(clienti) >= 5:
            cnt = len(clienti)//5
        return top[:cnt]

    def carti_imprumutate_sorted(self):
        """
        Functie care sorteaza cartile descrescator dupa numarul de clienti care le-au imprumutat si crescator dupa titlu
        :return:
        """
        # return sorted(self.__repositoryImprumut.get_carti_imprumutate().items(), key=lambda x: (-len(x[1]), x[0].get_titlu()))
        return ServicesImprumut.__QuickSort(self.__repositoryImprumut.get_carti_imprumutate().items(), key=lambda x: (-len(x[1]), x[0].get_titlu()))