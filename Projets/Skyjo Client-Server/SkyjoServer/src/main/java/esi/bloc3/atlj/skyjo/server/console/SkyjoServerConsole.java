package esi.bloc3.atlj.skyjo.server.console;

import esi.bloc3.atlj.skyjo.messages.Message;
import esi.bloc3.atlj.skyjo.server.controller.Controller;
import esi.bloc3.atlj.skyjo.server.model.SkyjoServer;
import esi.bloc3.atlj.skyjo.users.User;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.Observable;
import java.util.Observer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Console version of the SkyjoServer
 * 
 * @author Christophe Rische
 */
public class SkyjoServerConsole implements Observer {
 
    private final SkyjoServer model;

    /**
     * Constructs the console view. Subscribes to the instant messaging server.
     *
     * @param model instant messaging server.
     */
    public SkyjoServerConsole(SkyjoServer model) throws IOException {
        this.model = model;
    }

    @Override
    public void update(Observable o, Object arg) {
        updateUser();
        if (arg != null) {
            Message message = (Message) arg;
            updateMessage(message);
        }

    }

    /**
     * Displays on console the connected User's list
     */
    private void updateUser() {
        System.out.println("");
        StringBuilder builder = new StringBuilder();
        builder.append("\n---- ---- Liste Users ---- ----\n");
        builder.append("Nombre d'utilisateurs connectes : ")
                .append(model.getNbConnected()).append("\n");
        builder.append("ID").append("\t");
        builder.append("NAME").append("\n");
        for (User player : model.getPlayers()) {
            builder.append(player.getId()).append("\t");
            builder.append(player.getPassword()).append("\t");
            builder.append(player.getName()).append("\n");
        }    
        System.out.println(builder);
        System.out.println("");
    }

    /**
     * Displays on console a message with details
     * 
     * @param message to display 
     */
    private void updateMessage(Message message) {
        StringBuilder builder = new StringBuilder();
        builder.append("\n---- ---- Message recu ---- ----\n");
        builder.append(LocalDateTime.now()).append(" \n");
        builder.append("Type : ").append(message.getType().toString()).append("\n");
        builder.append("De : ").append(message.getAuthor().toString()).append("\t");
        builder.append("Pour : ").append(message.getRecipient().toString()).append("\n");
        builder.append("Contenu\t").append(message.getContent().toString());
        builder.append("\n");
        System.out.println(builder);
    }
}

