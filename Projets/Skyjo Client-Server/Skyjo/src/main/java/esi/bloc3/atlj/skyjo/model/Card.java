package esi.bloc3.atlj.skyjo.model;

import java.io.Serializable;

/**
 * A card can hold values from -2 to 12
 *
 * @author chris
 */
public final class Card implements Serializable {

    private final int value;
    private boolean hidden;

    /**
     * Simply constructs the card that is currently not visivle to anyone at a
     * given value
     *
     * throws expection if value is incorrect !
     *
     * @param value the value we want to intitialize the value at
     */
    public Card(int value) {
        if (value < -2 || value > 12) {
            throw new IllegalArgumentException("A card cant hold that value !");
        }
        this.value = value;
        this.hidden = true;
    }   
    
    /**
     * Copy constructor to be able to get a defensive copy system for 
     * method 
     * Note that it also has to get its hidden state or else when we attempt
     * to return a copy of card we wont be able to set its appropriate state
     * @param toCopy instance to copy
     */
    public Card(Card toCopy) {
        this(toCopy.getValue());
        this.hidden = toCopy.hidden;
    }

    /**
     * Simply gets the value of the current card
     *
     * @return an integer
     */
    public int getValue() {
        return value;
    }

    /**
     * Simply tells us if the card is hidden or not
     *
     * @return a boolean representing the card status
     */
    public boolean isHidden() {
        return hidden;
    }

    /**
     * Sets the status of the card from hidden to unhiden and vice versa
     *
     * @param hidden a boolean representing the staus of the card
     */
    public void setHidden(boolean hidden) {
        this.hidden = hidden;
    }

}
