package app.network.objectprotocol;

import app.model.ParticipantDTO;

import java.util.List;

public class GetParticipantsResponse implements Response {
    private final List<ParticipantDTO> participants;

    public GetParticipantsResponse(List<ParticipantDTO> participants) {
        this.participants = participants;
    }

    public List<ParticipantDTO> getParticipants() {
        return participants;
    }
}
