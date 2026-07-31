package app.network.objectprotocol;

import app.model.SwimmingTest;

import java.util.List;

public class GetSwimmingTestsForParticipantResponse implements Response {
    private final List<SwimmingTest> swimmingTests;

    public GetSwimmingTestsForParticipantResponse(List<SwimmingTest> swimmingTests) {
        this.swimmingTests = swimmingTests;
    }

    public List<SwimmingTest> getSwimmingTests() {
        return swimmingTests;
    }
}
