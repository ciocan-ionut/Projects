using Domain;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public interface IConfigRepository : IRepository<int, Config>
    {
        Config FindRandom();
    }
}
