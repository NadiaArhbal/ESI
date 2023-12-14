package model;

import View.Observer;
import View.Observable;
import java.util.ArrayList;
import java.util.List;

/**
 * Class representing a card
 * @author Arhbal
 */
public class Card implements Observable {

    private int val;
    private boolean visible;
    private List<Observer> listObserver;

    /**
     * Public constructor that create a card
     * @param val the value of the card
     */
    public Card(int val) {
        if (val > 12 && val < -2) {
            throw new IllegalArgumentException("The val of the card is incorrect");
        }
        this.val = val;
        this.visible = false;
        this.listObserver = new ArrayList<>();
    }

    /**
     * Getter of the val
     * @return the value of the card
     */
    public int getVal() {
        return val;
    }
    
    /**
     * Setter of val
     * @param val the val
     */
    public void setVal(int val) {
        this.val = val;
    }

    /**
     * ToString method 
     * @return a string corresponding to a card
     */
    @Override
    public String toString() {
        return val + "";
    }

    /**
     * Checking if the face of my card is revealed or not
     * @return true if the face and revealed otherwise not
     */
    public boolean isVisible() {
        return visible;
    }


    /**
     * Setter of visible
     * @param visible visibility of the face of my card
     */
    public void setVisible(boolean visible) {
        this.visible = visible;
    }

    /**
     * Add a observer in our observer list
     * @param obs the observer that we want to add
     */
    @Override
    public void registerObserver(Observer obs) {
        this.listObserver.add(obs);
    }

    /**
     * Remove the observer
     * @param obs observer it that we want to delete
     */
    @Override
    public void removeObserver(Observer obs) {
        this.listObserver.remove(obs);
    }

    /**
     * Method updating each observer from our observer list
     */
    @Override
    public void notifyObservers() {
        for (Observer observer : listObserver) {
            observer.update();
        }
    }

}
