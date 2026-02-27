package domain;

import events.Event;

import java.util.Objects;

public abstract class User extends Entity<Long> implements Observer {
    private final String username, email;
    private String password;

    public User(long id, String username, String email, String password) {
        super(id);
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public Long getId() {
        return super.getId();
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "User id = " + super.getId() + ", username = " + username + ", email = " + email + ", password = " + password;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return Objects.equals(username, user.username) || Objects.equals(email, user.email);
    }

    @Override
    public int hashCode() {
        return Objects.hash(username, email);
    }

    @Override
    public void update(Event e){
        System.out.println("User " + super.getId() + " got an update about event " + e.getName());
    }

    // public abstract void login();

    // public abstract void logout();

    // public abstract void sendMessage();

    // public abstract void receiveMessage();
}
