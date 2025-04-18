from Business.services_material import ServicesMaterial
from Repository.depozit import RepositoryMateriale
from UI.console import Console
from Teste.teste import run_tests

def main():
    repositoryMateriale = RepositoryMateriale()
    servicesMateriale = ServicesMaterial(repositoryMateriale)
    Console.run_menu(servicesMateriale)

if __name__ == '__main__':
    run_tests()
    main()