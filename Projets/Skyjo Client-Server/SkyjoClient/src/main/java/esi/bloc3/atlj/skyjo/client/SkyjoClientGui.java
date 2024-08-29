/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package esi.bloc3.atlj.skyjo.client;

import esi.bloc3.atlj.skyjo.client.gui.TypePlayer;
import esi.bloc3.atlj.skyjo.client.gui.ViewFx;
import esi.bloc3.atlj.skyjo.client.model.SkyjoClient;
import esi.bloc3.atlj.skyjo.messages.Message;
import esi.bloc3.atlj.skyjo.messages.MessageSendEndGame;
import esi.bloc3.atlj.skyjo.messages.MessageSendModel;
import esi.bloc3.atlj.skyjo.model.Facade;
import esi.bloc3.atlj.skyjo.model.Model;
import esi.bloc3.atlj.skyjo.model.Status;
import esi.bloc3.atlj.skyjo.users.User;
import esi.bloc3.atlj.skyjo.util.EndGameSpec;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.stage.Stage;

/**
 * Binds client with the ViewFx wich the game window this is the entry and exit
 * point ftom client -> server and server -> client
 *
 * @author Christophe Rische
 */
public class SkyjoClientGui implements Observer {

    private final SkyjoClient client;
    private ViewFx view;

    /**
     * Constructs the console view.Subscribes to the instant messaging client.
     *
     * @param client instant messaging client.
     * @param stage
     */
    public SkyjoClientGui(SkyjoClient client, Stage stage) {
        this.client = client;
        Model game = (Model) client.getInitialModel();
        client.addObserver(this);
        view = new ViewFx((Observable) game, stage,
                TypePlayer.getType(client.getMySelf().getId()));
        game.notifyObservers();
        game.registerObserver(this);
    }

    @Override
    public void update(Observable o, Object o1) {
        if (o1 == null) {
            Facade facade = new Model((Model) o);
            MessageSendModel msg
                    = new MessageSendModel(client.getMySelf(), User.ADMIN, facade);
            if (facade.getStatus() == Status.GAME_OVER) {
                boolean winner = facade.getPlayer();
                int winnerID = winner ? 1 : 2;
                sendToServer(generateMessage(winnerID, facade.getScore(),
                        facade.getScore(!winner)));
            }
            try {
                client.sendToServer(msg);
            } catch (IOException ex) {
                Logger.getLogger(SkyjoClientGui.class.getName()).log(Level.SEVERE, null, ex);
            }
        } else {
            Model game = (Model) o1;
            Platform.runLater(() -> {
                view.changeModel(game);
                game.notifyObservers();
                game.registerObserver(this);
            });
        }

    }

    /**
     * Simply send a message to server
     *
     * @param msg the abstract version of message
     */
    private void sendToServer(Message msg) {
        try {
            client.sendToServer(msg);
        } catch (IOException ex) {
            Logger.getLogger(SkyjoClientGui.class.getName())
                    .log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Generates a endgame message if endGameCheck returns true based on
     *
     * @param winner the winning player id
     * @return the message instance
     */
    private Message generateMessage(int winner, int wScore,
            int lScore) {
        return new MessageSendEndGame(client.getMySelf(),
                new EndGameSpec(winner, wScore, lScore));
    }

}
