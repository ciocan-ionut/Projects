using System;
using System.Collections.Generic;
using System.Text;

namespace Domain
{
    public class Category : Entity<int>
    {
        public string Name { get; set; }
        public ICollection<Answer> Answers { get; set; } = new List<Answer>();
    }
}
