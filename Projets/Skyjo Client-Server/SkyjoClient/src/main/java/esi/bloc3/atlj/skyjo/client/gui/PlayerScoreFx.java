package esi.bloc3.atlj.skyjo.client.gui;

import javafx.scene.control.Label;
import javafx.scene.text.Font;

/**
 * Represents the respective players score that gets updated whenerver a card of
 * the repective player gets replaced or shown via the model. We do this with
 * the observer update method the player string like "Joueur 1 : " + the score
 * represented as a double
 *
 * @author Christophe Rische
 */
public class PlayerScoreFx extends Label {

    private final String player;

    /**
     * Creates a score label with custom css propeties and fonts its gets
     * registered as an observer to the obsrvable object passed in parameters
     *
     * @param player indicates the player string to add if we need to update it
     */
    public PlayerScoreFx(String player) {
        this.player = player;
        setFont(new Font("Arial", 25));
        setStyle("-fx-background-color: #f5c242; "
                + "-fx-border-radius: 10 60 60 10;\n"
                + "-fx-background-radius: 10 10 10 10;");
    }

    /**
     * Simply sets the score of a player based on the template string player
     *
     * @param score current score
     */
    public void setScore(int score) {
        setText(player + score);
    }
}
