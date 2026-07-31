class ValidateCarte:
    @staticmethod
    def validate_id(id):
        """
        Functie care verifica daca id > 0
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string: "ID invalid!\n" daca id este <= 0
        """
        if id <= 0:
            raise ValueError("ID invalid!")

    @staticmethod
    def validate_titlu(titlu):
        """
        Functie care verifica daca a fost introdus un titlu
        :param titlu: string
        :return: -
        :raises: ValueError cu mesajul string: "Titlu invalid!\n" daca titlu este ""
        """
        if titlu == "":
            raise ValueError("Titlu invalid!")

    @staticmethod
    def validate_autor(autor):
        """
        Functie care verifica daca a fost introdus un autor
        :param autor: string
        :return: -
        :raises: ValueError cu mesajul string: "Autor invalid!\n" daca autor este ""
        """
        if autor == "":
            raise ValueError("Autor invalid!")

    @staticmethod
    def validate_id_titlu(id, titlu):
        """
        Functie care verifica daca id > 0 si daca a fost introdus un titlu
        :param id: int
        :param titlu: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Titlu invalid!\n" daca titlu este ""
        """
        errors = ""
        if id <= 0:
            errors += "ID invalid!\n"
        if titlu == "":
            errors += "Titlu invalid!"
        if len(errors) > 0:
            raise ValueError(errors)

    @staticmethod
    def validate_id_descriere(id, descriere):
        """
        Functie care verifica daca id > 0 si daca a fost introdusa o descriere
        :param id: int
        :param descriere: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Descriere invalida!\n" daca descriere este ""
        """
        errors = ""
        if id <= 0:
            errors += "ID invalid!\n"
        if descriere == "":
            errors += "Descriere invalida!"
        if len(errors) > 0:
            raise ValueError(errors)

    @staticmethod
    def validate_id_autor(id, autor):
        """
        Functie care verifica daca id > 0 si daca a fost introdus un autor
        :param id: int
        :param autor: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Autor invalid!\n" daca autor este ""
        """
        errors = ""
        if id <= 0:
            errors += "ID invalid!\n"
        if autor == "":
            errors += "Autor invalid!"
        if len(errors) > 0:
            raise ValueError(errors)

    @staticmethod
    def validate_carte(carte):
        """
        Functie care verifica daca cartea carte are un id > 0, a fost introdus un titlu, o descriere si un autor
        :param carte: o carte cu un id int, un titlu string, o descriere string si un autor string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id este <= 0
            "Titlu invalid!\n" daca titlu este ""
            "Descriere invalida!\n" daca descriere este ""
            "Autor invalid!\n" daca autor este ""
        """
        errors = ""
        if carte.get_id() <= 0:
            errors += "ID invalid!\n"
        if carte.get_titlu() == "":
            errors += "Titlu invalid!\n"
        if carte.get_descriere() == "":
            errors += "Descriere invalida!\n"
        if carte.get_autor() == "":
            errors += "Autor invalid!"
        if len(errors) > 0:
            raise ValueError(errors)