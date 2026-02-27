package repository.database;

import domain.duck.Duck;
import domain.Entity;
import domain.person.Persoana;
import domain.User;
import exceptions.RepositoryException;
import factory.DuckFactory;
import repository.Repository;
import utils.TipRata;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBUserRepository<ID, TElem extends Entity<ID>> implements Repository<ID, TElem> {
    private final Connection connection;

    public DBUserRepository(Connection connection) {
        this.connection = connection;
    }

    /**
     * Maps the current row of the given ResultSet to a concrete user entity
     *
     * @param rs the ResultSet positioned on the row to be converted
     * @return the mapped user entity as TElem
     * @throws SQLException if it encountered a database error
     * @throws RepositoryException if the user type is not supported
     */
    @SuppressWarnings("unchecked")
    private TElem mapUser(ResultSet rs) throws SQLException {
        long userID = rs.getLong("userID");
        String username = rs.getString("username");
        String email = rs.getString("email");
        String password = rs.getString("password");
        String type = rs.getString("type");

        return switch (type) {
            case "Person" -> (TElem) loadPerson(userID, username, email, password);
            case "Duck" -> (TElem) loadDuck(userID, username, email, password);
            default -> throw new RepositoryException("Unsupported user type!");
        };
    }

    /**
     * Finds an entity by its ID.
     *
     * @param id the ID of the entity to find
     * @return the entity with the given ID, or null if it does not exist
     * @throws RepositoryException if the ID is null, the user type is unsupported, or it encountered a database error
     */
    @Override
    public TElem findById(ID id) {
        if (id == null) {
            throw new RepositoryException("ID can not be null!");
        }

        String query = "SELECT * FROM Users WHERE userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setObject(1, id);

            ResultSet rs = stmt.executeQuery();
            if (!rs.next())
                return null;

            return mapUser(rs);
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Returns a list of all entities stored in the database.
     *
     * @return a list containing all entities
     * @throws RepositoryException if the user type is unsupported, or it encountered a database error
     */
    @Override
    public List<TElem> findAll() {
        List<TElem> users = new ArrayList<>();
        String userQuery = "SELECT * FROM Users";
        try (Statement stmt = connection.createStatement();
             ResultSet rs = stmt.executeQuery(userQuery)) {

            while (rs.next()) {
                users.add(mapUser(rs));
            }

            return users;
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Loads person's data from the database
     *
     * @param userID the id of the person
     * @param username the username of the person
     * @param email the email of the person
     * @param password the password of the person
     * @return the person with the loaded details
     * @throws RepositoryException if it encountered a database error
     */
    private Persoana loadPerson(long userID, String username, String email, String password) {
        String query = "SELECT * FROM People WHERE userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setLong(1, userID);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    String surname = rs.getString("surname");
                    String name = rs.getString("name");
                    String job = rs.getString("job");
                    Date dob = rs.getDate("dob");
                    double empathy = rs.getDouble("empathy");

                    return new Persoana(userID, username, email, password, surname, name, job, dob.toLocalDate(), empathy);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
        return null;
    }

    /**
     * Loads duck's data from the database
     *
     * @param userID the id of the duck
     * @param username the username of the duck
     * @param email the email of the duck
     * @param password the password of the duck
     * @return the duck with the loaded details
     * @throws RepositoryException if it encountered a database error
     */
    private Duck loadDuck(long userID, String username, String email, String password) {
        String query = "SELECT * FROM Ducks WHERE userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setLong(1, userID);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    String duckType = rs.getString("type");
                    double speed = rs.getDouble("speed");
                    double resistance = rs.getDouble("resistance");
                    long cardID = rs.getLong("cardID");

                    return DuckFactory.createDuck(userID, username, email, password, TipRata.valueOf(duckType), speed, resistance, cardID);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
        return null;
    }

    /**
     * Saves a new entity in the database.
     * If an entity with the same ID, username or email already exists, the entity is not added.
     *
     * @param entity the entity to save
     * @throws RepositoryException if the entity is null, or it encountered a database error
     */
    @Override
    public void save(TElem entity) {
        if (entity == null) {
            throw new RepositoryException("Entity can not be null!");
        }
        saveUserToDB(entity);
    }

    /**
     * Saves a new entity in the database if it's a user
     *
     * @param entity the entity to save
     * @throws RepositoryException if the user type is unsupported or encountered a database error
     */
    private void saveUserToDB(TElem entity) {
        if (entity instanceof User user) {
            String userQuery = "INSERT INTO Users (userID, username, email, password, type) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement stmt = connection.prepareStatement(userQuery)) {
                stmt.setLong(1, user.getId());
                stmt.setString(2, user.getUsername());
                stmt.setString(3, user.getEmail());
                stmt.setString(4, user.getPassword());

                if (user instanceof Persoana) {
                    stmt.setString(5, "Person");
                    stmt.executeUpdate();
                    savePersonToDB((Persoana) user);
                } else if (user instanceof Duck) {
                    stmt.setString(5, "Duck");
                    stmt.executeUpdate();
                    saveDuckToDB((Duck) user);
                } else {
                    throw new RepositoryException("Unsupported user type!");
                }
            } catch (SQLException e) {
                throw new RepositoryException("DB error: " + e.getMessage());
            }
        }
    }

    /**
     * Saves a new person in the database
     *
     * @param person the person to save
     * @throws RepositoryException if it encountered a database error
     */
    private void savePersonToDB(Persoana person) {
        String personQuery = "INSERT INTO People (userID, surname, name, job, dob, empathy) VALUES (?, ?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = connection.prepareStatement(personQuery)){
            stmt.setLong(1, person.getId());
            stmt.setString(2, person.getSurname());
            stmt.setString(3, person.getName());
            stmt.setString(4, person.getJob());
            stmt.setDate(5, Date.valueOf(person.getDob()));
            stmt.setDouble(6, person.getEmpathy());
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Saves a new duck in the database
     *
     * @param duck the duck to save
     * @throws RepositoryException if encountered a database error
     */
    private void saveDuckToDB(Duck duck) {
        String duckQuery = "INSERT INTO Ducks (userID, type, speed, resistance, cardID) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = connection.prepareStatement(duckQuery)){
            stmt.setLong(1, duck.getId());
            stmt.setString(2, duck.getType().toString());
            stmt.setDouble(3, duck.getSpeed());
            stmt.setDouble(4, duck.getResistance());
            stmt.setLong(5, duck.getCard());
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Deletes the entity with the specified ID from the database.
     *
     * @param id the ID of the entity to delete
     * @throws RepositoryException if the ID is null, the user type is unsupported or encountered a database error
     */
    @Override
    public void delete(ID id) {
        if (id == null) {
            throw new RepositoryException("ID can not be null!");
        }
        deleteFromDB(id);
    }

    /**
     * Deletes the user from the database
     *
     * @param id the id of the user to delete
     * @throws RepositoryException if the user type is unsupported or encountered a database error
     */
    private void deleteFromDB(ID id) {
        String query = "DELETE FROM Users WHERE userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setObject(1, id);
            stmt.executeUpdate();
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Updates an existing entity in the database
     *
     * @param entity the entity to update
     * @throws RepositoryException if the entity is null, the user type is unsupported or encountered a database error
     */
    public void update(TElem entity) {
        if (entity == null) {
            throw new RepositoryException("Entity can not be null!");
        }
        updateUserDB(entity);
    }

    /**
     * Updates an existing entity in the database
     *
     * @param entity the entity to update
     * @throws RepositoryException if the user type is unsupported or encountered a database error
     */
    private void updateUserDB(TElem entity) {
        if (entity instanceof User user) {
            String query = "UPDATE Users SET password = ? WHERE userID = ?";
            try (PreparedStatement stmt = connection.prepareStatement(query)) {
                stmt.setString(1, user.getPassword());
                stmt.setLong(2, user.getId());
                stmt.executeUpdate();

                if (entity instanceof Persoana) {
                    updatePersonDB((Persoana) entity);
                } else if (entity instanceof Duck){
                    updateDuckDB((Duck) entity);
                } else {
                    throw new RepositoryException("Unsupported user type!");
                }
            } catch (SQLException e){
                throw new RepositoryException("DB error: " + e.getMessage());
            }
        }
    }

    /**
     * Updates an existing person in the database
     *
     * @param person the person to update
     * @throws RepositoryException if encountered a database error
     */
    private void updatePersonDB(Persoana person) {
        String query = "UPDATE People SET job = ?, empathy = ? WHERE userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setString(1, person.getJob());
            stmt.setDouble(2, person.getEmpathy());
            stmt.setLong(3, person.getId());
            stmt.executeUpdate();
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Updates an existing duck in the database
     *
     * @param duck the entity to update
     * @throws RepositoryException if encountered a database error
     */
    private void updateDuckDB(Duck duck) {
        String query = "UPDATE Ducks SET speed = ?, resistance = ?, cardID = ? WHERE userID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setDouble(1, duck.getSpeed());
            stmt.setDouble(2, duck.getResistance());
            stmt.setLong(3, duck.getCard());
            stmt.setLong(4, duck.getId());
            stmt.executeUpdate();
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }
}
