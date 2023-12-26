package esi.bloc3.atlj.skyjo.messages;

import esi.bloc3.atlj.skyjo.users.User;

/**
 * MessageWait is a message used by the server to make the client wait for his
 * opponent
 *
 * @author guill
 */
public class MessageWait implements Message {
    private final User author;
    private final User recipient;

    /**
     * Constructs a Wait Message with the needed parameter for the client
     *
     * @param user the author.
     * @param recipient user name of the author.
     */
    public MessageWait(User user, User recipient) {
        this.author = user;
        this.recipient = recipient;
    }

    @Override
    public Type getType() {
        return Type.WAIT;
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
        return author;
    }

}
