package app.client.gui;

import app.services.AppException;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import app.services.IService;

import java.io.IOException;

public class LoginController {
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;

    private IService srv;

    public void setService(IService srv) {
        this.srv = srv;
    }

    @FXML
    void onLogin(ActionEvent event) {
        String username = usernameField.getText();
        String password = passwordField.getText();

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/main-page.fxml"));
            Parent root = loader.load();
            MainController controller = loader.getController();

            srv.login(username, password, controller);

            controller.setService(srv);
            controller.setLoggedUser(username);

            openMainPage(root);
            clearFields();
            usernameField.getScene().getWindow().hide();
        } catch (AppException | IOException e) {
            MessageBox.showWarning("Login failed", e.getMessage());
        }
    }

    void openMainPage(Parent root) throws IOException {
        Scene scene = new Scene(root);
        Stage stage  = new Stage();
        stage.setScene(scene);
        stage.setTitle("Management");
        stage.show();
    }

    void clearFields() {
        usernameField.clear();
        passwordField.clear();
    }
}
