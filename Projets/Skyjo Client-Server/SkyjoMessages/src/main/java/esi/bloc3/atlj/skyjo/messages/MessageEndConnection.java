package esi.bloc3.atlj.skyjo.messages;

import esi.bloc3.atlj.skyjo.users.User;

/**
 * This message is used by the server to stop a client when one of the two
 * players disconnects from the game
 * 
 * @author guill
 */
public class MessageEndConnection implements Message{
    private final User author;
    private final User recipient;
    
    /**
     * Constructs an END message 
     *
     * @param user the author.
     * @param recipient user name of the author.
     */
    public MessageEndConnection(User user, User recipient){
        this.author = user;
        this.recipient = recipient;
    }

    @Override
    public Type getType() {
        return Type.END;
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
        return recipient;
    }
    
}
