package domain.friendship;

import domain.Entity;

import java.util.Objects;

public class Friendship extends Entity<Long> {
    private final long userId1;
    private final long userId2;

    public Friendship(long id, long userId1, long userId2) {
        super(id);
        this.userId1 = userId1;
        this.userId2 = userId2;
    }

    public Long getId() {
        return super.getId();
    }

    public long getUserId1() {
        return userId1;
    }

    public long getUserId2() {
        return userId2;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return (userId1 == that.userId1 && userId2 == that.userId2) || (userId1 == that.userId2 && userId2 == that.userId1);
    }

    @Override
    public int hashCode() {
        return Objects.hash(Math.min(userId1, userId2), Math.max(userId1, userId2));
    }
}
