using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Practic
{
    public class Scoala
    {
        [Key]
        public int Id { get; set; }

        [Required]
        [MaxLength(100)]
        public string Nume { get; set; } = string.Empty;

        [Required]
        [MaxLength(100)]
        public string Locatie { get; set; } = string.Empty;

        [Required]
        public int AnInfiintare { get; set; }
    }
}
