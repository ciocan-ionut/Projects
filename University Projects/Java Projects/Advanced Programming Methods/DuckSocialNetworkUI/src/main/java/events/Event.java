package events;

import domain.Entity;
import utils.TipEvent;

public class Event extends Entity<Long> {
    private final String name;
    private final TipEvent type;
    private int subscribers;

    public Event(Long id, String name, TipEvent type) {
        super(id);
        this.name = name;
        this.type = type;
    }

    public String getName() {
        return name;
    }

    public TipEvent getType() {
        return type;
    }

    public void setSubscribers(int subscribers) {
        this.subscribers = subscribers;
    }

    @Override
    public String toString() {
        return "Event id = " + super.getId() + ", name = " + name + ", type = " + type + ", subscribers = " + subscribers;
    }
}
