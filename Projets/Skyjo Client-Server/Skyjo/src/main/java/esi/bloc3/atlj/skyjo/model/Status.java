package esi.bloc3.atlj.skyjo.model;

import java.io.Serializable;

/**
 * Represents the statuses that the model can be set in this enums also have the
 * messages that the model can use to notify the status bar
 *
 * @author Christophe Rische
 */
public enum Status implements Serializable{
    /**
     * Pick a card stage the user has the choice of picking the random card deck
     * or the discard deck
     */
    PICK_OPTION("tirez une carte au hasard ou échanger une de vos cartes "
            + "avec celle de la defausse"),
    /**
     * Status that the game is in if the player picked the discard card option
     */
    PICKED_DISCARD("veuillez maintenant échanger la carte de la defausse "
            + "avec une de vos cartes"),
    /**
     * Status that the game is in if the player picked the random card option
     */
    PICKED_SHUFFLED("voulez-vous défausser cette carte ou "
            + "échanger cette carte avec une de vos cartes ?"),
    /**
     * is a status that gets updated whenever the player decides to put his
     * random card on the discard deck
     */
    SWAP_DISCARD_SHUFFLE(""),
    /**
     * Coming from the SWAP_DISCARD_SHUFFLE state the player is prompted to
     * choose a card within his card board
     */
    DISCARD_SHUFFLED("veuillez choisir une carte non retournée parmis "
            + "vos cartes"),
    /**
     * Reveals a card within the players board of cards
     */
    REVEAL_CARD("veuillez reveler une carte parmis les votres !"),
    /**
     * Is a status that indicates that the game is officialy over
     */
    GAME_OVER("Partie terminée terminée !"),
    /**
     * Is a status that indicated the the shuffled deck is already emptied
     */
    SHUFFLED_EMPTY("La pile est vide !");
    private String message;

    private Status(String message) {
        this.message = message;
    }

    @Override
    public String toString() {
        return this.message;
    }

}
