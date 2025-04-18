from Business.services_imprumut import ServicesImprumut
from Domain.carte import Carte
from Domain.client import Client
from Repository.clientela import RepositoryClient
from Repository.depozit import RepositoryCarte
from Repository.imprumut import RepositoryImprumut
from Validare.validator_imprumut import ValidateImprumut
import unittest

class TestValidateImprumut(unittest.TestCase):
    def setUp(self):
        self.id_client_invalid = -1
        self.id_carte_invalid = -1
        self.id_client_invalid2 = 0
        self.id_carte_invalid2 = 0
        self.id_client_valid = 1
        self.id_carte_valid = 1

    def test_validate_imprumut(self):
        with self.assertRaises(ValueError) as context:
            ValidateImprumut.validate_imprumut(self.id_client_invalid, self.id_carte_invalid)
        self.assertEqual(str(context.exception),"ID-ul clientului este invalid!\nID-ul cartii este invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateImprumut.validate_imprumut(self.id_client_invalid2, self.id_carte_invalid2)
        self.assertEqual(str(context.exception),"ID-ul clientului este invalid!\nID-ul cartii este invalid!")

        try:
            ValidateImprumut.validate_imprumut(self.id_client_valid, self.id_carte_valid)
        except ValueError:
            self.assertFalse(True)

class TestImprumutaCarte(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        self.titlu = "Carbon Modificat"
        self.descriere = "Sci-Fi"
        self.autor = "Richard Morgan"
        self.carte = Carte(self.id_carte, self.titlu, self.descriere, self.autor)

        self.id_client = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_client, self.nume)

    def test_client_inexistent(self):
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Clientul nu exista!")

    def test_carte_inexistenta(self):
        self.repositoryClient.add_client(self.client)
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Cartea nu exista!")

    def test_client_deja_imprumutat_cartea(self):
        self.repositoryClient.add_client(self.client)
        self.repositoryCarte.add_carte(self.carte)
        self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Clientul a imprumutat deja cartea!")

    def test_imprumut_valid(self):
        self.repositoryClient.add_client(self.client)
        self.repositoryCarte.add_carte(self.carte)
        self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        clienti_cu_carti = self.repositoryImprumut.get_clienti_cu_carti()
        self.assertEqual(clienti_cu_carti[self.client], [self.carte])

class TestReturnareCarte(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        self.titlu = "Carbon Modificat"
        self.descriere = "Sci-Fi"
        self.autor = "Richard Morgan"
        self.carte = Carte(self.id_carte, self.titlu, self.descriere, self.autor)

        self.id_client = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_client, self.nume)

        self.id_carte2 = 2
        self.carte2 = Carte(self.id_carte2, self.titlu, self.descriere, self.autor)

    def test_returnare_client_inexistent(self):
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.returnare_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Clientul nu exista!")

    def test_returnare_carte_inexistenta(self):
        self.repositoryClient.add_client(self.client)
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.returnare_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Cartea nu exista!")

    def test_client_nu_a_imprumutat_cartea(self):
        self.repositoryClient.add_client(self.client)
        self.repositoryCarte.add_carte(self.carte)
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.returnare_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Clientul nu a imprumutat nicio carte!")

    def test_returnare_carte_neimprumutata(self):
        self.repositoryClient.add_client(self.client)
        self.repositoryCarte.add_carte(self.carte)
        self.repositoryCarte.add_carte(self.carte2)
        self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte2)
        with self.assertRaises(ValueError) as context:
            self.servicesImprumut.returnare_carte(self.id_client, self.id_carte)
        self.assertEqual(str(context.exception), "Cartea nu a fost imprumutata!")

    def test_returnare_valid(self):
        self.repositoryClient.add_client(self.client)
        self.repositoryCarte.add_carte(self.carte)
        self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        self.servicesImprumut.returnare_carte(self.id_client, self.id_carte)
        clienti_cu_carti = self.repositoryImprumut.get_clienti_cu_carti()
        self.assertEqual(len(clienti_cu_carti), 0)

class TestRemoveClientCuImprumuturi(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        self.titlu = "Carbon Modificat"
        self.descriere = "Sci-Fi"
        self.autor = "Richard Morgan"
        self.carte = Carte(self.id_carte, self.titlu, self.descriere, self.autor)

        self.id_client = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_client, self.nume)

    def test_remove_client(self):
        self.repositoryCarte.add_carte(self.carte)
        self.repositoryClient.add_client(self.client)
        self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        self.repositoryImprumut.remove_client_cu_imprumuturi(self.client)
        clienti_cu_carti = self.repositoryImprumut.get_clienti_cu_carti()
        self.assertEqual(len(clienti_cu_carti), 0)

class TestRemoveCarteImprumutata(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        self.titlu = "Carbon Modificat"
        self.descriere = "Sci-Fi"
        self.autor = "Richard Morgan"
        self.carte = Carte(self.id_carte, self.titlu, self.descriere, self.autor)
        self.id_client = 1
        self.nume = "Ion Popescu"
        self.client = Client(self.id_client, self.nume)

    def test_remove_carte(self):
        self.repositoryCarte.add_carte(self.carte)
        self.repositoryClient.add_client(self.client)
        self.servicesImprumut.imprumuta_carte(self.id_client, self.id_carte)
        self.repositoryImprumut.remove_carte_imprumutata(self.carte)
        clienti_cu_carti = self.repositoryImprumut.get_clienti_cu_carti()
        self.assertEqual(len(clienti_cu_carti), 0)

class TestTopCartiImprumutate(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        placeholder = "..."
        self.carte = Carte(self.id_carte, placeholder, placeholder, placeholder)
        self.id_carte2 = 2
        self.carte2 = Carte(self.id_carte2, placeholder, placeholder, placeholder)
        self.id_carte3 = 3
        self.carte3 = Carte(self.id_carte3, placeholder, placeholder, placeholder)
        self.id_carte4 = 4
        self.carte4 = Carte(self.id_carte4, placeholder, placeholder, placeholder)

        self.id_client = 1
        self.client = Client(self.id_client, placeholder)
        self.id_client2 = 2
        self.client2 = Client(self.id_client2, placeholder)
        self.id_client3 = 3
        self.client3 = Client(self.id_client3, placeholder)
        self.id_client4 = 4
        self.client4 = Client(self.id_client4, placeholder)

    def test_top_carti(self):
        self.repositoryCarte.add_carte(self.carte)
        self.repositoryCarte.add_carte(self.carte2)
        self.repositoryCarte.add_carte(self.carte3)
        self.repositoryCarte.add_carte(self.carte4)
        self.repositoryClient.add_client(self.client)
        self.repositoryClient.add_client(self.client2)
        self.repositoryClient.add_client(self.client3)
        self.repositoryClient.add_client(self.client4)

        self.repositoryImprumut.add_imprumut(self.client, self.carte)
        self.repositoryImprumut.add_imprumut(self.client, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client2, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client2, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client3, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client4, self.carte4)

        top = self.servicesImprumut.top_carti_imprumutate()
        self.assertEqual(top,[
            (self.carte3, [self.client, self.client2, self.client3]),
            (self.carte2, [self.client, self.client2]),
            (self.carte, [self.client])])

class TestClientiCuCartiSorted(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        placeholder = "..."
        self.carte = Carte(self.id_carte, placeholder, placeholder, placeholder)
        self.id_carte2 = 2
        self.carte2 = Carte(self.id_carte2, placeholder, placeholder, placeholder)
        self.id_carte3 = 3
        self.carte3 = Carte(self.id_carte3, placeholder, placeholder, placeholder)
        self.id_carte4 = 4
        self.carte4 = Carte(self.id_carte4, placeholder, placeholder, placeholder)

        self.id_client = 1
        nume = "a"
        self.client = Client(self.id_client, nume)
        self.id_client2 = 2
        nume2 = "e"
        self.client2 = Client(self.id_client2, nume2)
        self.id_client3 = 3
        nume3 = "d"
        self.client3 = Client(self.id_client3, nume3)
        self.id_client4 = 4
        nume4 = "b"
        self.client4 = Client(self.id_client4, nume4)

    def test_clienti_sorted(self):
        self.repositoryCarte.add_carte(self.carte)
        self.repositoryCarte.add_carte(self.carte2)
        self.repositoryCarte.add_carte(self.carte3)
        self.repositoryCarte.add_carte(self.carte4)

        self.repositoryClient.add_client(self.client)
        self.repositoryClient.add_client(self.client2)
        self.repositoryClient.add_client(self.client3)
        self.repositoryClient.add_client(self.client4)

        self.repositoryImprumut.add_imprumut(self.client, self.carte)
        self.repositoryImprumut.add_imprumut(self.client, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client2, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client3, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client3, self.carte4)
        self.repositoryImprumut.add_imprumut(self.client4, self.carte4)

        lista_clienti = self.servicesImprumut.clienti_cu_carti_sorted()
        self.assertEqual(lista_clienti, [
            (self.client, [self.carte, self.carte2, self.carte3]),
            (self.client3, [self.carte3, self.carte4]),
            (self.client4, [self.carte4]),
            (self.client2, [self.carte2])
        ])

class TestTopClientiCuCarti(unittest.TestCase):
    def setUp(self):
        self.repositoryCarte = RepositoryCarte()
        self.repositoryClient = RepositoryClient()
        self.repositoryImprumut = RepositoryImprumut()
        self.servicesImprumut = ServicesImprumut(self.repositoryCarte, self.repositoryClient, self.repositoryImprumut)

        self.id_carte = 1
        placeholder = "..."
        self.carte = Carte(self.id_carte, placeholder, placeholder, placeholder)
        self.id_carte2 = 2
        self.carte2 = Carte(self.id_carte2, placeholder, placeholder, placeholder)
        self.id_carte3 = 3
        self.carte3 = Carte(self.id_carte3, placeholder, placeholder, placeholder)
        self.id_carte4 = 4
        self.carte4 = Carte(self.id_carte4, placeholder, placeholder, placeholder)

        self.id_client = 1
        self.client = Client(self.id_client, placeholder)
        self.id_client2 = 2
        self.client2 = Client(self.id_client2, placeholder)
        self.id_client3 = 3
        self.client3 = Client(self.id_client3, placeholder)
        self.id_client4 = 4
        self.client4 = Client(self.id_client4, placeholder)
        self.id_client5 = 5
        self.client5 = Client(self.id_client5, placeholder)

    def test_top_clienti(self):
        self.repositoryCarte.add_carte(self.carte)
        self.repositoryCarte.add_carte(self.carte2)
        self.repositoryCarte.add_carte(self.carte3)
        self.repositoryCarte.add_carte(self.carte4)

        self.repositoryClient.add_client(self.client)
        self.repositoryClient.add_client(self.client2)
        self.repositoryClient.add_client(self.client3)
        self.repositoryClient.add_client(self.client4)
        self.repositoryClient.add_client(self.client5)

        self.repositoryImprumut.add_imprumut(self.client, self.carte)
        self.repositoryImprumut.add_imprumut(self.client, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client2, self.carte)
        self.repositoryImprumut.add_imprumut(self.client2, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client3, self.carte2)
        self.repositoryImprumut.add_imprumut(self.client3, self.carte3)
        self.repositoryImprumut.add_imprumut(self.client3, self.carte4)
        self.repositoryImprumut.add_imprumut(self.client4, self.carte4)
        self.repositoryImprumut.add_imprumut(self.client5, self.carte)

        top_clienti = self.servicesImprumut.top_clienti_cu_carti()
        self.assertEqual(top_clienti, [(self.client, [self.carte, self.carte2, self.carte3])])

def run_tests_imprumuturi():
    unittest.main()