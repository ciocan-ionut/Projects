package domain;

import events.Event;

public interface Observer {
    void update(Event e);
}
