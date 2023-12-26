package esi.bloc3.atlj.skyjo.model;

import esi.bloc3.atlj.skyjo.util.Randomizer;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.EmptyStackException;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

/**
 * Is the model of the MVC model, all methods are defined in Facade and or thus
 * the ones that interract with the View components in the e GUi
 *
 * @author Christophe Rische
 */
public class Model extends Observable implements Serializable, Facade {

    private Deck deck;
    private Discard discard;
    private Player player_1;
    private Player player_2;
    private boolean currentPlayer; //Replace with enum of statuses
    private List<Observer> observers;
    private Status status;

    /**
     * Initializes just the unshuflled deck and players without any cards for
     * now
     */
    public Model() {
        this.deck = new Deck();
        this.player_1 = new Player();
        this.player_2 = new Player();
        this.observers = new ArrayList<>();
        this.discard = new Discard();
    }

    public Model(Model copy) {
        this.deck = copy.deck;
        this.discard = copy.discard;
        this.player_1 = copy.player_1;
        this.player_2 = copy.player_2;
        this.status = copy.status;
        this.currentPlayer = copy.currentPlayer;
        this.observers = new ArrayList<>();
    }

    @Override
    public void start() {
        deck.shuffle();
        discard.insertCard(deck.draw());
        player_1.initCards(deck.playerInit());
        player_2.initCards(deck.playerInit());
        int[] player_1_indexes = Randomizer.generateIndexes();
        int[] player_2_indexes = Randomizer.generateIndexes();
        player_1.showCard(player_1_indexes[0], player_1_indexes[2]);
        player_1.showCard(player_1_indexes[1], player_1_indexes[3]);
        player_2.showCard(player_2_indexes[0], player_2_indexes[2]);
        player_2.showCard(player_2_indexes[1], player_2_indexes[3]);
        this.currentPlayer = player_1.getScore() == player_2.getScore()
                ? Randomizer.randomPlayer()
                : player_1.getScore() < player_2.getScore();
        this.status = Status.PICK_OPTION;
        notifyObservers();
    }

    @Override
    public void restart() {
        this.deck = new Deck();
        this.discard = new Discard();
        this.player_1 = new Player();
        this.player_2 = new Player();
        start();
    }

    @Override
    public Card getDiscard() {
        return discard.lookTopCard();
    }

    @Override
    public Card getShuffle() {
        return deck.lookTopCard();
    }

    @Override
    public boolean getPlayer() {
        return this.currentPlayer;
    }

    /**
     * Reveals the card based on the given coordinates of one player this only
     * can happen if we are at a appropriate stage of the game
     *
     * @param row index of the card in question
     * @param column indes of the card in question
     * @return true if we revealed a card that was not already shown and false
     * if not
     */
    private boolean revealCard(int row, int column) {
        return currentPlayer ? player_1.showCard(row, column)
                : player_2.showCard(row, column);
    }

    /**
     * Replaces a card of one player based on the given coordinates with the
     * discard, shuffle deck
     *
     * @param row index of the card in question
     * @param column indes of the card in question
     */
    private void replaceCard(int row, int column) {
        var current = currentPlayer ? player_1 : player_2;
        if (status == Status.PICKED_DISCARD) {
            discard.insertCard(current
                    .replaceCard(row, column, discard.takeCard()));
        } else {
            discard.insertCard(current.replaceCard(row,
                    column, deck.draw()));
        }
        changePlayer();
    }

    /**
     * Simply replaces a card from the shuffled deck to the dicard an sets the
     * status to REVEAL_CARD, so that the player can reveal a card
     */
    private void replaceCard() {
        discard.insertCard(deck.draw());
    }

    @Override
    public void updateStatus(Status st) {
        if (status == Status.PICKED_SHUFFLED && st == Status.PICKED_DISCARD) {
            replaceCard(); //clicked deck and then discard
            this.status = Status.REVEAL_CARD;
        } else if (st == Status.PICKED_SHUFFLED) {
            try {
                deck.revealCard();
                this.status = Status.PICKED_SHUFFLED;
            } catch (EmptyStackException e) {
                this.status = Status.SHUFFLED_EMPTY;
            }
        } else { // picked discard
            this.status = st;
        }
        notifyObservers();
    }

    @Override
    public Status getStatus() {
        return status;
    }

    @Override
    public void handleCard(int row, int column) {
        if (status == Status.REVEAL_CARD) {
            if (revealCard(row, column)) {
                //change of player only hidden card picked
                changePlayer();
            }
        } else if (status == Status.PICKED_DISCARD
                || status == Status.PICKED_SHUFFLED) {
            replaceCard(row, column); //procceeds to player card replacement
        }
        notifyObservers();
    }

    /**
     * Is reponsible of the change of the current player with conditions the win
     * conditions are that if the opposite player that has just revealed all of
     * his cards has a positive score and that his score is greater or equal to
     * the current player that is playing his finishing turn. Then in that case
     * we multiply the opponent score by two and set the winner as the
     * currentPlayer
     */
    private void changePlayer() {
        if (checkAllCards()) { //ending game
            int opnScore;
            //get the opponent score 
            if ((opnScore = getScore(!currentPlayer)) > 0) {
                if ((opnScore >= getScore())) {
                    opnScore = doubleScore(); //double score of opponent
                }
                currentPlayer = opnScore >= getScore() ? currentPlayer
                        : !currentPlayer;
            }
            status = Status.GAME_OVER; //sets to game over
        } else {
            status = Status.PICK_OPTION; //reverts to pick option 
            currentPlayer = !currentPlayer; // changes player
        }
    }

    @Override
    public int getScore() {
        return currentPlayer ? player_1.getScore() : player_2.getScore();
    }

    @Override
    public Card[][] getCards() {
        return currentPlayer ? player_1.getCards() : player_2.getCards();
    }

    @Override
    public Card[][] getCards(boolean player) {
        return player ? player_1.getCards() : player_2.getCards();
    }

    @Override
    public void registerObserver(Observer obs) {
        if (obs == null) {
            throw new IllegalArgumentException("No observers given !");
        }
        observers.add(obs);
    }

    /**
     * Overiden from Observable super class and its purpose is to notify the
     * observers in the REVERSE order For the View observers ViewFx wich
     * contains an alert window, wich is a blocking instance, is normaly added
     * in the first position folowing the flow of the instances construction's
     * needs to be loggicaly notified when every other has been notified
     */
    @Override
    public void notifyObservers() {
        var listIterator = observers.listIterator(observers.size());
        while (listIterator.hasPrevious()) {
            var obs = listIterator.previous();
            obs.update(this, null);
        }
    }

    @Override
    public int getScore(boolean player) {
        return player ? player_1.getScore() : player_2.getScore();
    }

    /**
     * Sets the score of the opposing player in case it has a equal or greater
     * score than the currently playing player
     *
     * @return the doubled score of the opposing player
     */
    private int doubleScore() {
        return currentPlayer ? player_2.doubleScore() : player_1.doubleScore();
    }

    /**
     * This method checks if the opposing player has had all of his cards
     * returned
     *
     * @return true if card counter reached 0
     */
    private boolean checkAllCards() {
        return currentPlayer ? player_2.turnedAll() : player_1.turnedAll();
    }

    @Override
    public boolean getWinner() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

}
