package app.model;

import jakarta.persistence.*;

import java.util.ArrayList;
import java.util.List;

@jakarta.persistence.Entity
@Table(name = "SwimmingTests")
public class SwimmingTest extends Entity<Integer>{
    private int distance;
    private String style;
    @Transient
    private List<Participant> participants;

    public SwimmingTest() { }

    public SwimmingTest(Integer id, int distance, String style) {
        super(id);
        this.distance = distance;
        this.style = style;
        this.participants = new ArrayList<>();
    }

    public int getDistance() {
        return distance;
    }

    public String getStyle() {
        return style;
    }

    public List<Participant> getParticipants() {
        return participants;
    }

    public void addParticipant(Participant participant) {
        participants.add(participant);
    }
}
