from Domain.material import Material
from Repository.depozit import RepositoryMateriale

def test_material_domain():
    cod = 101
    denumire = "Lemn"
    um = "m"
    cantitate = 15
    pret = 32.5
    material = Material(cod, denumire, um, cantitate, pret)
    assert cod == material.get_cod()
    assert denumire == material.get_denumire()
    assert um == material.get_unitate_de_masura()
    assert cantitate == material.get_cantitate_pe_stoc()
    assert pret == material.get_pret_unitar()

def test_add_material():
    repository = RepositoryMateriale()
    cod = 101
    denumire = "Lemn"
    um = "m"
    cantitate = 15
    pret = 32.5
    material = Material(cod, denumire, um, cantitate, pret)
    repository.add_material(material)
    depozit = repository.get_materiale()
    assert len(depozit) == 1
    assert depozit[0] == material
    try:
        repository.add_material(material)
        assert False
    except ValueError as errors:
        assert str(errors) == "Materialul exista deja in depozit!"

def run_tests():
    test_material_domain()
    test_add_material()