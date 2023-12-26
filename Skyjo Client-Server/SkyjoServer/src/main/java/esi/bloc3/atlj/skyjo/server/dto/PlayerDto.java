package esi.bloc3.atlj.skyjo.server.dto;

import esi.bloc3.atlj.skyjo.server.exception.DtoException;

/**
 *
 * @author jlc
 */
public class PlayerDto extends EntityDto<Integer>{
    
    private String pseudo;
    private String password;
    private String nbPlayed;
    private String nbWin;

    /**
     * constructeur d'un user persistant
     *
     * @param id
     * @param pseudo
     * @param password
     * @param nbPlayed
     * @param nbWin
     * @throws DtoException
     */
    public PlayerDto(int id, String pseudo, String password, 
            String nbPlayed, String nbWin) throws DtoException {
        this.pseudo = pseudo;
        this.password = password;
        this.id = id;
        this.nbPlayed = nbPlayed;
        this.nbWin = nbWin;
    }
    
    public PlayerDto(String pseudo, String password) throws DtoException {
        this.pseudo = pseudo;
        this.password = password;
        this.id = 0;
    }

    public String getNbPlayed() {
        return nbPlayed;
    }

    public String getNbWin() {
        return nbWin;
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
     * @param pseudo
     */
    public void setPseudo(String pseudo) {
        this.pseudo = pseudo;
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
     * @param password
     */
    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "[PlayerDto] (" + getId() + ") " + getPseudo() + " " + getPassword();
    }

}
