package app.server;

import app.model.*;
import app.persistance.OrganizerRepository;
import app.persistance.ParticipantRepository;
import app.persistance.SwimmingTestRepository;
import app.services.AppException;
import app.services.IObserver;
import app.services.IService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Service implements IService {
    private final OrganizerRepository organizerRepository;
    private final ParticipantRepository participantRepository;
    private final SwimmingTestRepository swimmingTestRepository;

    private Map<String, IObserver> loggedClients;

    private static final Logger logger = LogManager.getLogger(Service.class);

    public Service(OrganizerRepository organizerRepository, ParticipantRepository participantRepository, SwimmingTestRepository swimmingTestRepository) {
        this.organizerRepository = organizerRepository;
        this.participantRepository = participantRepository;
        this.swimmingTestRepository = swimmingTestRepository;
        this.loggedClients = new ConcurrentHashMap<>();
    }

    @Override
    public synchronized void login(String username, String password, IObserver client) throws AppException {
        Organizer org = organizerRepository.findByUsernameAndPassword(username, password);
        if (org != null) {
            if (loggedClients.containsKey(username)) {
                throw new AppException("User already logged in");
            }
            loggedClients.put(username, client);
        } else {
            throw new AppException("Authentication failed");
        }
    }

    @Override
    public synchronized void logout(String username, IObserver client) throws AppException {
        IObserver loggedClient = loggedClients.remove(username);
        if (loggedClient == null) {
            throw new AppException("User not found");
        }
    }

    @Override
    public List<SwimmingTestDTO> getAllSwimmingTestDTOs() {
        return swimmingTestRepository.findAllDTOs();
    }

    @Override
    public List<SwimmingTest> getSwimmingTestsForParticipant(Integer participantId) {
        return swimmingTestRepository.findSwimmingTestsByParticipantId(participantId);
    }

    @Override
    public List<ParticipantDTO> getAllParticipantDTOs(int swimmingTestId) {
        return participantRepository.findParticipantDTOsBySwimmingTestId(swimmingTestId);
    }

    @Override
    public void addParticipant(String name, int age, List<SwimmingTest> swimmingTests) throws AppException {
        Participant participant = new Participant(null, name, age);
        participant.setSwimmingTests(swimmingTests);
        participantRepository.save(participant);
        notifyAllLoggedClients();
    }

    @Override
    public void updateParticipant(ParticipantDTO participantDTO, List<SwimmingTest> swimmingTests) throws AppException {
        Participant participant = new Participant(participantDTO.id(), participantDTO.name(), participantDTO.age());
        participant.setSwimmingTests(swimmingTests);
        participantRepository.update(participant);
        notifyAllLoggedClients();
    }

    private void notifyAllLoggedClients() {
        ExecutorService executorService = Executors.newFixedThreadPool(5);
        logger.debug("Notifying {} clients",  loggedClients.size());

        for (IObserver loggedClient : loggedClients.values()) {
            executorService.execute(() -> {
                try {
                    loggedClient.update();
                } catch (AppException e) {
                    logger.error("Error while notifying logged clients", e);
                }
            });
        }

        executorService.shutdown();
    }
}
