package esi.bloc3.atlj.skyjo.users;

import java.io.Serializable;
import java.net.InetAddress;


/**
 * The <code> User </code> represents a connected user.
 */
public class User implements Serializable {
    public static final User ADMIN  = new User(0, "ADMIN");
    public static final User PROFILE  = new User(0, "PROFILE");
    public static final User EVERYBODY  = new User(0, "EVERYBODY");
    
    private final int id;
    private String name;
    private InetAddress address;
    private String password;
    /**
     * Constructs a connected user.
     *
     * @param id userID of the connected user.
     * @param name name of the connected user.
     * @param password password of the connected user.
     */
    public User(int id, String name, String password, InetAddress address) {
        this.name = name;
        this.id = id;
        this.password = password;
        this.address = address;
        
    }
    
      public User(int id, String name, String password) {
        this.name = name;
        this.id = id;
        this.password = password;   
    }
      
      public User(int id, String name) {
        this.name = name;
        this.id = id;
    }

    /**
     * Return the user name.
     *
     * @return the user name.
     */
    public String getName() {
        return name;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 37 * hash + this.id;
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final User other = (User) obj;
        return this.id == other.id;
    }

    public boolean isThisInstance(int id) {
        return this.id == id;
    }

    /**
     * Return the userID.
     *
     * @return the userID.
     */
    public int getId() {
        return id;
    }

    /**
     * Setter for the User's name
     * 
     * @param name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }


}