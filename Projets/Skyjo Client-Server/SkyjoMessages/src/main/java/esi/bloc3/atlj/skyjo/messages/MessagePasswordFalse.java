/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package esi.bloc3.atlj.skyjo.messages;

import esi.bloc3.atlj.skyjo.users.User;

/**
 *
 * @author reda-
 */
public class MessagePasswordFalse implements Message {
        private final User recipient;

    /**
     * Constructs message with the profile of a specific user.The author of the
            message give his profile to be send.
     *
     * @param id userID of the author.
     * @param name user name of the author.
     * @param password password of the author
     */
    public MessagePasswordFalse(int id, String name) {
        recipient = new User(id, name);
    }

    /**
     * Return the author of the message. The author send his profile.
     *
     * @return the author of the message.
     */
    @Override
    public User getAuthor() {
        return User.ADMIN;
    }

    /**
     * Return the recipient of this message. A profile message is always send to
     * the administrator.
     *
     * @return the recipient of this message.
     */
    @Override
    public User getRecipient() {
        return recipient;
    }

    /**
     * Return the type of the message, in this case Type.PROFILE.
     *
     * @return the type of the message, in this case Type.PROFILE.
     */
    @Override
    public Type getType() {
        return Type.PASSWORD_FALSE;
    }

    /**
     * Return the content of the message : the author profile.
     *
     * @return the content of the message : the author profile.
     */
    @Override
    public Object getContent() {
        return "Le mot de passe est erroné";
    }
}
