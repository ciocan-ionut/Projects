package ui;

import service.CardService;
import service.EventService;
import service.UserService;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class MainConsole implements Console{
    private final Scanner sc = new Scanner(System.in);

    private final UserConsole userConsole;
    private final CardConsole cardConsole;
    private final EventConsole eventConsole;

    public MainConsole(UserService userServ, CardService cardServ, EventService srv) {
        this.userConsole = new UserConsole(userServ);
        this.cardConsole = new CardConsole(cardServ);
        this.eventConsole = new EventConsole(srv);
    }

    /**
     * Starts the console application, displaying the menu and handling user input.
     */
    public void start() {
        boolean running = true;
        while (running) {
            printMenu();
            String cmd = sc.nextLine().trim();
            try {
                switch (cmd) {
                    case "1": userConsole.start(); break;
                    case "2": cardConsole.start(); break;
                    case "3": eventConsole.start(); break;
                    case "0": running = false; break;
                    default: System.out.println("Unknown option");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
        System.out.println("Bye!");
    }

    private void printMenu() {
        System.out.println("\n--- DuckSocialNetwork ---");
        System.out.println("1. Users");
        System.out.println("2. Cards");
        System.out.println("3. Events");
        System.out.println("0. Exit");
        System.out.print("Choose> ");
    }
}
