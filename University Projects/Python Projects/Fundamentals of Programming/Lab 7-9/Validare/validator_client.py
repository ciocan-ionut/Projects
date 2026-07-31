class ValidateClient:
    @staticmethod
    def validate_id(id):
        """
        Functie care verifica daca id > 0
        :param id: int
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id <= 0
        """
        if id <= 0:
            raise ValueError("ID invalid!")

    @staticmethod
    def validate_nume(nume):
        """
        Functie care verifica daca a fost introdus un nume
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string:
            "Nume invalid!\n" daca nume este ""
        """
        if nume == "":
            raise ValueError("Nume invalid!")

    @staticmethod
    def validate_id_nume(id, nume):
        """
        Functie care verifica daca id > 0 si daca a fost introdus un nume
        :param id: int
        :param nume: string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id <= 0
            "Nume invalid!\n" daca nume este ""
        """
        errors = ""
        if id <= 0:
            errors += "ID invalid!\n"
        if nume == "":
            errors += "Nume invalid!"
        if len(errors) > 0:
            raise ValueError(errors)

    @staticmethod
    def validate_client(client):
        """
        Functie care verifica daca clientul client are un id > 0 si a fost introdus un nume
        :param client: un client cu un id int si un nume string
        :return: -
        :raises: ValueError cu mesajul string:
            "ID invalid!\n" daca id <= 0
            "Nume invalid!\n" daca nume este ""
        """
        errors = ""
        if client.get_id() <= 0:
            errors += "ID invalid!\n"
        if client.get_nume() == "":
            errors += "Nume invalid!"
        if len(errors) > 0:
            raise ValueError(errors)