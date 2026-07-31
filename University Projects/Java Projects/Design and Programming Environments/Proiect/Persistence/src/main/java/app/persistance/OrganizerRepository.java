package app.persistance;

import app.model.Organizer;

public interface OrganizerRepository extends Repository<Integer, Organizer> {
    Organizer findByUsernameAndPassword(String username, String password);
}
