using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Formula_1_SGBD.Domain
{
    [Table("Drivers")]
    public class Driver
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }

        [MaxLength(100)]
        public string Name { get; set; }
        public int Salary { get; set; }
        public DateTime ContractExpDate { get; set; }

        [ForeignKey("Team")]
        public int TeamID { get; set; }

        public virtual Team Team { get; set; }

        public Driver() { }

        public Driver(int ID, string name, int salary, DateTime contractExpDate, int teamID)
        {
            this.ID = ID;
            Name = name;
            Salary = salary;
            ContractExpDate = contractExpDate;
            TeamID = teamID;
        }
    }
}
