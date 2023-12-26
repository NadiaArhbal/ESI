package esi.bloc3.atlj.skyjo.model;

import java.io.Serializable;
import java.util.Arrays;

/**
 * Represents a player that is folding 12 cards that are suceptible to change
 * based on the players action Every player has multiple observers, where their
 * position in the array matches the card array A player also has a score
 * observer that is updated when a cards get revealed or replaced
 *
 * @author chris
 */
public final class Player implements Serializable {

    private Card[][] cards;
    private int score;
    private int hiddenCards;

    /**
     * Constructs at first empty card and score at 0
     */
    public Player() {
        this.cards = null; //needs to be initialized in method
        this.score = 0;
        this.hiddenCards = 12; // 2 cards are gonna get revealed later on
    }

    /**
     * Simply initializes the cards of the player with the given parameter
     *
     * @param cards a 12 card 2D array
     */
    public void initCards(Card[][] cards) {
        this.cards = cards;
    }

    /**
     * This method allows us to show a card at a given index of the array it
     * also throws an exception in case we try to show a card that is already
     * been shown
     *
     * @param row repreesents the row where we need to find the card at
     * @param column represents the column where we need to find the card at
     * @return true if the card was returned and false if the card is already
     * shown
     */
    public boolean showCard(int row, int column) {
        if (cards[row][column].isHidden()) {
            cards[row][column].setHidden(false);
            this.score += cards[row][column].getValue();
            hiddenCards--;
        } else {
            return false;
        }
        return true;
    }

    /**
     * Simply return the value off
     *
     * @return an integer representing the current score
     */
    public int getScore() {
        return this.score;
    }

    /**
     * Simply Doubles this instance score of the player
     *
     * @return sets the score of the player but also returns the doubled score
     * fro indicative reasons
     */
    public int doubleScore() {
        score *= 2;
        return score;
    }

    /**
     * Simply Gets the copy of a card array
     *
     * @return a 2D card array copy to respect defensive copy idiome
     */
    public Card[][] getCards() {
        return Arrays.stream(cards).map(Card[]::clone).toArray(Card[][]::new);
    }

    /**
     * Replaces a card at given index and returns the card that is not in the
     * array anymore that needs to be put in the discard deck. Scores are
     * updated according the the exiting and entering cards values Note that if
     * the card
     *
     * @param row of the array to find the card to replace
     * @param column of the array to find the card to replace
     * @param card the subsitute card that could be comming from discard or
     * shuffled deck
     * @return the card that is replaced by the one in parameters
     */
    public Card replaceCard(int row, int column, Card card) {
        if (card == null) {
            throw new IllegalArgumentException("No card has been given "
                    + "for replacement !");
        }
        Card temp = cards[row][column];
        if (temp.isHidden()) {
            hiddenCards--; //if card to swap was hidden
        } else {
            this.score -= temp.getValue(); // substract from score
        }
        cards[row][column] = card;
        this.score += card.getValue();
        return temp;
    }

    /**
     * Checks if there is no hidden cards anymore
     *
     * @return true if no more cards
     */
    public boolean turnedAll() {
        return hiddenCards == 0;
    }
}
