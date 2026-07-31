using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Formula_1_SGBD.Domain
{
    [Table("Teams")]
    public class Team
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }

        [MaxLength(100)]
        public string Name { get; set; }

        public double Budget { get; set; }

        [MaxLength(100)]
        public string Location { get; set; }

        public virtual ICollection<Driver> Drivers { get; set; } = new List<Driver>();
    }
}
