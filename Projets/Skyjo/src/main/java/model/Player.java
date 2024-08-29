package model;

import View.Observer;
import View.Observable;
import java.util.ArrayList;
import java.util.List;

/**
 * Class representing a player
 * @author Arhbal
 */
public class Player implements Observable {

    private final List<Card> cardsPlayer;
    private int score;
    private boolean winner;
    private final List<Observer> observers;

    /**
     * Constructor of player
     */
    public Player() {
        cardsPlayer = new ArrayList<>();
        this.score = 0;
        this.winner = false;
        this.observers = new ArrayList<>();
    }

    /**
     * Card list getter
     * @return the list of cards
     */
    public List<Card> getCardsPlayer() {
        return cardsPlayer;
    }

    /**
     * Getter of score
     * @return the score
     */
    public int getScore() {
        return score;
    }

    /**
     * Check whether the player is a winner or not
     * @return true if the player wins otherwise no
     */
    public boolean isWinner() {
        return winner;
    }

    /**
     * Setter of score
     * @param score the score
     */
    public void setScore(int score) {
        this.score = score;
    }

    /**
     * Setter of winner
     * @param winner the status of the player
     */
    public void setWinner(boolean winner) {
        this.winner = winner;
    }

    /**
     * Add card on the deck 
     * @param card the card
     */
    public void addCards(Card card) {
        cardsPlayer.add(card);
    }

    /**
     * Returning for each player 2 cards randomly
     */
    public void reveal() {
        int index = (int) (Math.random() * 12);
        if (!this.cardsPlayer.get(index).isVisible()) {
            this.cardsPlayer.get(index).setVisible(true);
        } else {
            while (this.cardsPlayer.get(index).isVisible()) {
                index = (int) (Math.random() * 12);
            }
            this.cardsPlayer.get(index).setVisible(true);
        }
    
    }

    /**
     * Adds up the value of visible cards
     * @return the value of all visible cards
     */
    public int cmptValCardsVisibles() {
        int cmpt = 0;
        for (Card card : cardsPlayer) {
            if (card.isVisible()) {
                cmpt += card.getVal();
            }
        }
        return cmpt;
    }
    
    /**
     * Indicates if all of the player's cards are visible
     * @return true if all the player's cards are visible and false otherwise
     */
    public boolean allCardsVisible(){
        for (Card card : cardsPlayer) {
            if (!card.isVisible()) {
                return false;
            }
        }
        return true;
    }

    /**
     * Register the observers
     * @param obs the observer
     */
    @Override
    public void registerObserver(Observer obs) {
        this.observers.add(obs);
    }

    /**
     * Remove the observers
     * @param obs the observer
     */
    @Override
    public void removeObserver(Observer obs) {
        this.observers.remove(obs);
    }

    /**
     * Update the observers
     */
    @Override
    public void notifyObservers() {
        for (Observer observer : observers) {
            observer.update();
        }
    }
}
