package domain.card;

import domain.duck.SwimmingDuck;
import utils.TipRata;

public class SwimmingCard extends Card<SwimmingDuck> {
    public SwimmingCard(long id, String name, TipRata type) {
        super(id, name, type);
    }

    public boolean canAccept(TipRata duckType) {
        return duckType == getType();
    }
}
