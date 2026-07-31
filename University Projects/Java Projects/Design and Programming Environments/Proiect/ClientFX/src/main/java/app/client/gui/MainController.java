package app.client.gui;

import app.model.ParticipantDTO;
import app.model.SwimmingTest;
import app.model.SwimmingTestDTO;
import app.services.AppException;
import app.services.IObserver;
import javafx.application.Platform;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleLongProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.FlowPane;
import app.services.IService;

import java.util.List;

public class MainController implements IObserver {
    @FXML
    TableView<SwimmingTestDTO> swimmingTestsTable;
    @FXML
    TableColumn<SwimmingTestDTO, Integer> distanceColumn;
    @FXML
    TableColumn<SwimmingTestDTO, String> styleColumn;
    @FXML
    TableColumn<SwimmingTestDTO, Long> participantsColumn;

    @FXML
    TableView<ParticipantDTO> participantsTable;
    @FXML
    TableColumn<ParticipantDTO, String> nameColumn;
    @FXML
    TableColumn<ParticipantDTO, Integer> ageColumn;
    @FXML
    TableColumn<ParticipantDTO, Long> swimmingTestsColumn;

    @FXML
    TextField nameField;
    @FXML
    Spinner<Integer> ageSpinner;
    @FXML
    FlowPane swimmingTestsPane;

    @FXML
    Button clearBtn;
    @FXML
    Button modifyBtn;
    @FXML
    Button saveBtn;

    private IService srv;
    private String loggedUser;

    ObservableList<SwimmingTestDTO> swimmingTests = FXCollections.observableArrayList();
    ObservableList<ParticipantDTO> participants = FXCollections.observableArrayList();

    public void setService(IService srv) {
        this.srv = srv;

        loadSwimmingTestTable();
        loadSwimmingTestPane();
    }

    public void setLoggedUser(String loggedUser) {
        this.loggedUser = loggedUser;
    }

    @FXML
    public void initialize() {
        initializeSwimmingTestTable();
        initializeParticipantsTable();
        ageSpinner.setValueFactory(new SpinnerValueFactory.IntegerSpinnerValueFactory(0, 100));
    }

    private void initializeSwimmingTestTable() {
        distanceColumn.setCellValueFactory(cellData -> new SimpleIntegerProperty(cellData.getValue().distance()).asObject());
        styleColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().style()));
        participantsColumn.setCellValueFactory(cellData -> new SimpleLongProperty(cellData.getValue().participantCount()).asObject());
        swimmingTestsTable.setItems(swimmingTests);

        swimmingTestsTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                loadParticipantsTable(newSelection.id());
            }
        });
    }

    private void initializeParticipantsTable() {
        nameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().name()));
        ageColumn.setCellValueFactory(cellData -> new SimpleIntegerProperty(cellData.getValue().age()).asObject());
        swimmingTestsColumn.setCellValueFactory(cellData -> new SimpleLongProperty(cellData.getValue().swimmingTestCount()).asObject());
        participantsTable.setItems(participants);

        participantsTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                nameField.setText(newSelection.name());
                ageSpinner.getValueFactory().setValue(newSelection.age());

                nameField.setDisable(true);
                ageSpinner.setDisable(true);
                saveBtn.setDisable(true);

                checkSwimmingTestsForParticipant(newSelection.id());
            }
        });
    }

    private void loadSwimmingTestTable() {
        try {
            List<SwimmingTestDTO> swimmingTestDTOs = srv.getAllSwimmingTestDTOs();
            swimmingTests.setAll(swimmingTestDTOs);
        } catch (AppException e) {
            MessageBox.showWarning("Error", e.getMessage());
        }
    }

    private void loadParticipantsTable(int swimmingTestId) {
        try {
            List<ParticipantDTO> participantDTOs = srv.getAllParticipantDTOs(swimmingTestId);
            participants.setAll(participantDTOs);
        } catch (AppException e) {
            MessageBox.showWarning("Error", e.getMessage());
        }
    }

    private void loadSwimmingTestPane() {
        swimmingTestsPane.getChildren().clear();
        for (SwimmingTestDTO swimmingTest : swimmingTests) {
            CheckBox checkBox = new CheckBox(swimmingTest.style() + " " + swimmingTest.distance());
            checkBox.setUserData(swimmingTest);
            swimmingTestsPane.getChildren().add(checkBox);
        }
    }

    private void checkSwimmingTestsForParticipant(int participantId) {
        try {
            List<SwimmingTest> swimmingTests = srv.getSwimmingTestsForParticipant(participantId);
            for (var node : swimmingTestsPane.getChildren()) {
                if (node instanceof CheckBox checkBox) {
                    SwimmingTestDTO swimmingTest = (SwimmingTestDTO) checkBox.getUserData();
                    checkBox.setSelected(swimmingTests.stream().anyMatch(st -> st.getId() == swimmingTest.id()));
                }
            }
        } catch (AppException e) {
            MessageBox.showWarning("Error", e.getMessage());
        }
    }

    @FXML
    private void onClear(ActionEvent event) {
        participantsTable.getSelectionModel().clearSelection();

        nameField.clear();
        ageSpinner.getValueFactory().setValue(0);

        nameField.setDisable(false);
        ageSpinner.setDisable(false);
        saveBtn.setDisable(false);

        checkSwimmingTestsForParticipant(0);
    }

    @FXML
    private void onModify(ActionEvent event) {
        ParticipantDTO selectedParticipant = participantsTable.getSelectionModel().getSelectedItem();
        if (selectedParticipant != null) {
            List<SwimmingTest> selectedSwimmingTests = swimmingTestsPane.getChildren().stream()
                    .filter(node -> node instanceof CheckBox checkBox && checkBox.isSelected())
                    .map(node -> (SwimmingTestDTO) node.getUserData())
                    .map(dto -> new SwimmingTest(dto.id(), dto.distance(), dto.style()))
                    .toList();

            try {
                srv.updateParticipant(selectedParticipant, selectedSwimmingTests);
            } catch (AppException e) {
                MessageBox.showWarning("Error", e.getMessage());
            }
        } else {
            MessageBox.showWarning("Error", "No participant selected!");
        }
    }

    @FXML
    private void onSave(ActionEvent event) {
        String name = nameField.getText();
        int age = ageSpinner.getValue();
        List<SwimmingTest> selectedSwimmingTests = swimmingTestsPane.getChildren().stream()
                .filter(node -> node instanceof CheckBox checkBox && checkBox.isSelected())
                .map(node -> (SwimmingTestDTO) node.getUserData())
                .map(dto -> new SwimmingTest(dto.id(), dto.distance(), dto.style()))
                .toList();

        if (name == null || name.isEmpty() || age < 11 || age > 100 || selectedSwimmingTests.isEmpty()) {
            MessageBox.showWarning("Error", "Invalid input!");
            return;
        }
        try {
            srv.addParticipant(name, age, selectedSwimmingTests);
            onClear(null);
        } catch (AppException e) {
            MessageBox.showWarning("Error", e.getMessage());
        }
    }

    private void refreshTables() {
        SwimmingTestDTO selectedSwimmingTest = swimmingTestsTable.getSelectionModel().getSelectedItem();
        loadSwimmingTestTable();
        if (selectedSwimmingTest != null) {
            for (SwimmingTestDTO test : swimmingTestsTable.getItems()) {
                if (test.id() == selectedSwimmingTest.id()) {
                    swimmingTestsTable.getSelectionModel().select(test);
                    loadParticipantsTable(test.id());
                    break;
                }
            }
        }
        else {
            participants.clear();
        }
    }

    @FXML
    private void onLogout(ActionEvent event) {
        try {
            srv.logout(loggedUser, this);
            saveBtn.getScene().getWindow().hide();
        } catch (AppException e) {
            MessageBox.showWarning("Error", e.getMessage());
        }
    }

    @Override
    public void update() throws AppException {
        Platform.runLater(this::refreshTables);
    }
}
