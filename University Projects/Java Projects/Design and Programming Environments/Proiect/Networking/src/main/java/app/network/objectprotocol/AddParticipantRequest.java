package app.network.objectprotocol;

import app.model.SwimmingTest;

import java.util.List;

public class AddParticipantRequest implements Request {
    private final String name;
    private final int age;
    private final List<SwimmingTest> tests;

    public AddParticipantRequest(String name, int age, List<SwimmingTest> tests) {
        this.name = name;
        this.age = age;
        this.tests = tests;
    }

    public String getName() {
        return name;
    }
    public int getAge() {
        return age;
    }
    public List<SwimmingTest> getTests() {
        return tests;
    }
}
