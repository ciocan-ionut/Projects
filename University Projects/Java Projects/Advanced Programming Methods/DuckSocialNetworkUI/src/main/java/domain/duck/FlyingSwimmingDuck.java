package domain.duck;

import utils.TipRata;

public class FlyingSwimmingDuck extends Duck implements Zburator, Inotator{
    public FlyingSwimmingDuck(long id, String username, String email, String password, TipRata type, double speed, double resistance, Long cardID) {
        super(id, username, email, password, type, speed, resistance, cardID);
    }

    @Override
    public String toString() {
        return super.toString() + "\nDuck is doing both!";
    }

    public void inoata(){
        System.out.println(getUsername() + " is swimming!");
    }

    public void zboara(){
        System.out.println(getUsername() + " is flying!");
    }
}
