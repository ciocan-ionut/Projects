package domain.duck;

import utils.TipRata;

public class FlyingDuck extends Duck implements Zburator{
    public FlyingDuck(long id, String username, String email, String password, TipRata type, double speed, double resistance, Long cardID) {
        super(id, username, email, password, type, speed, resistance, cardID);
    }

    @Override
    public String toString() {
        return super.toString() + "\nDuck is flying!";
    }

    public void zboara() {
        System.out.println(getUsername() + " is flying!");
    }
}
