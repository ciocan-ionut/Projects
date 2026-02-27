package factory;

import domain.card.Card;
import domain.card.FlyingCard;
import domain.card.FlyingSwimmingCard;
import domain.card.SwimmingCard;
import utils.TipRata;

public class CardFactory {
    public static Card<?> createCard(Long id, String name, TipRata type){
        if (type == TipRata.FLYING)
            return new FlyingCard(id, name, type);
        if (type == TipRata.SWIMMING)
            return new SwimmingCard(id, name, type);
        if (type == TipRata.FLYING_AND_SWIMMING)
            return new FlyingSwimmingCard(id, name, type);
        return null;
    }
}
