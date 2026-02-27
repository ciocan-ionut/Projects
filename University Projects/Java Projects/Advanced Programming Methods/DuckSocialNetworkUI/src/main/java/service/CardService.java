package service;

import domain.User;
import domain.card.Card;
import domain.card.FlyingCard;
import domain.card.FlyingSwimmingCard;
import domain.card.SwimmingCard;
import domain.duck.Duck;
import domain.duck.FlyingDuck;
import domain.duck.FlyingSwimmingDuck;
import domain.duck.SwimmingDuck;
import exceptions.ServiceException;
import factory.CardFactory;
import repository.database.DBCardRepository;
import repository.database.DBUserRepository;
import utils.TipRata;
import validators.CardValidator;
import validators.Validator;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class CardService {
    private final DBUserRepository<Long, User> userRepo;
    private final DBCardRepository<Long, Card<? extends Duck>> cardRepo;

    private final Validator<Card<? extends Duck>> cardValidator = new CardValidator();

    public CardService(DBUserRepository<Long, User> userRepo, DBCardRepository<Long, Card<? extends Duck>> cardRepo) {
        this.userRepo = userRepo;
        this.cardRepo = cardRepo;
    }

    /**
     * Adds a new card to the network.
     *
     * @param id the unique id of the card
     * @param name the name of the card
     * @param tip the type of the card
     */
    public void addCard(long id, String name, TipRata tip){
        Card<?> card = CardFactory.createCard(id, name, tip);
        cardValidator.validate(card);
        cardRepo.save(card);
    }

    /**
     * Removes a card from the network
     *
     * @param id the unique id of the card
     */
    public void deleteCard(long id) {
        if (cardRepo.findById(id) == null)
            throw new ServiceException("Card not found");
        cardRepo.delete(id);
    }

    /**
     * Returns a list of all cards in the network
     *
     * @return list of all cards
     */
    public List<Card<?>> listCards() {
        Map<Long, Card<?>> cards = cardRepo.findAll().stream()
                .collect(Collectors.toMap(Card::getId, c -> c));

        for (var u : userRepo.findAll()) {
            if (u instanceof Duck duck) {
                Card<?> card = cards.get(duck.getCard());
                if (card == null)
                    continue;

                switch (duck.getType()) {
                    case FLYING ->
                            ((FlyingCard) card).addDuck((FlyingDuck) duck);
                    case SWIMMING ->
                            ((SwimmingCard) card).addDuck((SwimmingDuck) duck);
                    case FLYING_AND_SWIMMING ->
                            ((FlyingSwimmingCard) card).addDuck((FlyingSwimmingDuck) duck);
                }
            }
        }

        return new ArrayList<>(cards.values());
    }
}
