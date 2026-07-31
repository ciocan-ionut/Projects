using System;
using System.Collections.Generic;
using System.Text;

namespace model
{
    public class Organizer : Entity<int>
    {
        public string Username { get; }
        public string Password { get; }

        public Organizer(int id, string username, string password) : base(id)
        {
            Username = username;
            Password = password;
        }
    }
}
