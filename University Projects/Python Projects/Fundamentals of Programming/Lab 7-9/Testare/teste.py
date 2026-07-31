from Business.services_carte import ServicesCarte
from Business.services_imprumut import ServicesImprumut
from Domain.carte import Carte
from Domain.client import Client
from Repository.clientela import RepositoryClient
from Repository.depozit import RepositoryCarte
from Repository.imprumut import RepositoryImprumut
from Validare.validator_carte import ValidateCarte
from Validare.validator_client import ValidateClient
from Validare.validator_imprumut import ValidateImprumut

def test_carte_domain():
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    assert id == carte.get_id()
    assert titlu == carte.get_titlu()
    assert descriere == carte.get_descriere()
    assert autor == carte.get_autor()

def test_validate_carte():
    id_invalid = -1
    titlu_invalid = ""
    descriere_invalida = ""
    autor_invalid = ""
    carte_invalida = Carte(id_invalid, titlu_invalid, descriere_invalida, autor_invalid)
    try:
        ValidateCarte.validate_carte(carte_invalida)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!\nTitlu invalid!\nDescriere invalida!\nAutor invalid!"

def test_validate_id_carte():
    id_invalid = -1
    try:
        ValidateCarte.validate_id(id_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!"

def test_validate_titlu():
    titlu_invalid = ""
    try:
        ValidateCarte.validate_titlu(titlu_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "Titlu invalid!"

def test_validate_autor():
    autor_invalid = ""
    try:
        ValidateCarte.validate_autor(autor_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "Autor invalid!"

def test_validate_id_titlu():
    id_invalid = -1
    titlu_invalid = ""
    try:
        ValidateCarte.validate_id_titlu(id_invalid, titlu_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!\nTitlu invalid!"

def test_validate_id_descriere():
    id_invalid = -1
    descriere_invalida = ""
    try:
        ValidateCarte.validate_id_descriere(id_invalid, descriere_invalida)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!\nDescriere invalida!"

def test_validate_id_autor():
    id_invalid = -1
    autor_invalid = ""
    try:
        ValidateCarte.validate_id_autor(id_invalid, autor_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!\nAutor invalid!"

def test_add_carte():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    repository.add_carte(carte)
    carti = repository.get_carti()
    assert len(carti) == 1
    # assert carti[id] == carte
    assert carti[0] == carte
    try:
        repository.add_carte(carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea exista deja!"

def test_update_titlu_carte():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    assert titlu == carte.get_titlu()
    titlu_nou = "Jackson"
    try:
        repository.update_titlu_carte(id, titlu_nou)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    repository.add_carte(carte)
    repository.update_titlu_carte(id, titlu_nou)
    assert titlu_nou == carte.get_titlu()

def test_update_descriere_carte():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    assert descriere == carte.get_descriere()
    descriere_noua = "Science-Fiction"
    try:
        repository.update_descriere_carte(id, descriere_noua)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    repository.add_carte(carte)
    repository.update_descriere_carte(id, descriere_noua)
    assert descriere_noua == carte.get_descriere()

def test_update_autor_carte():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    assert autor == carte.get_autor()
    autor_nou = "Riordan"
    try:
        repository.update_descriere_carte(id, autor_nou)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    repository.add_carte(carte)
    repository.update_autor_carte(id, autor_nou)
    assert autor_nou == carte.get_autor()

def test_remove_carte():
    repository = RepositoryCarte()
    id = 1
    try:
        repository.remove_carte(id)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    repository.add_carte(carte)
    repository.remove_carte(id)
    carti = repository.get_carti()
    assert len(carti) == 0

def test_search_carte_by_id():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    try:
        carte_gasita = repository.search_carte_by_id(id)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    repository.add_carte(carte)
    carte_gasita = repository.search_carte_by_id(id)
    assert carte == carte_gasita

def test_search_carti_by_titlu():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    try:
        solutie = repository.search_carti_by_titlu(titlu)
        assert False
    except ValueError as errors:
        assert str(errors) == "Nu exista nicio carte cu acest titlu!"
    descriere = "Sci-Fi"
    autor = "Rick"
    carte = Carte(id, titlu, descriere, autor)
    repository.add_carte(carte)
    id2 = 2
    descriere2 = "Science-Fiction"
    autor2 = "Riordan"
    carte2 = Carte(id2, titlu, descriere2, autor2)
    repository.add_carte(carte2)
    id3 = 3
    titlu3 = "..."
    descriere3 = "..."
    autor3 = "..."
    carte3 = Carte(id3, titlu3, descriere3, autor3)
    repository.add_carte(carte3)
    solutie = repository.search_carti_by_titlu(titlu)
    carti = repository.get_carti()
    assert len(carti) == 3
    assert solutie == [carte, carte2]

def test_search_carti_by_autor():
    repository = RepositoryCarte()
    id = 1
    titlu = "Percy"
    descriere = "Sci-Fi"
    autor = "Rick"
    try:
        solutie = repository.search_carti_by_autor(autor)
        assert False
    except ValueError as errors:
        assert str(errors) == "Nu exista nicio carte scrisa de acest autor!"
    carte = Carte(id, titlu, descriere, autor)
    repository.add_carte(carte)
    id2 = 2
    titlu2 = "Jackson"
    descriere2 = "Science-Fiction"
    carte2 = Carte(id2, titlu2, descriere2, autor)
    repository.add_carte(carte2)
    id3 = 3
    titlu3 = "..."
    descriere3 = "..."
    autor3 = "..."
    carte3 = Carte(id3, titlu3, descriere3, autor3)
    repository.add_carte(carte3)
    solutie = repository.search_carti_by_autor(autor)
    carti = repository.get_carti()
    assert len(carti) == 3
    assert solutie == [carte, carte2]

def test_client_domain():
    id = 1
    nume = "Ion Popescu"
    client = Client(id, nume)
    assert id == client.get_id()
    assert nume == client.get_nume()

def test_validate_client():
    id_invalid = -1
    nume_invalid = ""
    client_invalid = Client(id_invalid, nume_invalid)
    try:
        ValidateClient.validate_client(client_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!\nNume invalid!"

def test_validate_id_nume():
    id_invalid = -1
    nume_invalid = ""
    try:
        ValidateClient.validate_id_nume(id_invalid, nume_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!\nNume invalid!"

def test_validate_id():
    id_invalid = -1
    try:
        ValidateClient.validate_id(id_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID invalid!"

def test_validate_nume():
    nume_invalid = ""
    try:
        ValidateClient.validate_nume(nume_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "Nume invalid!"

def test_add_client():
    repository = RepositoryClient()
    id = 1
    nume = "Ion Popescu"
    client = Client(id, nume)
    repository.add_client(client)
    clienti = repository.get_clienti()
    assert len(clienti) == 1
    assert clienti[0] == client
    try:
        repository.add_client(client)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul exista deja!"

def test_update_client():
    repository = RepositoryClient()
    id = 1
    nume = "Ion Popescu"
    client = Client(id, nume)
    assert nume == client.get_nume()
    nume_nou = "Vasile Popescu"
    try:
        repository.update_client(id, nume_nou)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul nu exista!"
    repository.add_client(client)
    repository.update_client(id, nume_nou)
    assert nume_nou == client.get_nume()

def test_remove_client():
    repository = RepositoryClient()
    id = 1
    nume = "Ion Popescu"
    client = Client(id, nume)
    try:
        repository.remove_client(id)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul nu exista!"
    repository.add_client(client)
    repository.remove_client(id)
    clienti = repository.get_clienti()
    assert len(clienti) == 0

def test_search_client_by_id():
    repository = RepositoryClient()
    id = 1
    nume = "Ion Popescu"
    client = Client(id, nume)
    try:
        client_gasit = repository.search_client_by_id(id)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul nu exista!"
    repository.add_client(client)
    client_gasit = repository.search_client_by_id(id)
    assert client == client_gasit

def test_search_clienti_by_nume():
    repository = RepositoryClient()
    id = 1
    nume = "Ion Popescu"
    client = Client(id, nume)
    try:
        client_gasit = repository.search_clienti_by_nume(nume, None, None)
        assert False
    except ValueError as errors:
        assert str(errors) == "Nu exista niciun client cu acest nume!"
    repository.add_client(client)
    id2 = 2
    client2 = Client(id2, nume)
    repository.add_client(client2)
    id3 = 3
    nume3 = "..."
    client3 = Client(id3, nume3)
    repository.add_client(client3)
    clienti_gasiti = repository.search_clienti_by_nume(nume, None, None)
    assert clienti_gasiti == [client, client2]

def test_validate_imprumut():
    id_client_invalid = -1
    id_carte_invalid = -1
    try:
        ValidateImprumut.validate_imprumut(id_client_invalid, id_carte_invalid)
        assert False
    except ValueError as errors:
        assert str(errors) == "ID-ul clientului este invalid!\nID-ul cartii este invalid!"

def test_imprumuta_carte():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "Carbon Modificat"
    descriere = "Sci-Fi"
    autor = "Richard Morgan"
    carte = Carte(id_carte, titlu, descriere, autor)
    id_client = 1
    nume = "Ion Popescu"
    client = Client(id_client, nume)
    try:
        servicesImprumut.imprumuta_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul nu exista!"
    repositoryClient.add_client(client)
    try:
        servicesImprumut.imprumuta_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    repositoryCarte.add_carte(carte)
    servicesImprumut.imprumuta_carte(id_client, id_carte)
    try:
        servicesImprumut.imprumuta_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul a imprumutat deja cartea!"
    clienti_cu_carti = repositoryImprumut.get_clienti_cu_carti()
    assert clienti_cu_carti[client] == [carte]

def test_returnare_carte():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "Carbon Modificat"
    descriere = "Sci-Fi"
    autor = "Richard Morgan"
    carte = Carte(id_carte, titlu, descriere, autor)
    id_client = 1
    nume = "Ion Popescu"
    client = Client(id_client, nume)
    try:
        servicesImprumut.returnare_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul nu exista!"
    repositoryClient.add_client(client)
    try:
        servicesImprumut.returnare_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu exista!"
    repositoryCarte.add_carte(carte)
    try:
        servicesImprumut.returnare_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Clientul nu a imprumutat nicio carte!"
    id_carte_2 = 2
    carte_2 = Carte(id_carte_2, titlu, descriere, autor)
    repositoryCarte.add_carte(carte_2)
    servicesImprumut.imprumuta_carte(id_client, id_carte_2)
    try:
        servicesImprumut.returnare_carte(id_client, id_carte)
        assert False
    except ValueError as errors:
        assert str(errors) == "Cartea nu a fost imprumutata!"
    servicesImprumut.returnare_carte(id_client, id_carte_2)
    clienti_cu_carti = repositoryImprumut.get_clienti_cu_carti()
    assert len(clienti_cu_carti) == 0

def test_remove_client_cu_imprumuturi():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "Carbon Modificat"
    descriere = "Sci-Fi"
    autor = "Richard Morgan"
    carte = Carte(id_carte, titlu, descriere, autor)
    repositoryCarte.add_carte(carte)
    id_client = 1
    nume = "Ion Popescu"
    client = Client(id_client, nume)
    repositoryClient.add_client(client)
    id_client_2 = 2
    client_2 = Client(id_client_2, nume)
    repositoryClient.add_client(client_2)
    servicesImprumut.imprumuta_carte(id_client, id_carte)
    servicesImprumut.imprumuta_carte(id_client_2, id_carte)
    clienti_cu_carti = repositoryImprumut.get_clienti_cu_carti()
    carti_imprumutate = repositoryImprumut.get_carti_imprumutate()
    assert clienti_cu_carti == {client: [carte], client_2: [carte]}
    assert carti_imprumutate == {carte: [client, client_2]}
    repositoryImprumut.remove_client_cu_imprumuturi(client)
    assert clienti_cu_carti == {client_2: [carte]}
    assert carti_imprumutate == {carte: [client_2]}
    repositoryImprumut.remove_client_cu_imprumuturi(client_2)
    assert len(clienti_cu_carti) == 0
    assert len(carti_imprumutate) == 0

def test_remove_carte_imprumutata():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "Carbon Modificat"
    descriere = "Sci-Fi"
    autor = "Richard Morgan"
    carte = Carte(id_carte, titlu, descriere, autor)
    repositoryCarte.add_carte(carte)
    id_client = 1
    nume = "Ion Popescu"
    client = Client(id_client, nume)
    repositoryClient.add_client(client)
    id_carte_2 = 2
    carte_2 = Carte(id_carte_2, titlu, descriere, autor)
    repositoryCarte.add_carte(carte_2)
    servicesImprumut.imprumuta_carte(id_client, id_carte)
    servicesImprumut.imprumuta_carte(id_client, id_carte_2)
    clienti_cu_carti = repositoryImprumut.get_clienti_cu_carti()
    carti_imprumutate = repositoryImprumut.get_carti_imprumutate()
    assert clienti_cu_carti == {client: [carte, carte_2]}
    assert carti_imprumutate == {carte: [client], carte_2: [client]}
    repositoryImprumut.remove_carte_imprumutata(carte)
    assert clienti_cu_carti == {client: [carte_2]}
    assert carti_imprumutate == {carte_2: [client]}
    repositoryImprumut.remove_carte_imprumutata(carte_2)
    assert len(clienti_cu_carti) == 0
    assert len(carti_imprumutate) == 0

def test_top_carti_imprumutate():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "..."
    descriere = "..."
    autor = "..."
    carte = Carte(id_carte, titlu, descriere, autor)
    repositoryCarte.add_carte(carte)
    id_carte2 = 2
    carte2 = Carte(id_carte2, titlu, descriere, autor)
    repositoryCarte.add_carte(carte2)
    id_carte3 = 3
    carte3 = Carte(id_carte3, titlu, descriere, autor)
    repositoryCarte.add_carte(carte3)
    id_carte4 = 4
    carte4 = Carte(id_carte4, titlu, descriere, autor)
    repositoryCarte.add_carte(carte4)
    id_client = 1
    nume = "..."
    client = Client(id_client, nume)
    repositoryClient.add_client(client)
    id_client2 = 2
    client2 = Client(id_client2, nume)
    repositoryClient.add_client(client2)
    id_client3 = 3
    client3 = Client(id_client3, nume)
    repositoryClient.add_client(client3)
    id_client4 = 4
    client4 = Client(id_client4, nume)
    repositoryClient.add_client(client4)
    repositoryImprumut.add_imprumut(client, carte)
    repositoryImprumut.add_imprumut(client, carte2)
    repositoryImprumut.add_imprumut(client2, carte2)
    repositoryImprumut.add_imprumut(client, carte3)
    repositoryImprumut.add_imprumut(client2, carte3)
    repositoryImprumut.add_imprumut(client3, carte3)
    repositoryImprumut.add_imprumut(client4, carte4)
    top = servicesImprumut.top_carti_imprumutate()
    assert top == [(carte3, [client, client2, client3]), (carte2, [client, client2]), (carte, [client])]

def test_clienti_cu_carti_sorted():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "..."
    descriere = "..."
    autor = "..."
    carte = Carte(id_carte, titlu, descriere, autor)
    repositoryCarte.add_carte(carte)
    id_carte2 = 2
    carte2 = Carte(id_carte2, titlu, descriere, autor)
    repositoryCarte.add_carte(carte2)
    id_carte3 = 3
    carte3 = Carte(id_carte3, titlu, descriere, autor)
    repositoryCarte.add_carte(carte3)
    id_carte4 = 4
    carte4 = Carte(id_carte4, titlu, descriere, autor)
    repositoryCarte.add_carte(carte4)
    id_client = 1
    nume = "a"
    client = Client(id_client, nume)
    repositoryClient.add_client(client)
    id_client2 = 2
    nume_2 = "e"
    client2 = Client(id_client2, nume_2)
    repositoryClient.add_client(client2)
    id_client3 = 3
    nume_3 = "d"
    client3 = Client(id_client3, nume_3)
    repositoryClient.add_client(client3)
    id_client4 = 4
    nume_4 = "b"
    client4 = Client(id_client4, nume_4)
    repositoryClient.add_client(client4)
    repositoryImprumut.add_imprumut(client, carte)
    repositoryImprumut.add_imprumut(client, carte2)
    repositoryImprumut.add_imprumut(client, carte3)
    repositoryImprumut.add_imprumut(client2, carte2)
    repositoryImprumut.add_imprumut(client3, carte3)
    repositoryImprumut.add_imprumut(client3, carte4)
    repositoryImprumut.add_imprumut(client4, carte4)
    lista_clienti = servicesImprumut.clienti_cu_carti_sorted()
    assert lista_clienti == [(client, [carte, carte2, carte3]), (client3, [carte3, carte4]), (client4, [carte4]), (client2, [carte2])]

def test_top_clienti_cu_carti():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "..."
    descriere = "..."
    autor = "..."
    carte = Carte(id_carte, titlu, descriere, autor)
    repositoryCarte.add_carte(carte)
    id_carte2 = 2
    carte2 = Carte(id_carte2, titlu, descriere, autor)
    repositoryCarte.add_carte(carte2)
    id_carte3 = 3
    carte3 = Carte(id_carte3, titlu, descriere, autor)
    repositoryCarte.add_carte(carte3)
    id_carte4 = 4
    carte4 = Carte(id_carte4, titlu, descriere, autor)
    repositoryCarte.add_carte(carte4)
    id_client = 1
    nume = "..."
    client = Client(id_client, nume)
    repositoryClient.add_client(client)
    id_client2 = 2
    client2 = Client(id_client2, nume)
    repositoryClient.add_client(client2)
    id_client3 = 3
    client3 = Client(id_client3, nume)
    repositoryClient.add_client(client3)
    id_client4 = 4
    client4 = Client(id_client4, nume)
    repositoryClient.add_client(client4)
    id_client5 = 5
    client5 = Client(id_client5, nume)
    repositoryClient.add_client(client5)
    repositoryImprumut.add_imprumut(client, carte)
    repositoryImprumut.add_imprumut(client, carte2)
    repositoryImprumut.add_imprumut(client, carte3)
    repositoryImprumut.add_imprumut(client2, carte)
    repositoryImprumut.add_imprumut(client2, carte2)
    repositoryImprumut.add_imprumut(client3, carte2)
    repositoryImprumut.add_imprumut(client3, carte3)
    repositoryImprumut.add_imprumut(client3, carte4)
    repositoryImprumut.add_imprumut(client4, carte4)
    repositoryImprumut.add_imprumut(client5, carte)
    lista_clienti = servicesImprumut.top_clienti_cu_carti()
    assert lista_clienti == [(client, [carte, carte2, carte3])]

def test_carti_imprumutate_sorted():
    repositoryCarte = RepositoryCarte()
    repositoryClient = RepositoryClient()
    repositoryImprumut = RepositoryImprumut()
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)
    id_carte = 1
    titlu = "a"
    descriere = "..."
    autor = "..."
    carte = Carte(id_carte, titlu, descriere, autor)
    repositoryCarte.add_carte(carte)
    id_carte2 = 2
    titlu_2 = "b"
    carte2 = Carte(id_carte2, titlu_2, descriere, autor)
    repositoryCarte.add_carte(carte2)
    id_carte3 = 3
    titlu_3 = "d"
    carte3 = Carte(id_carte3, titlu_3, descriere, autor)
    repositoryCarte.add_carte(carte3)
    id_carte4 = 4
    titlu_4 = "c"
    carte4 = Carte(id_carte4, titlu_4, descriere, autor)
    repositoryCarte.add_carte(carte4)
    id_client = 1
    nume = "..."
    client = Client(id_client, nume)
    repositoryClient.add_client(client)
    id_client2 = 2
    client2 = Client(id_client2, nume)
    repositoryClient.add_client(client2)
    id_client3 = 3
    client3 = Client(id_client3, nume)
    repositoryClient.add_client(client3)
    id_client4 = 4
    client4 = Client(id_client4, nume)
    repositoryClient.add_client(client4)
    repositoryImprumut.add_imprumut(client, carte)
    repositoryImprumut.add_imprumut(client, carte2)
    repositoryImprumut.add_imprumut(client, carte3)
    repositoryImprumut.add_imprumut(client2, carte2)
    repositoryImprumut.add_imprumut(client3, carte2)
    repositoryImprumut.add_imprumut(client3, carte3)
    repositoryImprumut.add_imprumut(client3, carte4)
    repositoryImprumut.add_imprumut(client4, carte4)
    lista_carti = servicesImprumut.carti_imprumutate_sorted()
    assert lista_carti == [(carte2, [client, client2, client3]), (carte4, [client3, client4]), (carte3, [client, client3]), (carte, [client])]

def test_generate_X_carti():
    repositoryCarte = RepositoryCarte()
    repositoryImprumut = RepositoryImprumut()
    servicesCarte = ServicesCarte(repositoryCarte, repositoryImprumut)
    X = 10
    servicesCarte.generate_X_carti(X)
    carti = repositoryCarte.get_carti()
    assert len(carti) == 10

def run_tests():
    test_carte_domain()
    test_validate_carte()
    test_validate_id_carte()
    test_validate_titlu()
    test_validate_autor()
    test_validate_id_titlu()
    test_validate_id_descriere()
    test_validate_id_autor()
    test_add_carte()
    test_update_titlu_carte()
    test_update_descriere_carte()
    test_update_autor_carte()
    test_remove_carte()
    test_search_carte_by_id()
    test_search_carti_by_titlu()
    test_search_carti_by_autor()
    test_client_domain()
    test_validate_client()
    test_validate_id_nume()
    test_validate_id()
    test_validate_nume()
    test_add_client()
    test_update_client()
    test_remove_client()
    test_search_client_by_id()
    test_search_clienti_by_nume()
    test_validate_imprumut()
    test_imprumuta_carte()
    test_returnare_carte()
    test_generate_X_carti()
    test_remove_client_cu_imprumuturi()
    test_remove_carte_imprumutata()
    test_top_carti_imprumutate()
    test_clienti_cu_carti_sorted()
    test_top_clienti_cu_carti()
    test_carti_imprumutate_sorted()
    # print("Merge")