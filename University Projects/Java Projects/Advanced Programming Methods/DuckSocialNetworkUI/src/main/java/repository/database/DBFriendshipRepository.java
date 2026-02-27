package repository.database;

import exceptions.RepositoryException;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.*;

public class DBFriendshipRepository {
    private final Connection connection;

    public DBFriendshipRepository(Connection connection) {
        this.connection = connection;
    }

    /**
     * Saves a new friendship between two users.
     * If a friendship already exists between the users, a RepositoryException is thrown.
     *
     * @param userId1 the id of the first user
     * @param userId2 the id of the second user
     * @throws RepositoryException if the users are already friends
     */
    public void save(Long userId1, Long userId2){
        String query = "INSERT INTO Friendships(userId1, userId2) VALUES (?, ?)";
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setLong(1, userId1);
            stmt.setLong(2, userId2);
            stmt.executeUpdate();
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Deletes the friendship between two users.
     * If either user ID does not exist in the repository, a RepositoryException is thrown.
     *
     * @param userId1 the id of the first user
     * @param userId2 the id of the second user
     * @throws RepositoryException if one of the user IDs is invalid
     */
    public void delete(Long userId1, Long userId2){
        String query = "DELETE FROM Friendships WHERE userId1 = ? AND userId2 = ?";
        Long min = userId1 < userId2 ? userId1 : userId2;
        Long max = userId1 > userId2 ? userId1 : userId2;

        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setLong(1, min);
            stmt.setLong(2, max);
            int affected = stmt.executeUpdate();

            if (affected != 1)
                throw new RepositoryException("The friendship does not exist!");
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }

    /**
     * Returns a list of user IDs that are friends with the given user.
     * If the user has no friends, returns an empty list.
     *
     * @param userId the id of the user
     * @return a list of user IDs who are friends with the given user
     */
    public List<Long> getFriendsIds(Long userId) {
        String query = """
        SELECT
            CASE
                WHEN userID1 = ? THEN userID2
                ELSE userID1
            END AS friendID
        FROM Friendships
        WHERE userID1 = ? OR userID2 = ?
       """;

        List<Long> ids = new ArrayList<>();
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setLong(1, userId);
            stmt.setLong(2, userId);
            stmt.setLong(3, userId);

            var rs = stmt.executeQuery();
            while (rs.next()) {
                ids.add(rs.getLong("friendID"));
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }

        return ids;
    }

    /**
     * Returns a set of all user IDs that have at least one friendship.
     *
     * @return a set of user IDs who have friends
     */
    public Set<Long> findAll() {
        String query = "SELECT userID1, userID2 FROM Friendships";

        Set<Long> ids = new HashSet<>();
        try (PreparedStatement stmt = connection.prepareStatement(query)){
            var rs = stmt.executeQuery();
            while (rs.next()){
                ids.add(rs.getLong("userID1"));
                ids.add(rs.getLong("userID2"));
            }
        } catch (SQLException e) {
            throw new RepositoryException("DB error: " + e.getMessage());
        }
        return ids;
    }

    /**
     * Builds the adjacency list for the friendship graph.
     *
     * @return a map where keys are user IDs and values are lists of friend IDs
     * @throws RepositoryException if no friendships exist
     */
    public Map<Long, List<Long>> buildAdjacency(){
        Map<Long, List<Long>> adj = new HashMap<>();

        var friends = findAll();
        if (friends.isEmpty())
            throw new RepositoryException("No friendships found!");

        for (var id : friends){
            adj.put(id, getFriendsIds(id));
        }
        return adj;
    }

    /**
     * Checks if two users are friends.
     *
     * @param userId1 the id of the first user
     * @param userId2 the id of the second user
     * @return true if the users are friends, false otherwise
     */
    public boolean checkIfTheyAreFriends(Long userId1, Long userId2){
        String query = "SELECT userID1, userID2 FROM Friendships WHERE userId1 = ? AND userId2 = ?";
        Long min  = userId1 < userId2 ? userId1 : userId2;
        Long max = userId1 > userId2 ? userId1 : userId2;

        try (PreparedStatement stmt = connection.prepareStatement(query)){
            stmt.setLong(1, min);
            stmt.setLong(2, max);
            var rs = stmt.executeQuery();
            return rs.next();
        } catch (SQLException e){
            throw new RepositoryException("DB error: " + e.getMessage());
        }
    }
}
