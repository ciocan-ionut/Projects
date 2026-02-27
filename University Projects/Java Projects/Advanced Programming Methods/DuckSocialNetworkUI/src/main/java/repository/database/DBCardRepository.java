package repository.database;

import domain.Entity;
import domain.card.Card;
import exceptions.RepositoryException;
import factory.CardFactory;
import repository.Repository;
import utils.TipRata;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBCardRepository<ID, TElem extends Entity<ID>> implements Repository<ID, TElem> {
    private final Connection connection;

    public DBCardRepository(Connection connection) {
        this.connection = connection;
    }

    /**
     * Maps the current row of the ResultSet to a Card entity.
     *
     * @param rs the ResultSet positioned on the row to map
     * @return the mapped Card object
     * @throws SQLException if it encountered a database error
     */
    @SuppressWarnings("unchecked")
    private TElem mapCard(ResultSet rs) throws SQLException {
        long flockID = rs.getLong("flockID");
        String name = rs.getString("name");
        String type = rs.getString("type");

        return (TElem) CardFactory.createCard(flockID, name, TipRata.valueOf(type));
    }

    /**
     * Finds a card by its ID.
     *
     * @param id the ID of the card
     * @return the card, or null if not found
     * @throws RepositoryException if it encountered a database error
     */
    public TElem findById(ID id) {
        String query = "SELECT * FROM Flocks WHERE flockID = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setObject(1, id);

            try (ResultSet rs = stmt.executeQuery()) {
                if (!rs.next())
                    return null;
                return mapCard(rs);
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB Error: " + e.getMessage());
        }
    }

    /**
     * Returns all cards stored in the database.
     *
     * @return a list of all cards
     * @throws RepositoryException if it encountered a database error
     */
    public List<TElem> findAll() {
        List<TElem> cards = new ArrayList<>();
        String query = "SELECT * FROM Flocks";

        try (Statement stmt = connection.createStatement();
             ResultSet rs = stmt.executeQuery(query)) {

            while (rs.next()) {
                cards.add(mapCard(rs));
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB Error: " + e.getMessage());
        }

        return cards;
    }

    /**
     * Saves a new card in the database.
     *
     * @param entity the card to save
     * @throws RepositoryException if it encountered a database error
     */
    public void save(TElem entity) {
        if (entity instanceof Card<?> card) {
            String query = "INSERT INTO Flocks (flockID, name, type) VALUES (?, ?, ?)";

            try (PreparedStatement stmt = connection.prepareStatement(query)) {
                stmt.setObject(1, card.getId());
                stmt.setString(2, card.getName());
                stmt.setString(3, card.getType().toString());
                stmt.executeUpdate();
            } catch (SQLException e) {
                throw new RepositoryException("DB Error: " + e.getMessage());
            }
        }
    }

    /**
     * Deletes a card from the database.
     *
     * @param id the ID of the card to delete
     * @throws RepositoryException if it encountered a database error
     */
    public void delete(ID id) {
        String query = "DELETE FROM Flocks WHERE flockID = ?";

        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setObject(1, id);
            stmt.executeUpdate();

        } catch (SQLException e) {
            throw new RepositoryException("DB Error: " + e.getMessage());
        }
    }
}
