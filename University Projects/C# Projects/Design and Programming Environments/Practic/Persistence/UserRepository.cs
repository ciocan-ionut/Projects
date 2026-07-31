using Domain;
using log4net;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public class UserRepository : IUserRepository
    {
        private readonly AppDbContext _context;
        private static readonly ILog _logger = LogManager.GetLogger(typeof(UserRepository));

        public UserRepository(AppDbContext context)
        {
            _context = context;
            _logger.Info("Initializare UserRepository");
        }

        public Domain.User FindById(int id)
        {
            _logger.Info($"Cautare utilizator cu ID: {id}");
            return _context.Users.FirstOrDefault(u => u.Id == id);
        }

        public Domain.User FindByAlias(string alias)
        {
            _logger.Info($"Cautare utilizator cu alias: {alias}");
            return _context.Users.FirstOrDefault(u => u.Alias == alias);
        }

        public IEnumerable<Domain.User> FindAll()
        {
            _logger.Info("Cautare toti utilizatorii");
            return _context.Users.ToList();
        }

        public void Save(Domain.User entity)
        {
            _logger.Info($"Salvare utilizator cu ID: {entity.Id}");
            _context.Users.Add(entity);
            _context.SaveChanges();
            _logger.Info($"Utilizator cu ID: {entity.Id} salvat cu succes");
        }

        public void Update(Domain.User entity)
        {
            _logger.Info($"Actualizare utilizator cu ID: {entity.Id}");
            _context.Users.Update(entity);
            _context.SaveChanges();
            _logger.Info($"Utilizator cu ID: {entity.Id} actualizat cu succes");
        }

        public void Delete(int id)
        {
            _logger.Info($"Stergere utilizator cu ID: {id}");
            _context.Users.Remove(FindById(id));
            _context.SaveChanges();
            _logger.Info($"Utilizator cu ID: {id} sters cu succes");
        }

        public IEnumerable<UserDTO> FindAllWinners(int gameId)
        {
            _logger.Info($"Cautare toti castigatorii pentru jocul cu ID: {gameId}");
            var game = _context.Games.FirstOrDefault(g => g.Id == gameId);

            var winners = _context.GameActions
                .Where(ga => ga.GameId == gameId && ga.PointsAwarded > 0)
                .GroupBy(ga => ga.UserId)
                .Where(g => g.Count() >= game.Players / 2)
                .Select(ga => new UserDTO
                {
                    Username = _context.Users.FirstOrDefault(u => u.Id == ga.Key).Alias,
                    ActionData = string.Join(", ", ga.Select(a => a.ActionData)),
                    PointsAwarded = string.Join(", ", ga.Select(a => a.PointsAwarded))
                })
                .ToList();
            return winners;
        }
    }
}
