package repository.memory;

import domain.card.Card;
import domain.duck.Duck;
import exceptions.RepositoryException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CardRepository {
    protected final Map<Long, Card<? extends Duck>> repo = new HashMap<>();

    /**
     * Saves a new card in the repository.
     *
     * @param card the card to save
     */
    public void save(Card<? extends Duck> card) {
        if (card == null)
            throw new RepositoryException("Card can not be null!");
        if (repo.containsValue(card))
            throw new RepositoryException("Card already exists!");
        repo.put(card.getId(), card);
    }

    /**
     * Deletes a card from the repository
     *
     * @param id the id of the card
     */
    public void delete(long id){
        repo.remove(id);
    }

    /**
     * Finds a card by its id.
     *
     * @param id the id of the card to find
     * @return the card with the given id
     */
    public Card<? extends Duck> findById(long id) {
        return repo.get(id);
    }

    /**
     * Returns a list of all card stored in the repository.
     *
     * @return a list containing all cards
     */
    public List<Card<? extends Duck>> findAll() {
        return new ArrayList<>(repo.values());
    }
}
