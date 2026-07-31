using Domain;
using log4net;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public class ConfigRepository : IConfigRepository
    {
        private readonly AppDbContext _context;
        private static readonly ILog _logger = LogManager.GetLogger(typeof(ConfigRepository));

        public ConfigRepository(AppDbContext context)
        {
            _context = context;
            _logger.Info("Initializare ConfigRepository");
        }

        public void Save(Config entity)
        {
            _logger.Info($"Salvare configuratie cu ID: {entity.Id}");
            _context.Configs.Add(entity);
            _context.SaveChanges();
            _logger.Info($"Configuratie cu ID: {entity.Id} salvata cu succes");
        }

        public Config FindRandom()
        {
            _logger.Info("Cautare configuratie aleatoare");
            var config = _context.Configs.OrderBy(c => EF.Functions.Random()).FirstOrDefault();
            _logger.Info($"Configuratie aleatoare gasita: {config?.Id}");
            return config;
        }

        public void Update(Config entity)
        {
            throw new NotImplementedException();
        }

        public void Delete(int id)
        {
            throw new NotImplementedException();
        }
        
        public Config FindById(int id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Config> FindAll()
        {
            throw new NotImplementedException();
        }
    }
}
