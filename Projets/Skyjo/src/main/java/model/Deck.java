package model;

import View.Observer;
import View.Observable;
import java.util.ArrayList;
import java.util.List;

/**
 * Class representing the 150 cards including 12 per person
 * @author Arhbal
 */
public class Deck implements Observable {
    
    private final List<Card>cards;
    private final List<Observer>observers;
    
    /**
     * Constructor deck
     */
    public Deck() {
        this.cards = new ArrayList<>();
        this.observers=new ArrayList<>();
    }
    
    /**
     * Checking if our card list is empty or not
     * @return true if the list is empty otherwise no
     */
    public boolean isEmpty(){
        return cards.isEmpty();
    }

    /**
     * Getter of cards 
     * @return the card list
     */
    public List<Card> getCards() {
        return cards;
    }

    /**
     * Get the first card of the deck of cards
     * @return the first card
     */
    public Card getFirstCard(){
        return cards.get(0);
    }
    
    /**
     * Adds a card to our cards list
     * @param card 
     */
    public void addCard(Card card){
        cards.add(0,card);
    }
    
    /**
     * Allows you to remove the first card
     * @return the deleted card
     */
    public Card removeFirstCard(){
        return cards.remove(0);
    }
    
    /**
     * Add a observer to our observers list
     * @param obs the observer
     */
    @Override
    public void registerObserver(Observer obs) {
       this.observers.add(obs);
    }

    /**
     * Remove a observer to our observers list
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
