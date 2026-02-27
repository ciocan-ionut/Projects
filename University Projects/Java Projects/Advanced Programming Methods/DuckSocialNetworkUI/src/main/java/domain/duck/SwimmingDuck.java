package domain.duck;

import utils.TipRata;

public class SwimmingDuck extends Duck implements Inotator{
    public SwimmingDuck(long id, String username, String email, String password, TipRata type, double speed, double resistance, Long cardID) {
        super(id, username, email, password, type, speed, resistance, cardID);
    }

    @Override
    public String toString() {
        return super.toString() + "\nDuck is swimming!";
    }

    public void inoata() {
        System.out.println(getUsername() + " is swimming!");
    }
}
