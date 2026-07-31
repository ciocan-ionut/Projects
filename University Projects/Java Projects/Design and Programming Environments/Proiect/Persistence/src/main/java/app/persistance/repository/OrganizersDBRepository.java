package app.persistance.repository;

import app.persistance.OrganizerRepository;

import app.model.Organizer;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.List;

public class OrganizersDBRepository implements OrganizerRepository {
    private final DBUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public OrganizersDBRepository(DBUtils dbUtils) {
        logger.info("Initializing OrganizersDBRepository with utils: {} ", dbUtils);
        this.dbUtils = dbUtils;
    }

    @Override
    public Organizer findByUsernameAndPassword(String username, String password) {
        logger.info("Validating username and password: {} {}", username, password);

        var con = dbUtils.getConnection();
        String query = "SELECT id FROM Organizers WHERE username = ? AND password = ?";
        try (var stmt = con.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            try (var result = stmt.executeQuery()) {
                if (result.next()) {
                    int id = result.getInt("id");
                    logger.info("Found organizer with ID: {}", id);
                    return new Organizer(id, username, password);
                } else {
                    logger.info("No organizer found with provided credentials");
                    return null;
                }
            }
        } catch (Exception e) {
            logger.error(e);
            System.out.println("Error DB " + e);
            return null;
        }
    }

    @Override
    public void save(Organizer entity) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public void delete(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public void update(Organizer entity) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public Organizer findById(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public List<Organizer> findAll() {
        throw new UnsupportedOperationException("Not implemented yet");
    }
}
