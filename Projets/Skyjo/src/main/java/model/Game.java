package model;

import View.ButtonObserver;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Class representing the necessary for the Skyjo
 * @author Arhbal
 */
public class Game implements Model {

    private final Player player1;
    private final Player player2;
    private Player currPlayer;
    private boolean isFinished;
    private final Deck pioche;
    private final Deck defausse;
    private State status;

    /**
     * Public constructor for game
     */
    public Game() {
        this.player1 = new Player();
        this.player2 = new Player();
        this.pioche = new Deck();
        this.defausse = new Deck();
        this.currPlayer = null;
        this.isFinished = false;
    }

    /**
     * Indicating if a game is finished or not
     * @return true if the game is over and false otherwise
     */
    public boolean isFinished() {
        return isFinished;
    }

    /**
     * Getter of currentplayer
     * @return the currentplayer
     */
    public Player getCurrPlayer() {
        return currPlayer;
    }

    /**
     * Setter of currentplayer
     * @param player the currentplayer
     */
    public void setCurrentPlayer() {
       currPlayer=  currPlayer == player1 ? player2 : player1;
    }

    /**
     * Setter which puts the game over
     */
    public void setIsFinished() {
        this.isFinished = true;
    }

//    /**
//     * Setter of currplayer
//     * @param currPlayer
//     */
//    public void setCurrPlayer(Player currPlayer) {
//        this.currPlayer = currPlayer;
//    }

    /**
     * Getter of player who indicates who is the winner
     * @return player 1 if it's the winner and player 2 otherwise
     */
    public Player getWinner() {
////        return currPlayer.cmptValCardsVisibles() < getOppositePlayer().cmptValCardsVisibles() ? currPlayer : getOppositePlayer();
        return player1.cmptValCardsVisibles() < player2.cmptValCardsVisibles() ? player1 : player2;
    }

    /**
     * Gives us the opposite player of the current player
     * @return the opposite player
     */
    public Player getOppositePlayer() {
        return currPlayer == player1 ? player2 : player1;
    }

    /**
     * Getter of player1
     * @return the player1
     */
    @Override
    public Player getPlayer1() {
        return player1;
    }

    /**
     * Getter of player2
     * @return the player2
     */
    @Override
    public Player getPlayer2() {
        return player2;
    }

    /**
     * Getter of pioche
     * @return the pickaxe
     */
    @Override
    public Deck getPioche() {
        return pioche;
    }

    /**
     * Getter of defausse
     * @return the defausse
     */
    @Override
    public Deck getDefausse() {
        return defausse;
    }

    /**
     * Getter of status
     *
     * @return the status
     */
    public State getStatus() {
        return status;
    }

    /**
     * Setter of status
     * @param status the status
     */
    @Override
    public void setStatus(State status) {
        this.status = status;
    }

    /**
     * Card initialization method
     */
    @Override
    public void initGame() {
        List<Card> listCards = new ArrayList<>();
        int val = 1;
        for (int i = 1; i <= 140; i++) {
            if (i <= 5) {
                listCards.add(new Card(-2));
            } else if (i <= 20) {
                listCards.add(new Card(0));
            } else {

                listCards.add(new Card(val));
                if (i % 10 == 0) {
                    val++;
                }
            }
            if (i <= 10) {
                listCards.add(new Card(-1));
            }
        }
        Collections.shuffle(listCards);
        for (int i = 0; i < 12; i++) {
            player1.addCards(listCards.get(0));
            listCards.remove(0);
        }
        for (int i = 0; i < 12; i++) {
            player2.addCards(listCards.get(0));
            listCards.remove(0);
        }

        pioche.getCards().addAll(listCards);

        defausse.getCards().add(pioche.getFirstCard());
        pioche.removeFirstCard();
    }

    /**
     * Initializes the elements of the beginning of the game
     */
    @Override
    public void start() {
        this.setStatus(State.TAKECARD);
        player1.reveal();
        player1.reveal();
        player2.reveal();
        player2.reveal();

        for (Card card : player1.getCardsPlayer()) {
            card.notifyObservers();
        }
        for (Card card : player2.getCardsPlayer()) {
            card.notifyObservers();
        }
        player1.notifyObservers();
        player2.notifyObservers();
        defausse.getFirstCard().setVisible(true);
        defausse.getFirstCard().notifyObservers();
        pioche.getFirstCard().notifyObservers();
        this.setCurrPlayer(getStartingPlayer());
    }

    public void setCurrPlayer(Player currPlayer) {
        this.currPlayer = currPlayer;
    }

    /**
     * Reveals a card
     * @param player the player
     */
    @Override
    public void reveal(Player player) {
        player.reveal();
    }

    /**
     * Take the first card from the pickaxe
     * @return the first card of the pickaxe
     */
    @Override
    public Card firstCardPioche() {
        return pioche.getFirstCard();
    }

    /**
     * Take the first card from the defausse
     * @return the first card of the defausse
     */
    @Override
    public Card firstCardDefausse() {
        return defausse.getFirstCard();
    }

    /**
     * Indicating the player who starts the game
     * @return the player who starts the game
     */
    public Player getStartingPlayer() {
        if (player1.cmptValCardsVisibles() > player2.cmptValCardsVisibles()) {
            return player1;
        } else if (player1.cmptValCardsVisibles() == player2.cmptValCardsVisibles()) {
            return ((int) Math.random() * 2 % 2) == 0 ? player2 : player1;
        } else {
            return player2;
        }
    }

    /**
     * Exchanges a player's card with a card from the deck
     * @param id the player's card id
     * @param deck the deck with which we exchange the card
     */
    public void swapCard(int id, Deck deck) {
        getCurrPlayer().getCardsPlayer().get(id).setVisible(true);
        int value = getCurrPlayer().getCardsPlayer().get(id).getVal();
        getCurrPlayer().getCardsPlayer().get(id).setVal(firstCardDefausse().getVal());
        deck.getFirstCard().setVal(value);
        deck.getFirstCard().notifyObservers();
        currPlayer.notifyObservers();
        for (Card card : currPlayer.getCardsPlayer()) {
            card.notifyObservers();
        }
    }

    /**
     * Doubles the score of the player who finished first if he has the highest score
     */
    public void setFinalScore() {
        if (this.isFinished()) {
            if (currPlayer.cmptValCardsVisibles() >= this.getOppositePlayer().cmptValCardsVisibles()
                    && currPlayer.cmptValCardsVisibles() >= 0) {
                for (Card card : currPlayer.getCardsPlayer()) {
                    card.setVal(card.getVal()*2);
                }
            }
        }
    }

    /**
     * Performs the steps when in defausse mode
     * @param id the id of the card
     */
    public void playDefausse(int id) {
        this.swapCard(id, defausse);
        currPlayer.getCardsPlayer().get(id).notifyObservers();
        this.setCurrentPlayer();
        this.setStatus(State.TAKECARD);
    }

    /**
     * Performs the steps when in discard mode
     * @param id the id of the card
     */
    public void playDiscard(int id) {
        if (!currPlayer.getCardsPlayer().get(id).isVisible()) {
            currPlayer.getCardsPlayer().get(id).setVisible(true);
            currPlayer.getCardsPlayer().get(id).notifyObservers();
            this.setStatus(State.TAKECARD);
            this.setCurrentPlayer();
        }
    }

    /**
     * Indicates whether the pickaxe is empty or not
     * @return true if the pickaxe is empty and false otherwise
     */
    public boolean isPiocheEmpty() {
        return pioche.isEmpty();
    }

    /**
     * Adds the first card from the pickaxe to the defausse
     * @param pioche the pickaxe
     * @param def the defausse
     */
    public void addFirstCardPiocheOnDef(ButtonObserver pioche, ButtonObserver def) {
        this.defausse.getCards().add(0, this.pioche.getFirstCard());
        this.pioche.removeFirstCard();
        pioche.setCard(this.pioche.getFirstCard());
        this.defausse.getFirstCard().registerObserver(def);
        def.setCard(this.defausse.getFirstCard());
        this.pioche.notifyObservers();
        this.defausse.getFirstCard().notifyObservers();
        this.setStatus(State.DISCARD);
        
    }

}
