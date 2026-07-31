package app.client;

import app.client.gui.LoginController;
import app.network.objectprotocol.ServicesObjectProxy;
import app.services.IService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class StartObjectClientFX extends Application {
    private static final int PORT = 55555;
    private static final String SERVER = "localhost";

    @Override
    public void start(Stage primaryStage) throws Exception {
        IService service = new ServicesObjectProxy(SERVER, PORT);
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/login-page.fxml"));
        Parent root = loader.load();
        LoginController loginController = loader.getController();
        loginController.setService(service);

        primaryStage.setTitle("Login");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
