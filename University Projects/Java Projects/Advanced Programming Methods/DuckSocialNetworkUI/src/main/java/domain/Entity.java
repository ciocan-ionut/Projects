package domain;

public class Entity<ID> {
    private final ID id;

    public Entity(ID id) {
        this.id = id;
    }

    public ID getId() {
        return id;
    }
}
