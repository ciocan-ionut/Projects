using Domain;
using log4net;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public class CategoryRepository : ICategoryRepository
    {
        private readonly AppDbContext _context;
        private static readonly ILog _logger = LogManager.GetLogger(typeof(CategoryRepository));

        public CategoryRepository(AppDbContext context)
        {
            _context = context;
            _logger.Info("Initializare CategoryRepository");
        }

        public IEnumerable<Category> FindRandom(int count)
        {
            _logger.Info($"Cautare {count} categorii random");
            var categories = _context.Categories.OrderBy(c => EF.Functions.Random()).Take(count).ToList();
            _logger.Info($"S-au gasit {categories.Count} categorii random");
            return categories;
        }

        public void Save(Category entity)
        {
            _logger.Info($"Salvare categorie cu ID: {entity.Id}");
            _context.Categories.Add(entity);
            _context.SaveChanges();
            _logger.Info($"Categorie cu ID: {entity.Id} salvata cu succes");
        }

        public void Update(Category entity)
        {
            throw new NotImplementedException();
        }

        public void Delete(int id)
        {
            throw new NotImplementedException();
        }

        public Category FindById(int id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Category> FindAll()
        {
            throw new NotImplementedException();
        }

        public Category FindByName(string name)
        {
            _logger.Info($"Cautare categorie cu numele: {name}");
            var category = _context.Categories.FirstOrDefault(c => c.Name == name);
            _logger.Info(category != null ? $"Categorie gasita: {category.Name}" : "Categoria nu a fost gasita");
            return category;
        }

        public void AddNewAnswer(int categoryId, Answer answer)
        {
            _logger.Info($"Adaugare raspuns nou la categoria cu ID: {categoryId}");
            var category = _context.Categories.Include(c => c.Answers).FirstOrDefault(c => c.Id == categoryId);
            if (category != null)
            {
                category.Answers.Add(answer);
                _context.SaveChanges();
                _logger.Info($"Raspuns adaugat cu succes la categoria cu ID: {categoryId}");
            }
        }
    }
}
