package app.persistance;

import app.model.Entity;

import java.util.List;

public interface Repository<ID, T extends Entity<ID>> {
    void save(T entity);
    void delete(ID id);
    void update(T entity);
    T findById(ID id);
    List<T> findAll();
}
