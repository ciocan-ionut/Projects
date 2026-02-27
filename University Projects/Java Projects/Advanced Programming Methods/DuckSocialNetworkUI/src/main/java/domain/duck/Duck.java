package domain.duck;

import domain.User;
import utils.TipRata;

public abstract class Duck extends User {
    private final TipRata type;
    private double speed;
    private double resistance;
    private Long cardID;


    @Override
    public String toString() {
        return super.toString() + "\nDuck: tip = " + type + ", viteza = " + speed + ", rezistenta = " + resistance + ", card = " + cardID;
    }

    public Duck(long id, String username, String email, String password,
                TipRata type, double speed, double resistance, Long cardID) {
        super(id, username, email, password);
        this.type = type;
        this.speed = speed;
        this.resistance = resistance;
        this.cardID = cardID;
    }

    public TipRata getType() {
        return type;
    }

    public double getSpeed() {
        return speed;
    }

    public double getResistance() {
        return resistance;
    }

    public Long getCard() {
        return cardID;
    }

    public void setSpeed(double speed) {
        this.speed = speed;
    }

    public void setResistance(double resistance) {
        this.resistance = resistance;
    }

    public void setCardID(Long cardID) {
        this.cardID = cardID;
    }
}
