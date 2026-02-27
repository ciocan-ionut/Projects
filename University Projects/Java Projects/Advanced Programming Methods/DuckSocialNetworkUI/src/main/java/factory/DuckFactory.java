package factory;

import domain.duck.Duck;
import domain.duck.FlyingDuck;
import domain.duck.FlyingSwimmingDuck;
import domain.duck.SwimmingDuck;
import utils.TipRata;

public class DuckFactory {
    public static Duck createDuck(Long id, String username, String email, String password,
                                  TipRata type, double speed, double resistance, Long cardID) {
        if (type == TipRata.FLYING)
            return new FlyingDuck(id, username, email, password, type, speed, resistance, cardID);
        if (type == TipRata.SWIMMING)
            return new SwimmingDuck(id, username, email, password, type, speed, resistance, cardID);
        if (type == TipRata.FLYING_AND_SWIMMING)
            return new FlyingSwimmingDuck(id, username, email, password, type, speed, resistance, cardID);
        return null;
    }
}
