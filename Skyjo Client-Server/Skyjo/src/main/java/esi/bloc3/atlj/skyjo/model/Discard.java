package esi.bloc3.atlj.skyjo.model;

import java.io.Serializable;
import java.util.Stack;

/**
 * Represents the discard where cards get placed and taken from. Note that in
 * the contrary of a Deck class the Discard class,starts empty until it gets
 * it's first card inserted when the game starts, and then the Model manages
 * card swap's between the currently players Card's or the Deck
 *
 * @author Christophe Rische
 */
public class Discard implements Serializable{

    private final Stack<Card> discard;

    /**
     * Innitialises a empty stack at first
     */
    public Discard() {
        this.discard = new Stack();
    }

    /**
     * Inserts a card in the discard's stack, and requires them to be unhidden
     * when put on the top of the discard
     *
     * @param card reference to the card from the players cards and
     */
    public void insertCard(Card card) {
        if (card == null) {
            throw new IllegalArgumentException("No card to "
                    + "insert in the discard");
        }
        card.setHidden(false); // unhides card of player deck
        discard.push(card);
    }

    /**
     * Allows us to take a card off the discard stack note that in the flow of
     * the game the discard is never supposed to be empty
     *
     * @return the reference to the card, so that we can do a swap
     */
    public Card takeCard() {
        return discard.pop();
    }

    /**
     * Only looks at the top of the discard's stack and ensures a defensive copy
     *
     * @return the card copy
     */
    public final Card lookTopCard() {
        return new Card(discard.peek());
    }

}
