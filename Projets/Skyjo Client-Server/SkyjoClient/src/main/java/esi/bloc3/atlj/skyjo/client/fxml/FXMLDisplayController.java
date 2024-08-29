package esi.bloc3.atlj.skyjo.client.fxml;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

/**
 * FXML Display Controller class, this class is used to display a custom
 * error message to an user
 *
 * @author guill
 */
public class FXMLDisplayController implements Initializable {

    /**
     * displayMessage a global variable that contains the error message to
     * display on the window, this String needs to be set before controller
     * instanciation
     */
    public static String displayMessage;
    
    @FXML
    private Label LBL;
    
    @FXML
    private ImageView IV_main;
    
    @FXML
    private Button BTN_Ok;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        LBL.setText(displayMessage);
        IV_main.setImage(new Image("/data/warning.png"));
    }
    
    /**
     * Event listenning to the ok Button
     * 
     * @param event OnClicked
     */
    @FXML
    private void ok(ActionEvent event) {
        Stage stage = (Stage) LBL.getScene().getWindow();
        stage.close();
    }

    /**
     * The start method is used at the controller instanciation, this is 
     * displaying the error window
     * The error message needs to be set before controller instantiation
     */
    public void start() {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/fxml/FXMLDisplay.fxml"));
            Parent root = loader.load();
            Stage stage = new Stage();
            Scene scene = new Scene(root);
            stage.getIcons().add(new Image("/data/error.png"));
            stage.setTitle("Erreur");
            stage.setScene(scene);
            stage.showAndWait();
            
        } catch (IOException ex) {
            Logger.getLogger(FXMLDisplayController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
