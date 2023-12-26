package esi.bloc3.atlj.skyjo.client.gui;

import esi.bloc3.atlj.skyjo.model.Status;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;

/**
 * Representes the status bar where the model will comunicate with the player by
 * setting a text to the label
 *
 * @author Christophe Rische
 */
public class StatusBarFx extends Label {

    private String current;

    /**
     * Simply builds the white rectangular status bar that centers status text
     * coming from the model
     */
    public StatusBarFx() {
        setFont(new Font("Arial", 20));
        setStyle("-fx-background-color: #ffffff;");
        setMaxWidth(Double.MAX_VALUE);
        setTextAlignment(TextAlignment.CENTER);
        setAlignment(Pos.CENTER);
    }

    /**
     * Sets the text of the status bar based on the status of the model if the
     * game is over then the player part is not appended
     *
     * @param st current status
     */
    public void setStatus(Status st) {
        if (st != Status.GAME_OVER || st != Status.SHUFFLED_EMPTY) {
            setText(current + st);
        } else {
            setText("" + st);
        }
    }

    /**
     * Updates the string representing the current player, and assignes it to
     * current
     *
     * @param player true if player 1 and else 2
     */
    public void updatePlayer(boolean player) {
        current = player ? "Joueur 1 : " : "Joueur 2 : ";
    }

}
