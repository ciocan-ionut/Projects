using Microsoft.EntityFrameworkCore;
using Practic;

using (var context = new AppDbContext())
{
    if (!context.Scoli.Any())
    {
        var scoala = new Scoala
        {
            Nume = "Liceul Teoretic \"Mihai Eminescu\"",
            Locatie = "București",
            AnInfiintare = 1950
        };
        context.Scoli.Add(scoala);
        context.SaveChanges();
    }
}

Task task1 = Task.Run(async () =>
{
    await Task.Delay(1000);

    using var context = new AppDbContext();
    using var transaction = context.Database.BeginTransaction();

    var scoala = new Scoala
    {
        Nume = "Colegiul National \"Mihai Viteazul\"",
        Locatie = "Turda",
        AnInfiintare = 1960
    };
    context.Scoli.Add(scoala);
    context.SaveChanges();

    transaction.Commit();
});

Task task2 = Task.Run(async () =>
{
    using var context = new AppDbContext();
    using var transaction = context.Database.BeginTransaction(System.Data.IsolationLevel.RepeatableRead);

    var scoli = context.Scoli.Where(s => s.AnInfiintare <= 1960).ToList();
    scoli.ForEach(s => Console.WriteLine($"Scoala: {s.Nume}, An Infiintare: {s.AnInfiintare}"));

    await Task.Delay(2000);

    scoli = context.Scoli.Where(s => s.AnInfiintare <= 1960).ToList();
    scoli.ForEach(s => Console.WriteLine($"Scoala: {s.Nume}, An Infiintare: {s.AnInfiintare}"));

    transaction.Rollback();
});

Task.WaitAll(task1, task2);
using (var context = new AppDbContext())
{
    var scoala = context.Scoli.FirstOrDefault(s => s.Nume == "Colegiul National \"Mihai Viteazul\"");
    if (scoala != null)
        context.Scoli.Remove(scoala);
    context.SaveChanges();
}