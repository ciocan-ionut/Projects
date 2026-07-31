using Domain;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public interface IUserRepository : IRepository<int, Domain.User>
    {
        Domain.User FindByAlias(string alias);
        IEnumerable<UserDTO> FindAllWinners(int gameId);
    }
}
