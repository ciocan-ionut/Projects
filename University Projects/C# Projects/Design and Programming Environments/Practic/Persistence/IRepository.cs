namespace Persistence
{
    public interface IRepository<TId, TEntity> where TEntity : Domain.Entity<TId>
    {
        TEntity FindById(TId id);
        IEnumerable<TEntity> FindAll();
        void Save(TEntity entity);
        void Update(TEntity entity);
        void Delete(TId id);
    }
}
