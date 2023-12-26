/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package esi.bloc3.atlj.skyjo.client.fxml;

import java.io.IOException;
import java.net.URL;
import javafx.event.ActionEvent;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.stage.Stage;

/**
 * FXML Connection Controller class, this class is used to control the 
 * connection window and recovers the users inputs
 *
 * @author guill
 */
public class FXMLConnectionController implements Initializable {

    /**
     * The controller have 4 global variables that can be read from the outside,
     * thoses variables will be filled when the user is pressing the validate
     * button
     */
    public static String pseudo;
    public static int portNumber;
    public static String hostName;
    public static String password;

    @FXML
    private TextField TF_Pseudo;

    @FXML
    private TextField TF_PortNumber;

    @FXML
    private TextField TF_HostName;

    @FXML
    private TextField TF_Password;

    @FXML
    private Button BTN_Validate;

    /**
     * Event listenning to the validate Button
     * 
     * @param event OnClicked
     */
    @FXML
    private void validate(ActionEvent event) {
        if (isInputValid()) {
            hostName = TF_HostName.getText();
            portNumber = Integer.parseInt(TF_PortNumber.getText());
            pseudo = TF_Pseudo.getText();
            password = TF_Password.getText();
            closeWindow();
        }
    }
    
    /**
     * Closes the FXML Window
     */
    public void closeWindow() {
        Stage stage = (Stage) TF_HostName.getScene().getWindow();
        stage.close();
    }

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }

    /**
     * The start method is used at the controller instanciation, this is 
     * displaying the connection window
     */
    public void start() {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/fxml/FXMLConnection.fxml"));
            Parent root = loader.load();
            Stage authStage = new Stage();
            Scene scene = new Scene(root);
            authStage.getIcons().add(new Image("/data/skyjo.png"));
            authStage.setScene(scene);
            authStage.showAndWait();
        } catch (IOException ex) {
            Logger.getLogger(FXMLConnectionController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Validity check for the inputs TextFields
     * This method is checking if a field is missing or incorrect
     *
     * @return true if user input valid, false instead
     */
    private boolean isInputValid() {
        String errorMessage = "";

        if (TF_Pseudo.getText() == null || TF_Pseudo.getText().length() == 0) {
            errorMessage += "No valid pseudo!\n";
        }
        if (TF_PortNumber.getText() == null || TF_PortNumber.getText().length() == 0) {
            errorMessage += "No valid port number!\n";
        }
        if (TF_HostName.getText() == null || TF_HostName.getText().length() == 0) {
            errorMessage += "No valid host name!\n";
        }

        if (TF_Password.getText() == null || TF_Password.getText().length() == 0) {
            errorMessage += "No valid password!\n";
        } else {
            // try to parse the postal code into an int.
            try {
                Integer.parseInt(TF_PortNumber.getText());
            } catch (NumberFormatException e) {
                errorMessage += "No valid port number (must be an integer)!\n";
            }
        }

        if (errorMessage.length() == 0) {
            return true;
        } else {
            // Show the error message.
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Invalid Fields");
            alert.setHeaderText("Please correct invalid fields");
            alert.setContentText(errorMessage);

            alert.showAndWait();

            return false;
        }
    }

}
