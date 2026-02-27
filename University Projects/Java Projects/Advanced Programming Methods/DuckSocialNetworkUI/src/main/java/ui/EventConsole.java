package ui;

import domain.duck.Duck;
import service.EventService;
import service.UserService;
import utils.TipEvent;

import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class EventConsole implements Console {
    private final EventService srv;
    private final Scanner sc = new Scanner(System.in);

    public EventConsole(EventService srv) {
        this.srv = srv;
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
                    case "1": addRaceEvent(); break;
                    case "2": deleteRaceEvent(); break;
                    case "3": listEvents(); break;
                    case "4": startRaceEvent(); break;
                    case "5": subscribeToEvent(); break;
                    case "6": unsubscribeFromEvent(); break;
                    case "0": running = false; break;
                    default: System.out.println("Unknown option");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("\n--- DuckSocialNetwork (Event)---");
        System.out.println("1. Add event");
        System.out.println("2. Delete event");
        System.out.println("3. List events");
        System.out.println("4. Start race event");
        System.out.println("5. Subscribe");
        System.out.println("6. Unsubscribe");
        System.out.println("0. Back");
        System.out.print("Choose> ");
    }

    /**
     * Prompts the user for data input and adds a race event
     */
    private void addRaceEvent(){
        System.out.print("id: "); Long id = Long.parseLong(sc.nextLine());
        System.out.print("name: "); String name = sc.nextLine();
        System.out.print("Number of ducks: "); int nrDucks = Integer.parseInt(sc.nextLine());
        System.out.print("Number of lanes: "); int nrLanes = Integer.parseInt(sc.nextLine());
        List<Long> distances = new ArrayList<>(nrLanes);
        for (int i = 0; i < nrLanes; i++) {
            System.out.print("Distance on lane " + (i + 1) + ": ");
            distances.add(Long.parseLong(sc.nextLine()));
        }
        srv.addRaceEvent(id, name, TipEvent.Race, nrDucks, distances);
        System.out.println("New race event added.");
    }

    private void deleteRaceEvent() {
        System.out.print("id: "); Long id = Long.parseLong(sc.nextLine());
        srv.deleteRaceEvent(id);
        System.out.println("Race event deleted.");
    }

    private void listEvents() {
        var all = srv.listEvents();
        if (all.isEmpty()) {
            System.out.println("No race events found.");
        }
        else {
            all.forEach(System.out::println);
        }
    }

    private void startRaceEvent() {
        System.out.print("id: "); Long id = Long.parseLong(sc.nextLine());
        srv.startRaceEvent(id);
    }

    private void subscribeToEvent(){
        System.out.print("Event id: "); Long eventId = Long.parseLong( sc.nextLine());
        System.out.print("User id: "); Long userId = Long.parseLong(sc.nextLine());
        srv.addSubscriber(eventId, userId);
        System.out.println("Subscribed to race event.");
    }

    private void unsubscribeFromEvent(){
        System.out.print("Event id: "); Long eventId = Long.parseLong(sc.nextLine());
        System.out.print("User id: "); Long userId = Long.parseLong(sc.nextLine());
        srv.deleteSubscriber(eventId, userId);
        System.out.println("Unsubscribed from race event.");
    }
}
