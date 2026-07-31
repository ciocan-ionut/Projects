package app.model;

public class Organizer extends Entity<Integer>{
    private final String username;
    private final String password;

    public Organizer(Integer id, String username, String password) {
        super(id);
        this.username = username;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }
}
