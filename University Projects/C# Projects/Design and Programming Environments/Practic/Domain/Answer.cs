using System;
using System.Collections.Generic;
using System.Text;

namespace Domain
{
    public class Answer : Entity<int>
    {
        public string Text { get; set; }
        public int Points { get; set; }
    }
}
