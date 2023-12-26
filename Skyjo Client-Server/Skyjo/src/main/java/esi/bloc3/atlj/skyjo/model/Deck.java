package esi.bloc3.atlj.skyjo.model;

import java.io.Serializable;
import java.util.Collections;
import java.util.Stack;

/**
 * Holds 150 specific cards, e.g 10 -2 cards 10 -1 cards ... until 12
 *
 * @author Christophe Rische
 */
public class Deck implements Serializable {

    private final Stack<Card> deck;

    /**
     * Simply initializes the deck that is holding 150 specific cards, e.g 10 -2
     * cards 10 -1 cards ... until 12
     */
    public Deck() {
        this.deck = new Stack(); //allocates 150 card list
        for (int i = -2; i < 13; i++) {
            for (int j = 0; j < 10; j++) { //10 cards per value
                deck.push(new Card(i));
            }
        }
    }

    /**
     * Simply shuffles the list using the shuffle method of Collections
     */
    public void shuffle() {
        Collections.shuffle(deck);
    }

    /**
     * Simply gets the card at the last index of the list like its the top of
     * the deck
     *
     * @return the card reference to realize a swap with players card or a
     * simple oneway exchange to the discard
     */
    public Card draw() {
        return deck.pop();
    }

    /**
     * Gets the card situated at top of the deck, wich implies that we want to
     * reveal the card on top
     *
     * @return a card
     */
    public final Card lookTopCard() {
        return new Card(deck.peek());
    }

    /**
     * Reveals the card at the top of the deck, only if its hidden note that if
     * the stack has been emptied and that we try to peek an empty stack it
     * throws an expection
     */
    public void revealCard() {
        var topCard = deck.peek();
        if (topCard.isHidden()) {
            topCard.setHidden(false);
        }
    }

    /**
     * Initializes the 12 card array for a player at the start of the game
     * Eventually we will have an option to restart the game so might be
     * called again
     * @return a 2D Array containing all the 12 cards that a player needs
     */
    public Card[][] playerInit() {
        Card[][] cards = new Card[3][4];
        int rowIndex = 0;
        for (int columnIndex = 0; columnIndex < 12; columnIndex++) {
            if (columnIndex != 0 && columnIndex % 4 == 0) {
                rowIndex++;
            }
            cards[rowIndex][columnIndex % 4] = deck.pop();
        }
        return cards;
    }

}
