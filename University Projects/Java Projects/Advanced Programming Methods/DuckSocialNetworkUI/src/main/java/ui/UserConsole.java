package ui;

import domain.duck.Duck;
import domain.person.Persoana;
import domain.User;
import service.UserService;

import java.time.LocalDate;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class UserConsole implements Console{
    private final UserService srv;
    private final Scanner sc = new Scanner(System.in);

    public UserConsole(UserService srv) {
        this.srv = srv;
    }

    /**
     * Opens the user-manipulation console, displaying the menu and handling user input.
     */
    public void start() {
        boolean running = true;
        while (running) {
            printMenu();
            String cmd = sc.nextLine().trim();
            try {
                switch (cmd) {
                    case "1": addUser(); break;
                    case "2": updateUser(); break;
                    case "3": removeUser(); break;
                    case "4": listUsers(); break;
                    case "5": addFriend(); break;
                    case "6": removeFriend(); break;
                    case "7": listFriendships(); break;
                    case "8": communitiesCount(); break;
                    case "9": mostSociableCommunity(); break;
                    case "0": running = false; break;
                    default: System.out.println("Unknown option");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("\n--- DuckSocialNetwork (Users) ---");
        System.out.println("1. Add user");
        System.out.println("2. Update user");
        System.out.println("3. Remove user");
        System.out.println("4. List users");
        System.out.println("5. Add friend");
        System.out.println("6. Remove friend");
        System.out.println("7. List friendships");
        System.out.println("8. Number of communities");
        System.out.println("9. Most sociable community (max diameter)");
        System.out.println("0. Back");
        System.out.print("Choose> ");
    }

    /**
     * Prompts the user to input data and adds a new person or duck accordingly.
     */
    private void addUser() {
        System.out.print("id: "); Long id = Long.parseLong(sc.nextLine());
        System.out.print("username: "); String username = sc.nextLine();
        System.out.print("email: "); String email = sc.nextLine();
        System.out.print("password: "); String pass = sc.nextLine();
        System.out.print("Type PERSON or DUCK: ");
        String type = sc.nextLine().trim().toUpperCase();
        if (type.equals("PERSON")) {
            System.out.print("nume: "); String nume = sc.nextLine();
            System.out.print("prenume: "); String prenume = sc.nextLine();
            System.out.print("dob (YYYY-MM-DD): "); String dob = sc.nextLine();
            System.out.print("ocupatie: "); String ocup = sc.nextLine();
            System.out.print("nivel empatie (0-10): "); double emp = Double.parseDouble(sc.nextLine());
            srv.addPerson(id,username,email,pass,nume,prenume, LocalDate.parse(dob),ocup,emp);
            System.out.println("Person added.");
        } else if (type.equals("DUCK")) {
            System.out.print("tip (SWIMMING,FLYING,FLYING_AND_SWIMMING): "); String tip = sc.nextLine().toUpperCase();
            System.out.print("viteza: "); double v = Double.parseDouble(sc.nextLine());
            System.out.print("rezistenta: "); double r = Double.parseDouble(sc.nextLine());
            System.out.print("card id: "); Long cardId = Long.parseLong(sc.nextLine());
            srv.addDuck(id,username,email,pass,utils.TipRata.valueOf(tip), v, r, cardId);
            System.out.println("Duck added.");
        } else {
            System.out.println("Unknown type");
        }
    }

    private void printPersonUpdateMenu(){
        System.out.println("What you want to update?");
        System.out.println("1. Password");
        System.out.println("2. Job");
        System.out.println("3. Empathy (0-10)");
        System.out.println("0. Done");
    }

    private void printDuckUpdateMenu(){
        System.out.println("What you want to update?");
        System.out.println("1. Password");
        System.out.println("2. Speed");
        System.out.println("3. Resistance");
        System.out.println("4. Card ID");
        System.out.println("0. Done");
    }

    /**
     * Prompts the user to input data and updates a person.
     */
    private void updatePerson(Long id){
        String password = "", job = "";
        double nivelEmpatie = -1;
        boolean running = true;

        printPersonUpdateMenu();
        while (running) {
            System.out.print("Choose> ");
            String cmd = sc.nextLine().trim();
            switch (cmd) {
                case "1":
                    System.out.print("New password: "); password = sc.nextLine().trim(); break;
                case "2":
                    System.out.print("New job: "); job = sc.nextLine().trim(); break;
                case "3":
                    System.out.print("New value for empathy: ");
                    nivelEmpatie = Double.parseDouble(sc.nextLine().trim()); break;
                case "0": running = false; break;
                default: System.out.println("Unknown option");
            }
        }
        srv.updatePerson(id, password, job, nivelEmpatie);
        System.out.println("Person updated.");
    }

    /**
     * Prompts the user to input data and updates a duck.
     */
    private void updateDuck(Long id){
        String password = "";
        double speed = -1, resistance = -1;
        long cardId = -1;
        boolean running = true;

        printDuckUpdateMenu();
        while (running) {
            System.out.print("Choose> ");
            String cmd = sc.nextLine().trim();
            switch (cmd) {
                case "1":
                    System.out.print("New password: "); password = sc.nextLine().trim(); break;
                case "2":
                    System.out.print("New speed: "); speed = Double.parseDouble(sc.nextLine().trim()); break;
                case "3":
                    System.out.print("New resistance: "); resistance = Double.parseDouble(sc.nextLine().trim()); break;
                case "4":
                    System.out.print("New card ID: "); cardId = Long.parseLong(sc.nextLine().trim()); break;
                case "0": running = false; break;
                default: System.out.println("Unknown option");
            }
        }
        srv.updateDuck(id, password, speed, resistance, cardId);
        System.out.println("Duck updated.");
    }

    /**
     * Prompts the user to input data and updates a person or duck accordingly.
     */
    private void updateUser() {
        System.out.print("User id to update: "); Long id = Long.parseLong(sc.nextLine());
        User u = srv.findUserById(id);
        if (u instanceof Persoana){
            updatePerson(id);
        }
        else if (u instanceof Duck){
            updateDuck(id);
        }
    }

    /**
     * Prompts for a user ID and removes the corresponding user from the network.
     */
    private void removeUser() {
        System.out.print("User id to remove: ");
        Long id = Long.parseLong(sc.nextLine());
        srv.removeUser(id);
        System.out.println("Removed.");
    }

    /**
     * Prompts for two user IDs and adds a friendship between them.
     */
    private void addFriend() {
        System.out.print("User id1: "); Long id1 = Long.parseLong(sc.nextLine());
        System.out.print("User id2: "); Long id2 = Long.parseLong(sc.nextLine());
        srv.addFriend(id1, id2);
        System.out.println("Friendship added.");
    }

    /**
     * Prompts for two user IDs and removes the friendship between them.
     */
    private void removeFriend() {
        System.out.print("User id1: "); Long id1 = Long.parseLong(sc.nextLine());
        var ids = srv.getFriendsIds(id1);
        System.out.print("User's friends: ");
        for (Long id : ids) {
            String separator = "";
            if (!id.equals(ids.getLast()))
                separator = ", ";
            System.out.print(id + separator);
        }
        System.out.print("\nUser id2: "); Long id2 = Long.parseLong(sc.nextLine());
        srv.removeFriend(id1, id2);
        System.out.println("Friendship removed.");
    }

    /**
     * Lists all users in the network to the console.
     */
    private void listUsers() {
        var all = srv.listUsers();
        if (all.isEmpty())
            System.out.println("No users.");
        else
            all.forEach(System.out::println);
    }

    /**
     * Lists all friendships in the network to the console.
     */
    private void listFriendships(){
        var all = srv.listFriendships();
        if (all.isEmpty())
            System.out.println("No friendships.");
        else {
            for (var id : all.keySet())
                System.out.println(id + ": " + all.get(id));
        }
    }

    /**
     * Displays the number of communities in the network.
     */
    private void communitiesCount() {
        int c = srv.numberOfCommunities();
        System.out.println("Number of communities: " + c);
    }

    /**
     * Displays the most sociable community (largest diameter) and its members.
     */
    private void mostSociableCommunity() {
        Map.Entry<List<Long>, Integer> entry = srv.mostSociableCommunity();
        List<Long> comp = entry.getKey();
        int diam = entry.getValue();
        System.out.println("Diameter: " + diam);
        System.out.println("Members:");
        for (Long id : comp) {
            var u = srv.findUserById(id);
            System.out.println(" - " + u);
        }
    }
}
