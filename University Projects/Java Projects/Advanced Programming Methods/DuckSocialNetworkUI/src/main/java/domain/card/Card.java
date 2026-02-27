package domain.card;

import domain.Entity;
import domain.duck.Duck;
import utils.TipRata;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public abstract class Card<TElem extends Duck> extends Entity<Long> {
    private final String name;
    private final TipRata type;
    private final List<TElem> members;

    public Card(long id, String name, TipRata type) {
        super(id);
        this.name = name;
        this.type = type;
        members = new ArrayList<>();
    }

    public Long getId() {
        return super.getId();
    }

    public String getName() {
        return name;
    }

    public TipRata getType() {
        return type;
    }

    public List<TElem> getMembers() {
        return members;
    }

    public abstract boolean canAccept(TipRata tipRata);

    public void addDuck(TElem duck) {
        if (!members.contains(duck)) {
            members.add(duck);
        }
    }

    public void removeDuck(TElem duck) {
        members.remove(duck);
    }

    public double getAverageSpeed() {
        double medieV = 0;
        for (Duck duck : members)
            medieV += duck.getSpeed();
        return medieV / members.size();
    }

    public double getAverageResistance() {
        double medieR = 0;
        for (Duck duck : members)
            medieR += duck.getResistance();
        return medieR / members.size();
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Card<?> card = (Card<?>) o;
        return Objects.equals(super.getId(), card.getId()) || Objects.equals(name, card.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.getId(), name, members);
    }

    @Override
    public String toString() {
        return "Card: " + "id = " + super.getId() + ", numeCard = " + name + ", membri = " + members.size() +
                "\nViteza medie = " + getAverageSpeed() + ", rezistenta medie = " + getAverageResistance();
    }
}
