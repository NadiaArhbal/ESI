/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package esi.bloc3.atlj.skyjo.client;

import esi.bloc3.atlj.skyjo.client.model.SkyjoClient;
import esi.bloc3.atlj.skyjo.client.fxml.FXMLConnectionController;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.EventHandler;
import javafx.stage.Stage;

/**
 * Main application
 *
 * @author Christophe Rische
 */
public class Main extends Application {

    private Thread waiterThread;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {

        try {
            FXMLConnectionController ctrl = new FXMLConnectionController();
            ctrl.start();

            String name = FXMLConnectionController.pseudo;
            int port = FXMLConnectionController.portNumber;
            String host = FXMLConnectionController.hostName;
            String password = FXMLConnectionController.password;

            Thread waiterThread;
            SkyjoClient client = new SkyjoClient(host, port,
                    name, password);
            Task<Void> sleeper = new Task<Void>() {
                @Override
                protected Void call() throws Exception {
                    Thread.sleep(200);
                    while (client.isWaiting()) {
                        Thread.sleep(1);
                    }
                    return null;
                }
            };
            sleeper.setOnSucceeded(new EventHandler<WorkerStateEvent>() {
                @Override
                
                public void handle(WorkerStateEvent event) {
                    Platform.runLater(() -> {
                        SkyjoClientGui gui = new SkyjoClientGui(client, stage);
                    });
                }
            });
            sleeper.setOnFailed(new EventHandler<WorkerStateEvent>() {
                @Override
                public void handle(WorkerStateEvent event) {
                    Platform.runLater(() -> {
                        SkyjoClientGui gui = new SkyjoClientGui(client, stage);
                    });
                }
            });
            waiterThread = new Thread(sleeper);
            waiterThread.start();
            Thread.sleep(200);
        } catch (IOException ex) {
            Logger.getLogger(SkyjoClientGui.class.getName()).log(Level.SEVERE,
                    "Main error", ex);
            System.exit(0);
        }
    }
}
