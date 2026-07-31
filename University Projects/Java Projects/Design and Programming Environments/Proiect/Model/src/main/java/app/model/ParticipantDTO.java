package app.model;

import java.io.Serializable;

public record ParticipantDTO(int id, String name, int age, long swimmingTestCount) implements Serializable {
}
