package esi.bloc3.atlj.skyjo.client.gui;

import esi.bloc3.atlj.skyjo.model.Card;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.scene.layout.GridPane;

/**
 * Represents the 12 buttons per player in an array that the adequate model
 * classes need to have registered as observers
 *
 * @author Christophe Rische
 */
public class PlayerFx extends GridPane {

    private final CardFx[][] cards;

    private final PlayerScoreFx score;

    /**
     * Constructs a 12 button gridpane with a score bat thaat spans over 4 cells
     *
     * @param ps is the PlayerScore label to be associated with this instance
     */
    public PlayerFx(PlayerScoreFx ps) {
        this.score = ps;
        GridPane.setHalignment(ps, HPos.CENTER);
        setPadding(new Insets(5));
        setHgap(20);
        setVgap(20);
        add(ps, 0, 0, 4, 1); // a label spans over the lenght of 4 cards
        this.cards = new CardFx[3][4];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                cards[i][j] = new CardFx(i, j);
            }
        }
        int row = 0;
        int column = 0;
        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                add(cards[row % 3][column++ % 4], j, i);
            }
            row++;
        }
    }

    /**
     * Update the cardFx instance based on the 2D card array
     *
     * @param cards is the 2D array to read from to update the buttons
     * @param clear if this option is provided the method makes sure to reset
     * cards that are suppose to be hidden
     */
    public void updateCards(Card[][] cards, boolean clear) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                var card = cards[i][j];
                if (!card.isHidden()) {
                    this.cards[i][j].giveValue(card.getValue());
                } else if (clear) {
                    this.cards[i][j].reset();
                }
            }
        }
    }

    /**
     * Simply Gets the 2D card represented by buttons
     *
     * @return 2D array
     */
    public CardFx[][] getCards() {
        return cards;
    }

    /**
     * Simplu calls the score method of the playerScore class and relays the int
     * score
     *
     * @param score an integer representing the score
     */
    public void setScore(int score) {
        this.score.setScore(score);
    }

}
