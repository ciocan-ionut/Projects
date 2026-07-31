using System;
using System.Collections.Generic;
using System.Text;

namespace model
{
    public class Entity<ID>
    {
        public ID Id { get; set; }
        public Entity(ID id)
        {
            Id = id;
        }
    }
}
