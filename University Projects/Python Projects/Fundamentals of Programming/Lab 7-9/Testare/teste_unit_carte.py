from Domain.carte import Carte
from Repository.depozit import RepositoryCarte
from Validare.validator_carte import ValidateCarte
import unittest

class TestCarteDomain(unittest.TestCase):
    def setUp(self):
        self.id_carte = 1
        self.titlu = "Percy"
        self.descriere = "Sci-Fi"
        self.autor = "Rick"
        self.carte = Carte(self.id_carte, self.titlu, self.descriere, self.autor)

    def test_carte_domain(self):
        self.assertEqual(self.id_carte, self.carte.get_id())
        self.assertEqual(self.titlu, self.carte.get_titlu())
        self.assertEqual(self.descriere, self.carte.get_descriere())
        self.assertEqual(self.autor, self.carte.get_autor())

class TestValidateCarte(unittest.TestCase):
    def setUp(self):
        self.id_invalid = -1
        self.titlu_invalid = ""
        self.descriere_invalida = ""
        self.autor_invalid = ""
        self.carte_invalida = Carte(self.id_invalid, self.titlu_invalid, self.descriere_invalida, self.autor_invalid)

        self.id_invalid2 = 0
        self.carte_invalida2 = Carte(self.id_invalid2, self.titlu_invalid, self.descriere_invalida, self.autor_invalid)

        self.id_valid = 1
        self.titlu = "Percy"
        self.descriere = "Sci-Fi"
        self.autor = "Rick"
        self.carte = Carte(self.id_valid, self.titlu, self.descriere, self.autor)

    def test_validate_carte(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_carte(self.carte_invalida)
        self.assertEqual(str(context.exception),"ID invalid!\nTitlu invalid!\nDescriere invalida!\nAutor invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_carte(self.carte_invalida2)
        self.assertEqual(str(context.exception),"ID invalid!\nTitlu invalid!\nDescriere invalida!\nAutor invalid!")

        try:
            ValidateCarte.validate_carte(self.carte)
        except ValueError:
            self.assertFalse(True)

    def test_validate_id_carte(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id(self.id_invalid)
        self.assertEqual(str(context.exception), "ID invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id(self.id_invalid2)
        self.assertEqual(str(context.exception), "ID invalid!")

        try:
            ValidateCarte.validate_id(self.id_valid)
        except ValueError:
            self.assertFalse(True)

    def test_validate_titlu(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_titlu(self.titlu_invalid)
        self.assertEqual(str(context.exception), "Titlu invalid!")

        try:
            ValidateCarte.validate_titlu(self.titlu)
        except ValueError:
            self.assertFalse(True)

    def test_validate_autor(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_autor(self.autor_invalid)
        self.assertEqual(str(context.exception), "Autor invalid!")

        try:
            ValidateCarte.validate_autor(self.autor)
        except ValueError:
            self.assertFalse(True)

    def test_validate_id_titlu(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id_titlu(self.id_invalid, self.titlu_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nTitlu invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id_titlu(self.id_invalid2, self.titlu_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nTitlu invalid!")

        try:
            ValidateCarte.validate_id_titlu(self.id_valid, self.titlu)
        except ValueError:
            self.assertFalse(True)

    def test_validate_id_descriere(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id_descriere(self.id_invalid, self.descriere_invalida)
        self.assertEqual(str(context.exception), "ID invalid!\nDescriere invalida!")

        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id_descriere(self.id_invalid2, self.descriere_invalida)
        self.assertEqual(str(context.exception), "ID invalid!\nDescriere invalida!")

        try:
            ValidateCarte.validate_id_descriere(self.id_valid, self.descriere)
        except ValueError:
            self.assertFalse(True)

    def test_validate_id_autor(self):
        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id_autor(self.id_invalid, self.autor_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nAutor invalid!")

        with self.assertRaises(ValueError) as context:
            ValidateCarte.validate_id_autor(self.id_invalid2, self.autor_invalid)
        self.assertEqual(str(context.exception), "ID invalid!\nAutor invalid!")

        try:
            ValidateCarte.validate_id_autor(self.id_valid, self.autor)
        except ValueError:
            self.assertFalse(True)

class TestRepositoryCarte(unittest.TestCase):
    def setUp(self):
        self.repository = RepositoryCarte()
        self.id_carte = 1
        self.titlu = "Percy"
        self.descriere = "Sci-Fi"
        self.autor = "Rick"
        self.carte = Carte(self.id_carte, self.titlu, self.descriere, self.autor)

        self.titlu_nou = "Jackson"
        self.descriere_noua = "Science-Fiction"
        self.autor_nou = "Riordan"

        id2 = 2
        self.carte2 = Carte(id2, self.titlu, self.descriere, self.autor)
        id3 = 3
        placeholder = "..."
        self.carte3 = Carte(id3, placeholder, placeholder, placeholder)

    def test_add_carte(self):
        self.repository.add_carte(self.carte)
        carti = self.repository.get_carti()
        self.assertEqual(len(carti), 1)
        self.assertEqual(carti[0], self.carte)
        with self.assertRaises(ValueError) as context:
            self.repository.add_carte(self.carte)
        self.assertEqual(str(context.exception), "Cartea exista deja!")

    def test_update_titlu_carte(self):
        with self.assertRaises(ValueError) as context:
            self.repository.update_titlu_carte(self.id_carte, self.titlu_nou)
        self.assertEqual(str(context.exception), "Cartea nu exista!")
        self.repository.add_carte(self.carte)
        self.repository.update_titlu_carte(self.id_carte, self.titlu_nou)
        self.assertEqual(self.titlu_nou, self.carte.get_titlu())

    def test_update_descriere_carte(self):
        with self.assertRaises(ValueError) as context:
            self.repository.update_descriere_carte(self.id_carte, self.descriere_noua)
        self.assertEqual(str(context.exception), "Cartea nu exista!")
        self.repository.add_carte(self.carte)
        self.repository.update_descriere_carte(self.id_carte, self.descriere_noua)
        self.assertEqual(self.descriere_noua, self.carte.get_descriere())

    def test_update_autor_carte(self):
        with self.assertRaises(ValueError) as context:
            self.repository.update_autor_carte(self.id_carte, self.autor_nou)
        self.assertEqual(str(context.exception), "Cartea nu exista!")
        self.repository.add_carte(self.carte)
        self.repository.update_autor_carte(self.id_carte, self.autor_nou)
        self.assertEqual(self.autor_nou, self.carte.get_autor())

    def test_remove_carte(self):
        with self.assertRaises(ValueError) as context:
            self.repository.remove_carte(self.id_carte)
        self.assertEqual(str(context.exception), "Cartea nu exista!")
        self.repository.add_carte(self.carte)
        self.repository.remove_carte(self.id_carte)
        carti = self.repository.get_carti()
        self.assertEqual(len(carti), 0)

    def test_search_carte_by_id(self):
        with self.assertRaises(ValueError) as context:
            self.repository.search_carte_by_id(self.id_carte)
        self.assertEqual(str(context.exception), "Cartea nu exista!")
        self.repository.add_carte(self.carte)
        carte_gasita = self.repository.search_carte_by_id(self.id_carte)
        self.assertEqual(self.carte, carte_gasita)

    def test_search_carti_by_titlu(self):
        with self.assertRaises(ValueError) as context:
            self.repository.search_carti_by_titlu(self.titlu)
        self.assertEqual(str(context.exception), "Nu exista nicio carte cu acest titlu!")
        self.repository.add_carte(self.carte)
        self.repository.add_carte(self.carte2)
        self.repository.add_carte(self.carte3)
        solutie = self.repository.search_carti_by_titlu(self.titlu)
        self.assertEqual(solutie, [self.carte, self.carte2])

    def test_search_carti_by_autor(self):
        with self.assertRaises(ValueError) as context:
            self.repository.search_carti_by_autor(self.autor)
        self.assertEqual(str(context.exception), "Nu exista nicio carte scrisa de acest autor!")
        self.repository.add_carte(self.carte)
        self.repository.add_carte(self.carte2)
        self.repository.add_carte(self.carte3)
        solutie = self.repository.search_carti_by_autor(self.autor)
        self.assertEqual(solutie, [self.carte, self.carte2])

def run_tests_carte():
    unittest.main()