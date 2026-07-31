using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;

namespace Domain
{
    [Table("Games")]
    public class Game : Entity<int>
    {
        public DateTime StartTime { get; set; }
        public int Players { get; set; }
        public bool IsFinished { get; set; }
    }
}
