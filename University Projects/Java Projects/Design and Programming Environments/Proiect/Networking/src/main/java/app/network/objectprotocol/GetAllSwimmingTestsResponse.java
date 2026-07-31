package app.network.objectprotocol;

import app.model.SwimmingTestDTO;

import java.util.List;

public class GetAllSwimmingTestsResponse implements Response {
    private final List<SwimmingTestDTO> swimmingTestDTOs;

    public GetAllSwimmingTestsResponse(List<SwimmingTestDTO> swimmingTestDTOs) {
        this.swimmingTestDTOs = swimmingTestDTOs;
    }

    public List<SwimmingTestDTO> getSwimmingTestDTOs() {
        return swimmingTestDTOs;
    }
}
