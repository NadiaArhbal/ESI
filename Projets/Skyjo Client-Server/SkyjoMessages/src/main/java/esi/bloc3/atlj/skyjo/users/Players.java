package esi.bloc3.atlj.skyjo.users;

import java.io.Serializable;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 * The <code> Players </code> represents a list of all connected users.
 */
public class Players implements Iterable<User>, Serializable {

    private final List<User> users;
    private Map<User, Integer> response;

    /**
     * Constructs an empty list of users.
     *
     */
    public Players() {
        users = new ArrayList<>();
        response = new HashMap<>();
    }

    /**
     * Creates a new instance of an user and add this user to the list.
     *
     * @param id userID of the new user.
     * @param name name of the new user.
     * @param address
     * @param password password of the new user.
     * @return the userID of the new user.
     */
    public int add(int id, String name,InetAddress address, String password) {
        User user = new User(id, name, password, address);
        response.put(new User(id, name, password, address),0);
        add(user);
        return user.getId();
    }

    /**
     * Add a user to the list of connected users.
     *
     * @param user user connected.
     */
    public void add(User user) {
        response.put(user, 0);
        users.add(user);
    }

    /**
     * Remove the user with the current userID from the list of connected users.
     *
     * @param id userID of the user disconnected.
     */
    public void remove(int id) {
        Iterator<User> it = users.iterator();
        boolean find = false;
        User current = null;
        while (it.hasNext() && !find) {
            current = it.next();
            find = current.isThisInstance(id);
        }
        if (find) {
            response.remove(current);
            users.remove(current);
        }
    }

    /**
     * Return the number of users connected.
     *
     * @return the number of users connected.
     */
    public int size() {
        return users.size();
    }

    /**
     * Clear the list of connected users.
     */
    public void clear() {
        users.clear();
    }

    @Override
    public Iterator<User> iterator() {
        return users.iterator();
    }

    /**
     * Return the user of the given id.
     *
     * @param id userdId of the user to return.
     * @return the user of the given id.
     */
    public User getUser(int id) {
        Iterator<User> it = users.iterator();
        boolean find = false;
        User current = null;
        while (it.hasNext() && !find) {
            current = it.next();
            find = current.isThisInstance(id);
        }
        return find ? current : null;
    }

    /**
     * Update the name of a user.
     *
     * @param name new value of the name.
     * @param id userId of the user to update.
     */
    public void changeName(String name, int id) {
        User user = getUser(id);
        if (user != null) {
            user.setName(name);
        }
    }
    
    /**
     * gets the name of a player
     * @param id based on id of 1 or 2
     * @return the name form of string
     */
    public String getName(int id) {
       User user = getUser(id);
       return user.getName();
    }
}
