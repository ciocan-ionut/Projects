package app.services;

import java.util.List;
import app.model.Participant;
import app.model.ParticipantDTO;
import app.model.SwimmingTest;
import app.model.SwimmingTestDTO;

public interface IService {
    void login(String username, String password, IObserver client) throws AppException;
    void logout(String username, IObserver client) throws AppException;

    List<SwimmingTestDTO> getAllSwimmingTestDTOs() throws AppException;
    List<SwimmingTest> getSwimmingTestsForParticipant(Integer participantId) throws AppException;
    List<ParticipantDTO> getAllParticipantDTOs(int swimmingTestId) throws AppException;

    void addParticipant(String name, int age, List<SwimmingTest> swimmingTests) throws AppException;
    void updateParticipant(ParticipantDTO participantDTO, List<SwimmingTest> swimmingTests) throws AppException;
}
