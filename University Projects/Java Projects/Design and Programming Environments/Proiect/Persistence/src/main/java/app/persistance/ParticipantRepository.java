package app.persistance;

import app.model.Participant;
import app.model.ParticipantDTO;

import java.util.List;

public interface ParticipantRepository extends Repository<Integer, Participant> {
    List<ParticipantDTO> findParticipantDTOsBySwimmingTestId(Integer swimmingTestId);
}
