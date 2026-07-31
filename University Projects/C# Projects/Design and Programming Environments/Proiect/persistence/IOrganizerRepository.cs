using model;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public interface IOrganizerRepository : IRepository<int, Organizer>
    {
        Organizer FindByUsernameAndPassword(string username, string password);
    }
}
