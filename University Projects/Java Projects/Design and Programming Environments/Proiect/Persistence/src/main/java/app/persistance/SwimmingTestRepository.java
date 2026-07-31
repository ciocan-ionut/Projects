package app.persistance;

import app.model.SwimmingTest;
import app.model.SwimmingTestDTO;

import java.util.List;

public interface SwimmingTestRepository extends Repository<Integer, SwimmingTest> {
    List<SwimmingTest> findSwimmingTestsByParticipantId(Integer participantId);
    List<SwimmingTestDTO> findAllDTOs();

    List<SwimmingTest> findByStyle(String style);
}
