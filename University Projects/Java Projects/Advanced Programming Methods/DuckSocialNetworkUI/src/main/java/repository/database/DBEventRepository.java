package repository.database;

import domain.Entity;
import domain.duck.SwimmingDuck;
import events.Event;
import events.RaceEvent;
import exceptions.RepositoryException;
import repository.Repository;
import utils.TipEvent;
import utils.TipRata;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBEventRepository<ID, TElem extends Entity<ID>> implements Repository<ID, TElem> {
    private final Connection connection;

    public DBEventRepository(Connection connection) {
        this.connection = connection;
    }

    public void save(TElem entity) {
        if (entity instanceof Event event) {
            String query = "INSERT INTO Events(eventID, name, type) VALUES (?, ?, ?)";
            try (PreparedStatement stmt = connection.prepareStatement(query)) {
                stmt.setObject(1, event.getId());
                stmt.setString(2, event.getName());
                stmt.setString(3, event.getType().toString());
                stmt.executeUpdate();

                if (event.getType() == TipEvent.Race) {
                    saveRaceEvent(entity);
                }
            } catch (SQLException e) {
                throw new RepositoryException("DB error: " + e.getMessage());
            }
        }
    }

    private void saveRaceEvent(TElem entity) {
        if (entity instanceof RaceEvent event) {
            String query = "INSERT INTO RaceEvents(eventID, ducks, distances) VALUES (?, ?, ?)";
            try (PreparedStatement stmt = connection.prepareStatement(query)) {
                Long[] ducks = event.getDucks().stream().map(SwimmingDuck::getId).toArray(Long[]::new);
                Array duckArray = connection.createArrayOf("BIGINT", ducks);
                Array distArray = connection.createArrayOf("BIGINT", event.getDistances().toArray());

                stmt.setLong(1, event.getId());
                stmt.setArray(2, duckArray);
                stmt.setArray(3, distArray);
                stmt.executeUpdate();
            } catch (SQLException e) {
                throw new RepositoryException("DB error: " + e.getMessage());
            }
        }
    }

    public void delete(ID id) {
        String query = "DELETE FROM Events WHERE eventID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setObject(1, id);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    private List<SwimmingDuck> loadDucksByID(Long[] duckIDs) {
        List<SwimmingDuck> ducks = new ArrayList<>();

        if (duckIDs == null || duckIDs.length == 0)
            return ducks;

        String sql = """
                    SELECT u.userID, u.username, u.email, u.password,
                           d.type, d.speed, d.resistance, d.cardID
                    FROM Users u
                    JOIN Ducks d ON u.userID = d.userID
                    WHERE u.userID = ANY (?)
                    """;
        try (PreparedStatement st = connection.prepareStatement(sql)) {
            Array idArray = connection.createArrayOf("BIGINT", duckIDs);
            st.setArray(1, idArray);
            ResultSet rs = st.executeQuery();

            while (rs.next()) {
                long id = rs.getLong("userID");
                String username = rs.getString("username");
                String email = rs.getString("email");
                String password = rs.getString("password");

                TipRata type = TipRata.valueOf(rs.getString("type").toUpperCase());
                double speed = rs.getDouble("speed");
                double resistance = rs.getDouble("resistance");
                Long cardID = rs.getObject("cardID", Long.class);

                SwimmingDuck duck = new SwimmingDuck(id, username, email, password,
                        type, speed, resistance, cardID);
                ducks.add(duck);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error loading ducks by IDs", e);
        }
        return ducks;
    }


    @SuppressWarnings("unchecked")
    private TElem mapEvent(ResultSet rs) throws SQLException {
        long eventID = rs.getLong("eventID");
        String name = rs.getString("name");
        String type = rs.getString("type");

        Event e =  new Event(eventID, name, TipEvent.valueOf(type));
        e.setSubscribers(getSubscribersCountForAnEvent(eventID));
        return (TElem) e;
    }

    @SuppressWarnings("unchecked")
    public TElem findById(ID id) {
        String query = """
                    SELECT e.eventID, e.name, r.ducks, r.distances
                    FROM Events e
                    JOIN RaceEvents r ON e.eventID = r.eventID
                    WHERE e.eventID = ?
                    """;
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setObject(1, id);
            ResultSet rs = stmt.executeQuery();

            if (rs.next())
            {
                Long eventID = rs.getLong("eventID");
                String name = rs.getString("name");

                Long[] duckIDs = (Long[]) rs.getArray("ducks").getArray();
                Long[] dist = (Long[]) rs.getArray("distances").getArray();

                List<SwimmingDuck> ducks = loadDucksByID(duckIDs);

                return (TElem) new RaceEvent(eventID, name, TipEvent.Race, ducks, List.of(dist));
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
        return null;
    }

    public List<TElem> findAll() {
        String query = "SELECT * FROM Events";
        List<TElem> events = new ArrayList<>();
        try (Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery(query)){
            while (rs.next()){
                events.add(mapEvent(rs));
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
        return events;
    }

    public void subscribeToEvent(ID eventID, Long userID) {
        String query = "INSERT INTO EventSubscribers(eventID, userID) VALUES(?, ?)";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setObject(1, eventID);
            stmt.setLong(2, userID);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    public void unsubscribeFromEvent(ID eventID, Long userID) {
        String query = "DELETE FROM EventSubscribers WHERE eventID = ? AND userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setObject(1, eventID);
            stmt.setLong(2, userID);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    private int getSubscribersCountForAnEvent(Long eventID) {
        String query = "SELECT COUNT(*) FROM EventSubscribers WHERE eventID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setObject(1, eventID);
            var rs = stmt.executeQuery();
            if (rs.next()){
                return rs.getInt(1);
            }
            return 0;
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    public List<Long> getSubscriberIDsForAnEvent(Long eventID) {
        List<Long> subscriberIDs = new ArrayList<>();
        String query = "SELECT userID FROM EventSubscribers WHERE eventID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setLong(1, eventID);
            var rs = stmt.executeQuery();
            while(rs.next()){
                Long id = rs.getLong(1);
                subscriberIDs.add(id);
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
        return subscriberIDs;
    }
}
