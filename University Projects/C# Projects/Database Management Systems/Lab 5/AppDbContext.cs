using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace Lab_5
{
    public class AppDbContext : DbContext
    {
        public DbSet<Department> Departments { get; set; }
        public DbSet<Employee> Employees { get; set; }

        public DbSet<Project> Projects { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseNpgsql("Host=localhost;Database=SGBD;Username=postgres;Password=1234");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Sarcina D
            modelBuilder.Entity<Employee>()
                .Property(e => e.Salary)
                .HasColumnType("numeric(12,2)");

            // Sarcina E
            modelBuilder.Entity<Employee>()
                .HasIndex(e => e.DepartmentId)
                .HasDatabaseName("idx_employees_department");

            modelBuilder.Entity<Employee>()
                .HasIndex(e => e.Email)
                .HasDatabaseName("idx_employees_email");

            modelBuilder.Entity<Employee>()
                .HasQueryFilter(e => !e.IsDeleted);
        }

        public override int SaveChanges()
        {
            foreach (var entry in ChangeTracker.Entries<Employee>())
            {
                switch (entry.State)
                {
                    case EntityState.Deleted:
                        entry.State = EntityState.Modified;
                        entry.Entity.IsDeleted = true;
                        entry.Entity.DeletedAt = DateTime.UtcNow;
                        entry.Entity.DeletedBy = Environment.UserName;
                        break;
                    case EntityState.Modified:
                        entry.Entity.Version++;
                        break;
                }
            }
            return base.SaveChanges();
        }
    }
}
