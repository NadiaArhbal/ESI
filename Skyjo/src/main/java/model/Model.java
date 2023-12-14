package model;

/**
 * The interface Model
 * 
 * @author Arhbal
 */
public interface Model {
    
    public Player getPlayer1();
    public Player getPlayer2();
    public Deck getPioche();
    public Deck getDefausse(); 
    
    public void setStatus(State status);
    public void initGame();
    public void start();
    public void reveal(Player player);
    
    public Card firstCardPioche();
    public Card firstCardDefausse();
}
