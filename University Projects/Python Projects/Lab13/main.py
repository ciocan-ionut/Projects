"""
Cerinta:
Se dau două numere naturale m şi n.
Generaţi liste formate din numere de la 1 la n cu proprietatea că diferenţa (în valoare absolută)
între două numere consecutive din listă este m.
Tipăriţi un mesaj dacă problema nu are soluţie.
"""

"""
Rezolvare problema 11
   solutie candidat: solutie = (x1, x2, ..., xk), xi apartine (1, 2, ..., n)
   conditie consistent: solutie = (x1, x2, ..., xk) e consistent daca xi != xj pentru oricare ar fi i!=j,
                        |xi - xi+1| = m
   conditie solutie: solutie = (x1, x2, ..., xk) e solutie daca e consistent si k <= (n-1)/m + 1
"""

def backtrack_recursiv(n, m, solutie, solutii):
    if len(solutie) > (n - 1) / m + 1:
        return

    if len(solutie) >= 2:
        solutii.append(solutie.copy())

    ult = solutie[-1]

    urm = ult + m
    if urm <= n and urm not in solutie:
        solutie.append(urm)
        backtrack_recursiv(n, m, solutie, solutii)

    urm = ult - m
    if urm >= 1 and urm not in solutie:
        solutie.append(urm)
        backtrack_recursiv(n, m, solutie, solutii)

    solutie.pop()


def backtrack_iterativ(n, m, solutie, solutii):
    stiva = [solutie]
    while stiva:
        sol = stiva.pop()

        if len(sol) > (n - 1) / m + 1:
            continue

        if len(sol) >= 2:
            solutii.append(sol)

        ult = sol[-1]

        urm = ult + m
        if urm <= n and urm not in solutie:
            stiva.append(sol + [urm])

        urm = ult - m
        if urm >= 1 and urm not in solutie:
            stiva.append(sol + [urm])

def test_backtrack():
    n, m = 5, 2
    solutie = [1]
    solutii = []
    backtrack_recursiv(n, m, solutie, solutii)
    assert solutii == [[1, 3], [1, 3, 5]]

    solutie = [1]
    solutii = []
    backtrack_iterativ(n, m, solutie, solutii)
    assert solutii == [[1, 3], [1, 3, 5]]

    n, m = 5, 10
    solutie = [1]
    solutii = []
    backtrack_recursiv(n, m, solutie, solutii)
    assert solutii == []

test_backtrack()
n, m = 5, 2
print("~~~Backtrack recursiv~~~")
for start in range(1, n + 1):
    solutii = []
    backtrack_recursiv(n, m, [start], solutii)
    if not solutii:
        print("Nu are solutii!")
    else:
        for solutie in solutii:
            print(solutie)

print("\n~~~Backtrack iterativ~~~")
for start in range(1, n + 1):
    solutii = []
    backtrack_iterativ(n, m, [start], solutii)
    if not solutii:
        print("Nu are solutii!")
    else:
        for solutie in solutii:
            print(solutie)