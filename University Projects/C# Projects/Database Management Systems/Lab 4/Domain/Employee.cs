using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;

namespace Lab_4.Domain
{
    public class Employee
    {
        [Key]
        public long Id { get; set; }

        [Required]
        [MaxLength(150)]
        public string Email { get; set; }

        [Column(TypeName = "decimal(18,2)")]
        public decimal Salary { get; set; }

        public int DepartmentId { get; set; }

        [ForeignKey(nameof(DepartmentId))]
        public virtual Department Department { get; set; }
    }
}
