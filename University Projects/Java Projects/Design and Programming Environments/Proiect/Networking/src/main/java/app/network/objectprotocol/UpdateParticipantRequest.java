package app.network.objectprotocol;

import app.model.ParticipantDTO;
import app.model.SwimmingTest;

import java.util.List;

public class UpdateParticipantRequest implements Request {
    private final ParticipantDTO participantDTO;
    private final List<SwimmingTest> tests;

    public UpdateParticipantRequest(ParticipantDTO participantDTO, List<SwimmingTest> tests) {
        this.participantDTO = participantDTO;
        this.tests = tests;
    }

    public ParticipantDTO getParticipantDTO() {
        return participantDTO;
    }
    public List<SwimmingTest> getTests() {
        return tests;
    }
}
