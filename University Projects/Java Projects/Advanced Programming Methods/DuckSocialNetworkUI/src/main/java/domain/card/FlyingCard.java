package domain.card;

import domain.duck.FlyingDuck;
import utils.TipRata;

public class FlyingCard extends Card<FlyingDuck> {
    public FlyingCard(long id, String name, TipRata type) {
        super(id, name, type);
    }

    public boolean canAccept(TipRata duckType) {
        return duckType == getType();
    }
}
