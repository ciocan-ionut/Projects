using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public interface IGameRepository : IRepository<int, Domain.Game>
    {
        IEnumerable<Domain.Game> FindAllByUser(int userId);
    }
}
