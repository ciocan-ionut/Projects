class ValidateImprumut:
    @staticmethod
    def validate_imprumut(id_client, id_carte):
        """
        Functie care verifica daca id_client > 0 si id_carte > 0
        :param id_client: int
        :param id_carte: int
        :return: -
        :raises: ValueError cu mesajul string:
            "ID-ul clientului este invalid!\n" daca id_client este <= 0
            "ID-ul cartii este invalid!" daca id_carte <= 0
        """
        errors = ""
        if id_client <= 0:
            errors += "ID-ul clientului este invalid!\n"
        if id_carte <= 0:
            errors += "ID-ul cartii este invalid!"
        if len(errors) > 0:
            raise ValueError(errors)