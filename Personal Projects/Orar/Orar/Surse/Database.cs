using SQLite;
using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Essentials;

namespace Orar
{
    public class Database
    {
        readonly SQLiteAsyncConnection _database;
        public Database(string dbPath)
        {
            _database = new SQLiteAsyncConnection(dbPath);
            _database.CreateTableAsync<Zi>().Wait();
        }
        public async Task<List<Zi>> GetZile()
        {
            return await _database.Table<Zi>().ToListAsync();
        }
        public async Task<int> UpdateZi(Zi zi)
        {
            return await _database.UpdateAsync(zi);
        }
        public async Task InitializeDatabase()
        {
            List<Zi> cnt = await GetZile();
            if (cnt.Count == 0)
            {
                var zile = new List<Zi>
                {
                    new Zi { Nume = "Luni"},
                    new Zi { Nume = "Marti"},
                    new Zi { Nume = "Miercuri"},
                    new Zi { Nume = "Joi"},
                    new Zi { Nume = "Vineri"}
                };
                foreach (var zi in zile)
                    await _database.InsertAsync(zi);
            }
        }

    }
}