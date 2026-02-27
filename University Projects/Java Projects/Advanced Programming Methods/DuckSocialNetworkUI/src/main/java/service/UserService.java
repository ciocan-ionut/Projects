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
import domain.person.Persoana;
import exceptions.ServiceException;
import factory.DuckFactory;
import repository.database.DBCardRepository;
import repository.database.DBFriendshipRepository;
import repository.database.DBUserRepository;
import utils.GraphUtils;
import utils.TipRata;
import validators.DuckValidator;
import validators.PersonValidator;
import validators.Validator;

import java.time.LocalDate;
import java.util.*;

public class UserService {
    private final DBUserRepository<Long, User> userRepo;
    private final DBFriendshipRepository friendshipRepo;
    private final DBCardRepository<Long, Card<? extends Duck>> cardRepo;

    private final Validator<Persoana> personValidator = new PersonValidator();
    private final Validator<Duck> duckValidator = new DuckValidator();

    public UserService(DBUserRepository<Long, User> userRepo, DBFriendshipRepository friendshipRepo, DBCardRepository<Long, Card<? extends Duck>> cardRepo) {
        this.userRepo = userRepo;
        this.friendshipRepo = friendshipRepo;
        this.cardRepo = cardRepo;
    }

    /**
     * Adds a new person to the network.
     *
     * @param id the unique id of the person
     * @param username the username of the person
     * @param email the email of the person
     * @param password the password of the person
     * @param nume last name
     * @param prenume first name
     * @param dataNasterii birthdate
     * @param ocupatie occupation
     * @param nivelEmpatie empathy level
     * @throws ServiceException if the user already exists or validation fails
     */
    public void addPerson(Long id, String username, String email, String password,
                          String nume, String prenume, LocalDate dataNasterii,
                          String ocupatie, double nivelEmpatie) {
        Persoana p = new Persoana(id, username, email, password, nume, prenume, ocupatie, dataNasterii, nivelEmpatie);
        personValidator.validate(p);
        userRepo.save(p);
    }

    /**
     * Adds a new duck to the network.
     *
     * @param id the unique id of the duck
     * @param username the username of the duck
     * @param email the email of the duck
     * @param password the password of the duck
     * @param tip the type of the duck
     * @param viteza speed of the duck
     * @param rezistenta endurance of the duck
     * @throws ServiceException if the user already exists or validation fails
     */
    public void addDuck(Long id, String username, String email, String password,
                        utils.TipRata tip, double viteza, double rezistenta, Long cardId) {
        Card<? extends Duck> card = cardRepo.findById(cardId);
        if (card == null)
            throw new ServiceException("Card not found");

        if (!card.canAccept(tip))
            throw new ServiceException("Duck does not match card type!");

        Duck d = DuckFactory.createDuck(id, username, email, password, tip, viteza, rezistenta, cardId);
        duckValidator.validate(d);
        userRepo.save(d);

        if (tip == TipRata.FLYING)
            ((FlyingCard) card).addDuck((FlyingDuck) d);
        else if (tip == TipRata.SWIMMING)
            ((SwimmingCard) card).addDuck((SwimmingDuck) d);
        else
            ((FlyingSwimmingCard) card).addDuck((FlyingSwimmingDuck) d);
    }

    /**
     * Updates the data of a person from the network. Empty arguments mean the old data will be kept
     *
     * @param id the unique id of the person
     * @param password the password of the person
     * @param ocupatie occupation
     * @param nivelEmpatie empathy level
     * @throws ServiceException if the user doesn't exist
     */
    public void updatePerson(Long id, String password, String ocupatie, double nivelEmpatie) {
        User u = userRepo.findById(id);
        if (u == null)
            throw new ServiceException("User not found");

        Persoana p = (Persoana) u;
        if (password != null && !password.isBlank())
            p.setPassword(password);
        if (ocupatie != null && !ocupatie.isBlank())
            p.setJob(ocupatie);
        if (nivelEmpatie >= 0 && nivelEmpatie <= 10)
            p.setEmpathy(nivelEmpatie);
        userRepo.update(p);
    }

    /**
     * Updates the data of a duck from the network. Empty arguments mean the old data will be kept
     *
     * @param id the unique id of the duck
     * @param password the password of the duck
     * @param viteza speed of the duck
     * @param rezistenta endurance of the duck
     * @throws ServiceException if the user or card doesn't exist
     */
    public void updateDuck(Long id, String password, double viteza, double rezistenta, Long cardId) {
        User u = userRepo.findById(id);
        if (u == null)
            throw new ServiceException("User not found");
        Duck d = (Duck) u;

        if (cardId != -1) {
            Card<? extends Duck> newCard = cardRepo.findById(cardId);
            if (newCard == null)
                throw new ServiceException("Card not found");
            if (newCard.getType() == d.getType()) {
                Card<? extends Duck> card = cardRepo.findById(d.getCard());
                if (d.getType() == TipRata.FLYING){
                    ((FlyingCard) card).removeDuck((FlyingDuck) d);
                    ((FlyingCard) newCard).addDuck((FlyingDuck) d);
                }
                else if (d.getType() == TipRata.SWIMMING){
                    ((SwimmingCard) card).removeDuck((SwimmingDuck) d);
                    ((SwimmingCard) newCard).addDuck((SwimmingDuck) d);
                }
                else{
                    ((FlyingSwimmingCard) card).removeDuck((FlyingSwimmingDuck) d);
                    ((FlyingSwimmingCard) newCard).addDuck((FlyingSwimmingDuck) d);
                }
                d.setCardID(cardId);
            }
        }
        if (password != null && !password.isBlank())
            d.setPassword(password);
        if (viteza > 0)
            d.setSpeed(viteza);
        if (rezistenta > 0)
            d.setResistance(rezistenta);
        userRepo.update(d);
    }

    /**
     * Removes a user from the network, along with all their friendships.
     *
     * @param id the id of the user to remove
     * @throws ServiceException if the user is not found
     */
    public void removeUser(Long id) {
        if (userRepo.findById(id) == null)
            throw new ServiceException("User not found");
        userRepo.delete(id);
    }

    /**
     * Returns a list of all users in the network.
     *
     * @return list of all users
     */
    public List<User> listUsers() {
        return userRepo.findAll();
    }

    /**
     * Finds a user by ID.
     *
     * @param id the ID of the user
     * @return the user if found, or null otherwise
     */
    public User findUserById(Long id) {
        return userRepo.findById(id);
    }

    /**
     * Adds a friendship between two users.
     *
     * @param id1 the id of the first user
     * @param id2 the id of the second user
     * @throws ServiceException if users are the same, do not exist, or already friends
     */
    public void addFriend(Long id1, Long id2) {
        if (Objects.equals(id1, id2))
            throw new ServiceException("Cannot friend the same user");
        if (userRepo.findById(id1) == null || userRepo.findById(id2) == null)
            throw new ServiceException("One of the users does not exist");
        friendshipRepo.save(id1, id2);
    }

    /**
     * Removes the friendship between two users.
     *
     * @param id1 the id of the first user
     * @param id2 the id of the second user
     * @throws ServiceException if the friendship does not exist
     */
    public void removeFriend(Long id1, Long id2) {
        if (!friendshipRepo.checkIfTheyAreFriends(id1, id2))
            throw new ServiceException("Friendship does not exist");
        friendshipRepo.delete(id1, id2);
    }

    /**
     * Returns a map of all friendships in the network
     *
     * @return map of all friendships
     */
    public Map<Long, List<Long>> listFriendships() {
        return friendshipRepo.buildAdjacency();
    }

    /**
     * Returns a list of user IDs which are friends with the user ID given as argument
     *
     * @param id the ID of the user
     * @return list of user IDs which are friends with the given user
     */
    public List<Long> getFriendsIds(Long id){
        return friendshipRepo.getFriendsIds(id);
    }

    /**
     * Returns the number of connected communities in the network.
     *
     * @return the number of communities
     * @throws ServiceException if no friendships exist
     */
    public int numberOfCommunities() {
        Map<Long, List<Long>> adj = friendshipRepo.buildAdjacency();
        Set<Long> visited = new HashSet<>();
        int count = 0;
        for (Long id : adj.keySet()) {
            if (!visited.contains(id)) {
                count++;
                GraphUtils.dfs(id, adj, visited);
            }
        }
        return count;
    }

    /**
     * Finds the most sociable community based on the largest diameter.
     *
     * @return a Map.Entry where the key is the list of user IDs in the community
     *         and the value is the diameter of the community
     * @throws ServiceException if no friendships exist
     */
    public Map.Entry<List<Long>, Integer> mostSociableCommunity() {
        Map<Long, List<Long>> adj = friendshipRepo.buildAdjacency();
        Set<Long> visited = new HashSet<>();
        List<Long> bestComponent = new ArrayList<>();
        int bestDiameter = -1;
        for (Long id : adj.keySet()) {
            if (!visited.contains(id)) {
                List<Long> comp = new ArrayList<>();
                GraphUtils.collectComponent(id, adj, comp, visited);
                int diam = GraphUtils.computeDiameter(comp, adj);
                if (diam > bestDiameter) {
                    bestDiameter = diam;
                    bestComponent = comp;
                }
            }
        }
        return Map.entry(bestComponent, Math.max(bestDiameter, 0));
    }
}
