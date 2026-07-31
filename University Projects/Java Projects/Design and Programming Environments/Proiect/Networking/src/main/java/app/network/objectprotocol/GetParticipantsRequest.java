package app.network.objectprotocol;

public class GetParticipantsRequest implements Request {
    private final int swimmingTestId;

    public GetParticipantsRequest(int swimmingTestId) {
        this.swimmingTestId = swimmingTestId;
    }

    public int getSwimmingTestId() {
        return swimmingTestId;
    }
}
