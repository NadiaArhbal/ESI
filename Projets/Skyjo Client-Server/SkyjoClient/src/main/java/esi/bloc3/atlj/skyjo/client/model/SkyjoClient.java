package esi.bloc3.atlj.skyjo.client.model;

import esi.bloc3.atlj.skyjo.client.AbstractClient;
import esi.bloc3.atlj.skyjo.client.fxml.FXMLDisplayController;
import esi.bloc3.atlj.skyjo.messages.Message;
import esi.bloc3.atlj.skyjo.messages.MessageProfile;
import esi.bloc3.atlj.skyjo.users.User;
import esi.bloc3.atlj.skyjo.messages.Type;
import esi.bloc3.atlj.skyjo.model.Facade;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Observer;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * The <code> SkyjoClient </code> contains all the methods necessary to set up a
 * Instant messaging client.
 */
public class SkyjoClient extends AbstractClient {

    private User mySelf;
    public Facade game;
    private List<Observer> observers;
    private static Stage waitWindow;
    private boolean waiting;

    /**
     * Constructs the client. Opens the connection with the server. Sends the
     * user name inside a <code> MessageProfile </code> to the server. Builds an
     * empty list of users.
     *
     * @param host the server's host name.
     * @param port the port number.
     * @param name the name of the user.
     * @param password the password needed to connect.
     * @throws IOException if an I/O error occurs when opening.
     */
    public SkyjoClient(String host, int port, String name, String password
    ) throws IOException {
        super(host, port);
        observers = new ArrayList<Observer>();
        waitWindow = null;
        waiting = false;
        openConnection();
        updateName(name, password);
    }

    @Override
    protected synchronized void handleMessageFromServer(Object msg) {
        try {
            Message message = (Message) msg;
            Type type = message.getType();
            switch (type) {
                case PROFILE:
                    setMySelf(message.getAuthor());
                    notifyChange(message);
                    break;
                case SEND_MODEL:
                    waiting = false;
                    Platform.runLater(new Runnable() {
                        @Override
                        public void run() {
                            if (waitWindow != null) {
                                waitWindow.close();
                            }
                        }
                    });
                    game = (Facade) message.getContent();
                    notifyChange(game);
                    break;
                case WAIT:
                    waiting = true;
                    try {
                        FXMLLoader waitLoader = new FXMLLoader();
                        waitLoader.setLocation(getClass().getResource("/fxml"
                                + "/FXMLWaitForOpponent.fxml"));
                        Parent root;
                        root = waitLoader.load();
                        Scene waitScene = new Scene(root);
                        Platform.runLater(() -> {
                            waitWindow = new Stage();
                            waitWindow.setScene(waitScene);
                            waitWindow.show();
                        });

                    } catch (IOException ex) {
                        Logger.getLogger(SkyjoClient.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    break;
                case END:
                    Platform.runLater(() -> {
                        FXMLDisplayController.displayMessage
                                = "Un joueur s'est déconnecté\n\n "
                                + "La partie est terminée!";
                        FXMLDisplayController displayCtrl = new FXMLDisplayController();
                        displayCtrl.start();
                        Platform.exit();
                    });
                    quit();
                    break;
                case EXISTING_PSEUDO:
                    showMessage((String) message.getContent());
                    notifyChange(message);
                case PASSWORD_FALSE:
                    showMessage((String) message.getContent());
                    notifyChange(message);
                case EXISTING_CONNECTION:
                    showMessage((String) message.getContent());
                    notifyChange(message);
                default:
                    throw new IllegalArgumentException("Message type unknown " + type);
            }
            setChanged();
            notifyObservers(message);
        } catch (IOException ex) {
            Logger.getLogger(SkyjoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Calls platform run later to show messages window with a message from the
     * server
     *
     * @param message from the server
     */
    private void showMessage(String message) {
        Platform.runLater(() -> {
            FXMLDisplayController.displayMessage
                    = message;
            FXMLDisplayController displayCtrl
                    = new FXMLDisplayController();
            displayCtrl.start();
        });
    }

    /**
     * Quits the client and closes all aspects of the connection to the server.
     *
     * @throws IOException if an I/O error occurs when closing.
     */
    public void quit() throws IOException {
        closeConnection();
    }

    /**
     * Return the user.
     *
     * @return the user.
     */
    public User getMySelf() {
        return mySelf;
    }

    /**
     * Setter for the user
     *
     * @param user the actual user
     */
    void setMySelf(User user) {
        this.mySelf = user;
    }

    /**
     * Updates a SkyjoClient name
     *
     * @param name the new name to apply
     * @param password the password used for login
     * @throws IOException
     */
    private void updateName(String name, String password) throws IOException {
        sendToServer(new MessageProfile(0, name, password));
        notifyObservers();
    }

    /**
     * Retruns if the client is waiting for opponent
     *
     * @return waiting
     */
    public boolean isWaiting() {
        return waiting;
    }

    /**
     * Updates the model from the server
     *
     * @param model changed model from other player
     */
    private void notifyChange(Facade model) {
        game = model;
        setChanged();
        notifyObservers();
    }

    /**
     * Updates the view with a message from the server example game over message
     * or eventual errot message
     *
     * @param msg is a message from the server mainly
     */
    private void notifyChange(Message msg) {
        setChanged();
        notifyObservers(msg);

    }

    @Override
    public synchronized void addObserver(Observer o) {
        observers.add(o);
    }

    /**
     * Overiden from Observable super class and its purpose is to notify the
     * observers in the REVERSE order For the View observers ViewFx wich
     * contains an alert window, wich is a blocking instance, is normaly added
     * in the first position folowing the flow of the instances construction's
     * needs to be loggicaly notified when every other has been notified
     */
    @Override
    public void notifyObservers() {
        var listIterator = observers.listIterator(observers.size());
        while (listIterator.hasPrevious()) {
            var obs = listIterator.previous();
            obs.update(this, game);
        }
    }

    /**
     * Gets the model that the server sent to all of the players
     *
     * @return the model
     */
    public Facade getInitialModel() {
        return game;
    }

}
