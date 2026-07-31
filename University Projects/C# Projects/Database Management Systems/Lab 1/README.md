# Formula 1 SGBD - Aplicație de Gestiune

Aplicație Windows Forms dezvoltată în C# (.NET) pentru gestionarea echipelor de Formula 1 și a piloților acestora. 

## Cum se configurează baza de date
1. Asigurați-vă că aveți instalat **Microsoft SQL Server** și **SQL Server Management Studio (SSMS)**.
2. Deschideți SSMS și conectați-vă la instanța locală.
3. Rulați scripturile pentru crearea tabelelor Teams și Drivers, cât și pentru popularea acestora cu date pentru teste.

## Cum se configurează conexiunea la baza de date
Aplicația folosește `ConfigurationManager` pentru a extrage string-ul de conexiune. 
1. Deschideți fișierul `App.config` din Visual Studio.
2. Căutați secțiunea `<connectionStrings>`.
3. Asigurați-vă că string-ul de conexiune cu numele `Formula1DB` indică spre serverul dumneavoastră local. 

## Cum se rulează aplicația
1. Deschideți soluția (.sln) în Visual Studio.
2. Din meniul de sus, asigurați-vă că proiectul este setat pe Debug sau Release.
3. Apăsați butonul Start (sau tasta F5) pentru a compila și a lansa aplicația.
4. În formularul principal (DashboardForm), faceți click pe o echipă în tabelul din stânga pentru a-i vedea piloții asociați în tabelul din dreapta. Folosiți butoanele Adaugă/Editează/Șterge pentru operațiunile CRUD.