package validators;

import domain.card.Card;
import domain.duck.Duck;
import exceptions.ValidationException;

public class CardValidator implements Validator<Card<? extends Duck>> {
    public void validate(Card<? extends Duck> card)
    {
        if (card == null)
            throw new ValidationException("Null object!");
        if (card.getName() == null || card.getName().isBlank())
            throw new ValidationException("Name required!");
    }
}
