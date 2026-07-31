package app.persistance.repository;

import app.model.SwimmingTest;
import app.model.SwimmingTestDTO;
import app.persistance.SwimmingTestRepository;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.List;

public class SwimmingTestsDBRepository implements SwimmingTestRepository {
    private final DBUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public SwimmingTestsDBRepository(DBUtils dbUtils) {
        logger.info("Initializing SwimmingTestsDBRepository with utils: {} ", dbUtils);
        this.dbUtils = dbUtils;
    }

    @Override
    public List<SwimmingTest> findSwimmingTestsByParticipantId(Integer participantId) {
        logger.info("Finding swimming tests for participant with ID: {}", participantId);
        List<SwimmingTest> swimmingTests = new ArrayList<>();

        var con = dbUtils.getConnection();
        String query = "SELECT S.* FROM SwimmingTests S " +
                       "JOIN Registrations R ON S.id = R.swimmingtest_id " +
                       "WHERE R.participant_id = ?";
        try (var stmt = con.prepareStatement(query)) {
            stmt.setInt(1, participantId);
            try (var result = stmt.executeQuery()) {
                while (result.next()) {
                    SwimmingTest test = new SwimmingTest(
                            result.getInt("id"),
                            result.getInt("distance"),
                            result.getString("style")
                    );
                    swimmingTests.add(test);
                }
            }
        } catch (Exception e) {
            logger.error(e);
        }
        return swimmingTests;
    }

    @Override
    public List<SwimmingTestDTO> findAllDTOs() {
        logger.info("Finding all swimming test DTOs");
        List<SwimmingTestDTO> tests = new ArrayList<>();
        String query = "SELECT ST.*, COUNT(R.participant_id) AS participant_count " +
                       "FROM SwimmingTests ST " +
                       "LEFT JOIN Registrations R ON R.swimmingtest_id = ST.id " +
                       "GROUP BY ST.id, ST.distance, ST.style";

        var con = dbUtils.getConnection();
        try (var stmt = con.prepareStatement(query);
             var result = stmt.executeQuery()) {
            while (result.next()) {
                tests.add(new SwimmingTestDTO(
                        result.getInt("id"),
                        result.getInt("distance"),
                        result.getString("style"),
                        result.getInt("participant_count")
                ));
            }
        } catch (Exception e) {
            logger.error(e);
        }
        return tests;
    }

    @Override
    public List<SwimmingTest> findByStyle(String style) {
        throw new UnsupportedOperationException("Not implemented yet.");
    }

    @Override
    public List<SwimmingTest> findAll() {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public void save(SwimmingTest entity) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public void delete(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public void update(SwimmingTest entity) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public SwimmingTest findById(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }
}