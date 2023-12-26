package esi.bloc3.atlj.skyjo.messages;

import esi.bloc3.atlj.skyjo.users.User;
import esi.bloc3.atlj.skyjo.util.EndGameSpec;

/**
 * Is responsible for the sending of the arguments of and ending game
 * such as winning player losing score winning score contained on EndGameSpec
 * object
 * @author Christophe Rische
 */
public class MessageSendEndGame implements Message {

    private final User author;
    private final EndGameSpec endgame;
    
    /**
     * Constructs a message
     * @param author
     * @param endgame 
     */
    public MessageSendEndGame(User author, EndGameSpec endgame) {
        this.author = author;
        this.endgame = endgame;
    }

    @Override
    public Type getType() {
        return Type.SEND_ENDGAME;
    }

    @Override
    public User getAuthor() {
        return author;
    }

    @Override
    public User getRecipient() {
        return User.ADMIN;
    }

    @Override
    public Object getContent() {
        return endgame;
    }

}
