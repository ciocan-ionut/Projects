using Lab_5;
using Microsoft.EntityFrameworkCore;
using Npgsql.EntityFrameworkCore.PostgreSQL;
using System;
using System.Linq;

class Program
{
    static void Main()
    {
        bool running = true;
        while (running)
        {
            Console.WriteLine("\n=== MENIU ===");
            Console.WriteLine("1. Demonstreaza Locking Optimist (Conflict de Concurenta)");
            Console.WriteLine("2. Stergere Soft a unui Angajat");
            Console.WriteLine("3. Vizualizare Angajati Stersi (Vedere Admin)");
            Console.WriteLine("4. Restaurare Angajat Sters");
            Console.WriteLine("0. Iesire");
            Console.Write("Alege o optiune: ");

            var input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    DemonstrateOptimisticLocking();
                    break;
                case "2":
                    SoftDeleteEmployee();
                    break;
                case "3":
                    ViewDeletedEmployees();
                    break;
                case "4":
                    RestoreEmployee();
                    break;
                case "0":
                    running = false;
                    break;
                default:
                    Console.WriteLine("Opțiune invalidă!");
                    break;
            }
        }
    }

    static void DemonstrateOptimisticLocking()
    {
        Console.WriteLine("\n--- DEMO LOCKING OPTIMIST ---");
        try
        {
            using var contextA = new AppDbContext();
            using var contextB = new AppDbContext();

            var empA = contextA.Employees.FirstOrDefault();
            if (empA == null) { Console.WriteLine("Nu exista angajati in DB!"); return; }

            var empB = contextB.Employees.First(e => e.Id == empA.Id);

            Console.WriteLine($"Utilizatorul A si Utilizatorul B au incarcat angajatul {empA.Email} (Versiune: {empA.Version})");
            // Utilizatorul A actualizează salariul
            empA.Salary += 100;
            contextA.SaveChanges();
            Console.WriteLine("Utilizatorul A a salvat modificarile cu succes. (Versiunea in DB a crescut)");

            // Utilizatorul B încearcă să actualizeze salariul folosind datele vechi
            empB.Salary += 500;
            Console.WriteLine("Utilizatorul B incearca sa salveze...");
            contextB.SaveChanges();
        }
        catch (DbUpdateConcurrencyException)
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("-> EROARE INTERCEPTATA: Conflict detectat! Altcineva a modificat inregistrarea intre timp.");
            Console.ResetColor();
        }
    }

    static void SoftDeleteEmployee()
    {
        using var context = new AppDbContext();
        var emp = context.Employees.FirstOrDefault();

        if (emp != null)
        {
            // Apelăm Remove. Datorită override-ului din SaveChanges, se va transforma în Soft Delete
            context.Employees.Remove(emp);
            context.SaveChanges();
            Console.WriteLine($"Angajatul cu ID {emp.Id} ({emp.Email}) a fost sters soft.");
        }
        else
        {
            Console.WriteLine("Nu s-au gasit angajati activi.");
        }
    }

    static void ViewDeletedEmployees()
    {
        Console.WriteLine("\n--- VEDERE ADMIN: ANGAJATI STERSI ---");
        using var context = new AppDbContext();

        var deletedEmployees = context.Employees
                                      .IgnoreQueryFilters()
                                      .Where(e => e.IsDeleted)
                                      .ToList();

        if (!deletedEmployees.Any())
        {
            Console.WriteLine("Nu exista angajati stersi soft.");
            return;
        }

        foreach (var emp in deletedEmployees)
        {
            Console.WriteLine($"- ID: {emp.Id} | Email: {emp.Email} | Sters la: {emp.DeletedAt} de {emp.DeletedBy}");
        }
    }

    static void RestoreEmployee()
    {
        using var context = new AppDbContext();
        Console.Write("Introdu ID-ul angajatului pe care vrei sa il restaurezi: ");
        if (int.TryParse(Console.ReadLine(), out int id))
        {
            var emp = context.Employees
                             .IgnoreQueryFilters()
                             .FirstOrDefault(e => e.Id == id && e.IsDeleted);

            if (emp != null)
            {
                emp.IsDeleted = false;
                emp.DeletedAt = null;
                emp.DeletedBy = null;
                context.SaveChanges();
                Console.WriteLine($"Angajatul cu ID {id} a fost restaurat cu succes!");
            }
            else
            {
                Console.WriteLine("Nu a fost gasit niciun angajat sters cu acest ID.");
            }
        }
    }
}