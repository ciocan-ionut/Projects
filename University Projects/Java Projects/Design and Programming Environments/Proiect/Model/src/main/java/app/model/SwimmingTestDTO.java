package app.model;

import java.io.Serializable;

public record SwimmingTestDTO(int id, int distance, String style, long participantCount) implements Serializable {
}
