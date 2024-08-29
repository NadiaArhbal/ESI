package esi.bloc3.atlj.skyjo.model;

import java.io.Serializable;
import java.util.Observer;

/**
 * Defines all the methods that the model will have to implement
 *
 * @author chris
 */
public interface Facade  {

    /**
     * Initializes the game by giving the discard a card and all the two players
     * card 24 total cards then tha Randomizer generate indexes method is called
     * so that we can call the show method at the generated indexes
     */
    public void start();

    /**
     * Is responsible for the deck reset, discard emptying and player reset
     */
    public void restart();

    /**
     * Registers an observer to the model
     *
     * @param obs observer to add
     */
    public void registerObserver(Observer obs);

    /**
     * Simply gets the card at the top of the shuffled cards deck This does not
     * remove the card from the top of the deck !
     *
     * @return the card
     */
    public Card getDiscard();

    /**
     * Simply gets the card at the top of the shuffled cards deck this does not
     * remove the card from the top of the deck !
     *
     * @return the card
     */
    public Card getShuffle();

    /**
     * Simply gets the current player of the game initialy
     *
     * @return the current player in form of a boolean true player 1 and false
     * player 2
     */
    public boolean getPlayer();

    /**
     * Is received by the controller whenever it decides to change statuses
     * statuses are changed accordingly based on previous statuses 
     * and one status is prone to failure it is the PICK_SHUFFLE if 
     * the deck has been emptied (the users might do that ! ) 
     * 
     * @param st status that the controller wants to give the model
     */
    public void updateStatus(Status st);

    /**
     * Handles a card of a specific player based on the current status. This
     * method be used if we want to replace the card of a player, with the
     * discard or the shuffle top deck card OR alternatively just show a card of
     * a player if the status says so
     *
     * @param row row
     * @param column column
     */
    public void handleCard(int row, int column);

    /**
     * Simply returns the current status of the model
     *
     * an enum has a status message that can be treated accordingly from
     * the GUI
     * @return current status of the model
     */
    public Status getStatus();

    /**
     * Gets the score of the current playing player
     *
     * @return the score in question
     */
    public int getScore();
    
    public boolean getWinner(); //TODO
    
    /**
     * Gets the score of the choosen player
     *
     * @param player indicated wich player we cant to get
     * @return the score of the selected player
     */
    public int getScore(boolean player);

    /**
     * Gets the cards of the current playing player
     *
     * @return 2D array
     */
    public Card[][] getCards();

    /**
     * Gets the cards of the choosen playing player
     *
     * @param player specifies wich player we want to get the cards from
     * @return 2D array
     */
    public Card[][] getCards(boolean player);
}
