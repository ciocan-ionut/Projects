package app.persistance.repository;

import app.model.Participant;
import app.model.ParticipantDTO;
import app.model.SwimmingTest;

import app.persistance.ParticipantRepository;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class ParticipantsDBRepository implements ParticipantRepository {
    private final DBUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public ParticipantsDBRepository(DBUtils dbUtils) {
        logger.info("Initializing ParticipantsDBRepository with utils: {} ", dbUtils);
        this.dbUtils = dbUtils;
    }

    @Override
    public List<ParticipantDTO> findParticipantDTOsBySwimmingTestId(Integer swimmingTestId) {
        logger.info("Finding participant DTOs for swimming test ID: {}", swimmingTestId);
        List<ParticipantDTO> dtos = new ArrayList<>();

        String query = "SELECT P.*, COUNT(R2.swimmingtest_id) AS test_count " +
                       "FROM Participants P " +
                       "INNER JOIN Registrations R1 ON P.id = R1.participant_id " +
                       "INNER JOIN Registrations R2 ON P.id = R2.participant_id " +
                       "WHERE R1.swimmingtest_id = ? " +
                       "GROUP BY P.id, P.name, P.age";

        var con = dbUtils.getConnection();
        try (var stmt = con.prepareStatement(query)) {

            stmt.setInt(1, swimmingTestId);

            try (var result = stmt.executeQuery()) {
                while (result.next()) {
                    int id = result.getInt("id");
                    String name = result.getString("name");
                    int age = result.getInt("age");
                    int count = result.getInt("test_count");

                    dtos.add(new ParticipantDTO(id, name, age, count));
                }
            }
        } catch (Exception e) {
            logger.error("Error finding participant DTOs", e);
        }

        return dtos;
    }

    @Override
    public void save(Participant entity) {
        logger.info("Saving new participant: {}", entity.getName());
        String insertParticipant = "INSERT INTO Participants (name, age) VALUES (?, ?)";
        String insertEnrollment = "INSERT INTO Registrations (participant_id, swimmingtest_id) VALUES (?, ?)";

        var con = dbUtils.getConnection();
        try {
            con.setAutoCommit(false);

            try (var stmt = con.prepareStatement(insertParticipant, Statement.RETURN_GENERATED_KEYS)) {
                stmt.setString(1, entity.getName());
                stmt.setInt(2, entity.getAge());
                stmt.executeUpdate();

                try (ResultSet keys = stmt.getGeneratedKeys()) {
                    if (keys.next()) {
                        entity.setId(keys.getInt(1));
                    }
                }
            } catch (SQLException e) {
                logger.error("Error inserting participant: {}", e.getMessage());
                con.rollback();
                return;
            }

            try (var stmt = con.prepareStatement(insertEnrollment)) {
                for (SwimmingTest test : entity.getSwimmingTests()) {
                    stmt.setInt(1, entity.getId());
                    stmt.setInt(2, test.getId());
                    stmt.addBatch();
                }
                stmt.executeBatch();
            } catch (SQLException e) {
                logger.error("Error inserting enrollments: {}", e.getMessage());
                con.rollback();
                return;
            }

            con.commit();
        } catch (Exception e) {
            logger.error(e);
        }
    }

    @Override
    public void update(Participant entity) {
        logger.info("Updating enrollments for participant ID: {}", entity.getId());
        String deleteEnrollments = "DELETE FROM Registrations WHERE participant_id = ?";
        String insertEnrollment = "INSERT INTO Registrations (participant_id, swimmingtest_id) VALUES (?, ?)";

        var con = dbUtils.getConnection();
        try {
            con.setAutoCommit(false);

            try (var stmt = con.prepareStatement(deleteEnrollments)) {
                stmt.setInt(1, entity.getId());
                stmt.executeUpdate();
            } catch (SQLException e) {
                logger.error("Error deleting old enrollments: {}", e.getMessage());
                con.rollback();
            }

            try (var stmt = con.prepareStatement(insertEnrollment)) {
                for (SwimmingTest test : entity.getSwimmingTests()) {
                    stmt.setInt(1, entity.getId());
                    stmt.setInt(2, test.getId());
                    stmt.addBatch();
                }
                stmt.executeBatch();
            } catch (SQLException e) {
                logger.error("Error inserting new enrollments: {}", e.getMessage());
                con.rollback();
            }

            con.commit();
        } catch (Exception e) {
            logger.error(e);
        }
    }

    @Override
    public void delete(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public Participant findById(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public List<Participant> findAll() {
        throw new UnsupportedOperationException("Not implemented yet");
    }
}