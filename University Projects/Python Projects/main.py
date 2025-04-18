# main.py

"""
Modulul reprezintă punctul de intrare al aplicației, inițiind runda de teste pentru verificarea
funcționalităților și pornind interfața utilizator pentru gestiunea cheltuielilor.

Prin lansarea testelor la început, ne asigurăm că toate funcțiile rulează corect înainte ca
utilizatorul să înceapă lucrul efectiv cu aplicația.
"""

from UI.menu import run
from Teste.test import run_tests

if __name__ == '__main__':
    #run_tests()
    run()