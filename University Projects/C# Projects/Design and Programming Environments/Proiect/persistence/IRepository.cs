using model;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public interface IRepository<ID, T> where T : Entity<ID>
    {
        void Save(T entity);
        void Delete(ID id);
        void Update(T entity);
        T FindById(ID id);
        List<T> FindAll();
    }
}
