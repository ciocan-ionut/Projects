package repository;

import domain.Entity;

import java.util.List;

public interface Repository<ID, TElem extends Entity<ID>> {
    void save(TElem entity);
    TElem findById(ID id);
    Iterable<TElem> findAll();
    void delete(ID id);
}
