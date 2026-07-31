using Domain;
using System;
using System.Collections.Generic;
using System.Text;

namespace Persistence
{
    public interface ICategoryRepository : IRepository<int, Category>
    {
        IEnumerable<Category> FindRandom(int count);
        Category FindByName(string name);
        void AddNewAnswer(int categoryId, Answer answer);
    }
}
