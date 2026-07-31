from Domain.automobil import Automobil

def test_domain():
    id = 1
    marca = "BMW"
    pret = 30123.12
    model = "M3"
    data = "29:04:2026"
    automobil = Automobil(id, marca, pret, model, data)
    assert automobil.get_id() == id
    assert automobil.get_marca() == marca
    assert automobil.get_pret() == pret
    assert automobil.get_model() == model
    assert automobil.get_data() == data