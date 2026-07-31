from Business.services_carte import ServicesCarte
from Business.services_client import ServicesClient
from Business.services_imprumut import ServicesImprumut
from FileRepository.file_clientela import FileRepositoryClient
from FileRepository.file_depozit import FileRepositoryCarte
from FileRepository.file_imprumut import FileRepositoryImprumut
from Repository.clientela import RepositoryClient
from Repository.depozit import RepositoryCarte
from Repository.imprumut import RepositoryImprumut
from Testare.teste import run_tests
from UI.ui_main import MainMenu

def main():
    repositoryImprumut = RepositoryImprumut()
    repositoryCarte = RepositoryCarte()
    servicesCarte = ServicesCarte(repositoryCarte, repositoryImprumut)
    repositoryClient = RepositoryClient()
    servicesClient = ServicesClient(repositoryClient, repositoryImprumut)
    servicesImprumut = ServicesImprumut(repositoryCarte, repositoryClient, repositoryImprumut)

    path_file_carte = "Repository/carti.txt"
    path_file_client = "Repository/clienti.txt"
    path_file_imprumut = "Repository/imprumuturi.txt"
    repositoryFileCarte = FileRepositoryCarte(path_file_carte)
    repositoryFileClient = FileRepositoryClient(path_file_client)
    repositoryFileImprumut = FileRepositoryImprumut(repositoryFileCarte, repositoryFileClient, path_file_imprumut)
    servicesFileCarte = ServicesCarte(repositoryFileCarte, repositoryFileImprumut)
    servicesFileClient = ServicesClient(repositoryFileClient, repositoryFileImprumut)
    servicesFileImprumut = ServicesImprumut(repositoryFileCarte, repositoryFileClient, repositoryFileImprumut)

    MainMenu.run_main_menu(servicesCarte, servicesClient, servicesImprumut, servicesFileCarte, servicesFileClient, servicesFileImprumut)

if __name__ == '__main__':
    run_tests()
    main()