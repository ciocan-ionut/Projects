from Domain.client import Client
from Repository.clientela import RepositoryClient
from Validare.validator_client import ValidateClient
import unittest

class TestClientDomain(unittest.TestCase):
    def setUp(self):
        self.id_client = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_client, self.nume)

    def test_client_domain(self):
        self.assertEqual(self.id_client, self.client.get_id())
        self.assertEqual(self.nume, self.client.get_nume())

class TestValidateClient(unittest.TestCase):
    def setUp(self):
        self.id_invalid = -1
        self.nume_invalid = ""
        self.client_invalid = Client(self.id_invalid, self.nume_invalid)

        self.id_invalid2 = 0
        self.client_invalid2 = Client(self.id_invalid2, self.nume_invalid)

        self.id_valid = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_valid, self.nume)

    def test_validate_client(self):
        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_client(self.client_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nNume invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_client(self.client_invalid2)
        self.assertEqual(str(context.exception), "ID invalid!\nNume invalid!")

        try:
            ValidateClient.validate_client(self.client)
        except ValueError:
            self.assertFalse(True)

    def test_validate_id_nume(self):
        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_id_nume(self.id_invalid, self.nume_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nNume invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_id_nume(self.id_invalid2, self.nume_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nNume invalid!")

        try:
            ValidateClient.validate_id_nume(self.id_valid, self.nume)
        except ValueError:
            self.assertFalse(True)

    def test_validate_id(self):
        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_id(self.id_invalid)
        self.assertEqual(str(context.exception), "ID invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_id(self.id_invalid2)
        self.assertEqual(str(context.exception), "ID invalid!")

        try:
            ValidateClient.validate_id(self.id_valid)
        except ValueError:
            self.assertFalse(True)

    def test_validate_nume(self):
        with self.assertRaises(ValueError) as context:
            ValidateClient.validate_nume(self.nume_invalid)
        self.assertEqual(str(context.exception), "Nume invalid!")

        try:
            ValidateClient.validate_nume(self.nume)
        except ValueError:
            self.assertFalse(True)

class TestRepositoryClient(unittest.TestCase):
    def setUp(self):
        self.repository = RepositoryClient()
        self.id_client = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_client, self.nume)

        self.nume_nou = "Vasile Popescu"

        id2 = 2
        self.client2 = Client(id2, self.nume)
        id3 = 3
        placeholder = "..."
        self.client3 = Client(id3, placeholder)

    def test_add_client(self):
        self.repository.add_client(self.client)
        clienti = self.repository.get_clienti()
        self.assertEqual(len(clienti), 1)
        self.assertEqual(clienti[0], self.client)
        with self.assertRaises(ValueError) as context:
            self.repository.add_client(self.client)
        self.assertEqual(str(context.exception), "Clientul exista deja!")

    def test_update_client(self):
        self.assertEqual(self.nume, self.client.get_nume())
        with self.assertRaises(ValueError) as context:
            self.repository.update_client(id, self.nume_nou)
        self.assertEqual(str(context.exception), "Clientul nu exista!")
        self.repository.add_client(self.client)
        self.repository.update_client(self.id_client, self.nume_nou)
        self.assertEqual(self.nume_nou, self.client.get_nume())

    def test_remove_client(self):
        with self.assertRaises(ValueError) as context:
            self.repository.remove_client(self.id_client)
        self.assertEqual(str(context.exception), "Clientul nu exista!")
        self.repository.add_client(self.client)
        self.repository.remove_client(self.id_client)
        clienti = self.repository.get_clienti()
        self.assertEqual(len(clienti), 0)

    def test_search_client_by_id(self):
        with self.assertRaises(ValueError) as context:
            self.repository.search_client_by_id(self.id_client)
        self.assertEqual(str(context.exception), "Clientul nu exista!")
        self.repository.add_client(self.client)
        client_gasit = self.repository.search_client_by_id(self.id_client)
        self.assertEqual(self.client, client_gasit)

    def test_search_clienti_by_nume(self):
        with self.assertRaises(ValueError) as context:
            self.repository.search_clienti_by_nume(self.nume, None, None)
        self.assertEqual(str(context.exception), "Nu exista niciun client cu acest nume!")
        self.repository.add_client(self.client)
        self.repository.add_client(self.client2)
        self.repository.add_client(self.client3)
        clienti_gasiti = self.repository.search_clienti_by_nume(self.nume, None, None)
        self.assertEqual(clienti_gasiti, [self.client, self.client2])

def run_tests_client():
    unittest.main()