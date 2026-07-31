package app.model;

import jakarta.persistence.*;

import java.util.ArrayList;
import java.util.List;

@jakarta.persistence.Entity
@Table(name = "Participants")
public class Participant extends Entity<Integer> {
    private String name;
    private int age;

    @ManyToMany(fetch = FetchType.EAGER, cascade = {CascadeType.MERGE})
    @JoinTable(
            name = "Registrations",
            joinColumns = @JoinColumn(name = "participant_id"),
            inverseJoinColumns = @JoinColumn(name = "swimmingtest_id")
    )
    private List<SwimmingTest> swimmingTests;

    public Participant() { }

    public Participant(Integer id, String name, int age) {
        super(id);
        this.name = name;
        this.age = age;
        this.swimmingTests = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public List<SwimmingTest> getSwimmingTests() {
        return swimmingTests;
    }

    public void setSwimmingTests(List<SwimmingTest> swimmingTests) {
        this.swimmingTests.addAll(swimmingTests);
    }

    public void addSwimmingTest(SwimmingTest swimmingTest) {
        swimmingTests.add(swimmingTest);
    }
}
