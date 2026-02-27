import database.DBConnection;
import domain.User;
import domain.card.Card;
import domain.duck.Duck;
import events.Event;
import repository.database.DBCardRepository;
import repository.database.DBEventRepository;
import repository.database.DBFriendshipRepository;
import repository.database.DBUserRepository;
import service.CardService;
import service.EventService;
import service.UserService;
import ui.MainConsole;

import java.sql.SQLException;

public class Main {
    public static void main(String[] args) {
        try {
            MainConsole ui = getMainConsole();
            ui.start();
        } catch (SQLException e) {
            System.out.println("Can't connect to the database.");
        }
    }

    private static MainConsole getMainConsole() throws SQLException {
        DBCardRepository<Long, Card<? extends Duck>> cardRepo = new DBCardRepository<>(DBConnection.getConnection());
        DBUserRepository<Long, User> userRepo = new DBUserRepository<>(DBConnection.getConnection());
        DBFriendshipRepository friendshipRepo = new DBFriendshipRepository(DBConnection.getConnection());
        DBEventRepository<Long, Event> eventRepo = new DBEventRepository<>(DBConnection.getConnection());
        CardService cardServ = new CardService(userRepo, cardRepo);
        UserService userServ = new UserService(userRepo, friendshipRepo, cardRepo);
        EventService serv = new EventService(userRepo, eventRepo);
        return new MainConsole(userServ, cardServ, serv);
    }
}
