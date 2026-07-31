using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Lab_5
{
    public class Department
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public ICollection<Employee> Employees { get; set; }
    }

    public class Employee
    {
        public int Id { get; set; }
        public string Email { get; set; }
        public decimal Salary { get; set; }
        public int DepartmentId { get; set; }

        // Sarcina B
        public string? Phone { get; set; }

        public Department Department { get; set; }

        [ConcurrencyCheck]
        public int Version { get; set; }

        public bool IsDeleted { get; set; }
        public DateTime? DeletedAt { get; set; }
        public string? DeletedBy { get; set; }
    }

    // Sarcina C
    public class Project
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public DateTime? StartDate { get; set; }

        public int DepartmentId { get; set; }
        public Department Department { get; set; }
    }
}
