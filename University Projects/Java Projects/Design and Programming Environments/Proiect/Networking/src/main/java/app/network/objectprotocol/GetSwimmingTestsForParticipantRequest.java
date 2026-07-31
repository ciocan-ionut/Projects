package app.network.objectprotocol;

public class GetSwimmingTestsForParticipantRequest implements Request {
    private final int participantId;

    public GetSwimmingTestsForParticipantRequest(int participantId) {
        this.participantId = participantId;
    }

    public int getParticipantId() {
        return participantId;
    }
}
