using Domain;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public class AppDbContext : DbContext
    {
        public DbSet<Domain.User> Users { get; set; }
        public DbSet<Config> Configs { get; set; }
        public DbSet<Category> Categories { get; set; }
        public DbSet<Domain.Game> Games { get; set; }
        public DbSet<Domain.GameAction> GameActions { get; set; }

        private readonly string _connectionString;

        public AppDbContext(string connectionString)
        {
            _connectionString = connectionString;
            Database.EnsureCreated();
        }

        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
            Database.EnsureCreated();
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                optionsBuilder
                    .LogTo(Console.WriteLine, Microsoft.Extensions.Logging.LogLevel.Information)
                    .UseSqlite(_connectionString);
            }
        }
    }
}
