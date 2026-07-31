using System;
using System.Collections.Generic;
using System.Text;

namespace Domain
{
    public class GameAction : Entity<int>
    {
        public int GameId {  get; set; }
        public int UserId { get; set; }

        public string ActionData { get; set; }

        public int PointsAwarded { get; set; }
        public DateTime Timestamp { get; set; }

        public virtual Game Game { get; set; }
        public virtual User User { get; set; }
    }
}