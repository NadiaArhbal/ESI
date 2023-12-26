package esi.bloc3.atlj.skyjo.messages;

import esi.bloc3.atlj.skyjo.model.Facade;
import esi.bloc3.atlj.skyjo.users.User;

/**
 * This message is used by the server to send the model to a client
 * 
 * @author reda-
 */
public class MessageSendModel implements Message {
    private final Facade game;
    private final User author;
    private final User recipient;
   
    /**
     * Constructs a sendModel Message with the needed parameter for the client
     *
     * @param user the author.
     * @param recipient user name of the author.
     * @param game the game to display
     */
    public MessageSendModel(User user, User recipient, Facade game) {
        this.author = user;
        this.recipient = recipient;
        this.game = game;
    }
    
    @Override
    public Type getType() {
        return Type.SEND_MODEL;
    }

    @Override
    public User getAuthor() {
        return author;
    }

    @Override
    public User getRecipient() {
        return recipient;
    }

    @Override
    public Object getContent() {
        return game;
    }
}
