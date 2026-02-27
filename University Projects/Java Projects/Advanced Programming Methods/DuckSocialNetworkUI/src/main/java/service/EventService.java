package service;

import domain.*;
import domain.duck.SwimmingDuck;
import events.Event;
import events.RaceEvent;
import repository.database.DBEventRepository;
import repository.database.DBUserRepository;
import exceptions.ServiceException;
import utils.TipEvent;
import validators.EventValidator;
import validators.Validator;

import java.util.*;

public class EventService {
    private final DBUserRepository<Long, User> userRepo;
    private final DBEventRepository<Long, Event> eventsRepo;

    private final Validator<Event> eventValidator = new EventValidator();

    public EventService(DBUserRepository<Long, User> userRepo,  DBEventRepository<Long, Event> eventsRepo) {
        this.userRepo = userRepo;
        this.eventsRepo = eventsRepo;
    }

    /**
     * Returns a list of all swimming ducks in the network.
     *
     * @return list of all swimming ducks
     */
    private List<SwimmingDuck> getAllSwimmingDucks(){
        var users = userRepo.findAll();
        List<SwimmingDuck> swimmingDucks = new ArrayList<>();
        for (var user : users) {
            if (user instanceof SwimmingDuck) {
                swimmingDucks.add((SwimmingDuck) user);
            }
        }
        return swimmingDucks;
    }

    /**
     * Starts a new race event based on the problem 'Natatie'
     *
     * @param nrDucks number of ducks that participate in the event
     * @param distances at what distances are the buoys placed
     */
    public void addRaceEvent(Long id, String name, TipEvent type, int nrDucks, List<Long> distances){
        var ducks = getAllSwimmingDucks();
        if (ducks.size() < nrDucks) {
            throw new ServiceException("Not enough swimming ducks for the race!");
        }

        Collections.shuffle(ducks);
        List<SwimmingDuck> selected = ducks.subList(0, nrDucks);

        RaceEvent event = new RaceEvent(id, name, type, selected, distances);
        eventValidator.validate(event);
        eventsRepo.save(event);
    }

    public void deleteRaceEvent(Long id){
        if (eventsRepo.findById(id) == null)
            throw new ServiceException("Event not found!");
        eventsRepo.delete(id);
    }

    private void notifySubscribers(Long eventID){
        var ids = eventsRepo.getSubscriberIDsForAnEvent(eventID);
        for (var id : ids) {
            var subscriber = userRepo.findById(id);
            var event = eventsRepo.findById(eventID);
            subscriber.update(event);
        }
    }

    public void startRaceEvent(Long id){
        Event event = eventsRepo.findById(id);
        if (event == null)
            throw new ServiceException("Event not found!");
        if (event instanceof RaceEvent re) {
            re.startRace();
            notifySubscribers(id);
        }
    }

    public List<Event> listEvents(){
        return eventsRepo.findAll();
    }

    public void addSubscriber(Long eventID, Long userID){
        Event event = eventsRepo.findById(eventID);
        if (event == null)
            throw new ServiceException("Event not found!");
        User user = userRepo.findById(userID);
        if (user == null)
            throw new ServiceException("User not found!");
        eventsRepo.subscribeToEvent(eventID, userID);
    }

    public void deleteSubscriber(Long eventID, Long userID){
        Event event = eventsRepo.findById(eventID);
        if (event == null)
            throw new ServiceException("Event not found!");
        User user = userRepo.findById(userID);
        if (user == null)
            throw new ServiceException("User not found!");
       eventsRepo.unsubscribeFromEvent(eventID, userID);
    }
}