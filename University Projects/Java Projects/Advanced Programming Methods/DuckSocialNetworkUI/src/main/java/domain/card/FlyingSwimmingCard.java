package domain.card;

import domain.duck.FlyingSwimmingDuck;
import utils.TipRata;

public class FlyingSwimmingCard extends Card<FlyingSwimmingDuck> {
    public FlyingSwimmingCard(long id, String name, TipRata type) {
        super(id, name, type);
    }

    public boolean canAccept(TipRata duckType) {
        return duckType == getType();
    }
}
