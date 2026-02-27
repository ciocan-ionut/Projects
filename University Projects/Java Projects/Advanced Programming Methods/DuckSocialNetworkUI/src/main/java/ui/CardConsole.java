package ui;

import service.CardService;
import utils.TipRata;

import java.util.Scanner;

public class CardConsole implements Console{
    private final CardService srv;
    private final Scanner sc = new Scanner(System.in);

    public CardConsole(CardService srv) {
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
                    case "1": addCard(); break;
                    case "2": deleteCard(); break;
                    case "3": listCards(); break;
                    case "0": running = false; break;
                    default: System.out.println("Unknown option");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("\n--- DuckSocialNetwork (Card) ---");
        System.out.println("1. Add card");
        System.out.println("2. Delete card");
        System.out.println("3. List cards");
        System.out.println("0. Back");
        System.out.print("Choose> ");
    }

    /**
     * Prompts the user for data input and adds a new card
     */
    private void addCard(){
        System.out.print("Card id: "); long id = Long.parseLong(sc.nextLine());
        System.out.print("Card name: "); String name = sc.nextLine();
        System.out.print("tip (SWIMMING,FLYING,FLYING_AND_SWIMMING): "); String tip = sc.nextLine().toUpperCase();
        srv.addCard(id,name, TipRata.valueOf(tip));
        System.out.println("Card added.");
    }

    /**
     * Prompts the user for data input and deletes a card
     */
    private void deleteCard(){
        System.out.print("Card id: "); long id = Long.parseLong(sc.nextLine());
        srv.deleteCard(id);
        System.out.println("Card deleted.");
    }

    /**
     * Lists all cards in the network to the console
     */
    private void listCards(){
        var all = srv.listCards();
        if (all.isEmpty())
            System.out.println("No cards.");
        else
            all.forEach(System.out::println);
    }
}
