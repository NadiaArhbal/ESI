package esi.bloc3.atlj.skyjo.server.specification;

/**
 *
 * @author jlc
 */
public class PlayerSpecification {

    private final int id;
    private final String pseudo;
    private final String password;
    private int nbPlayed;
    private int nbWin;

    /**
     *
     * @param id
     * @param login
     * @param name
     */
    public PlayerSpecification(int id, String login, String name) {
        this.id = id;
        this.pseudo = login;
        this.password = name;
        this.nbPlayed = 0;
        this.nbWin = 0;
    }

    /**
     * Specification only based on the login name
     *
     * @param login is the login string that is currently playing
     */
    public PlayerSpecification(String login) {
        this.id = 0;
        this.pseudo = login;
        this.password = "";
        this.nbPlayed = 0;
        this.nbWin = 0;
    }

    /**
     *
     * @return
     */
    public int getId() {
        return id;
    }

    /**
     *
     * @return
     */
    public String getPseudo() {
        return pseudo;
    }

    /**
     *
     * @return
     */
    public String getPassword() {
        return password;
    }

    /**
     *
     * @return
     */
    public int getNbPlayed() {
        return nbPlayed;
    }

    /**
     *
     */
    public void plusOneNbPlayer() {
        nbPlayed++;
    }

    /**
     *
     * @return
     */
    public int getNbWin() {
        return nbWin;
    }

}
