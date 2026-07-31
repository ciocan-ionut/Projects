using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;

namespace Domain
{
    [Table("Users")]
    public class User : Entity<int>
    {
        [Required]
        [MaxLength(50)]
        public string Alias { get; set; }

        [Required]
        public int Age { get; set; }
    }
}
