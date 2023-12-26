package esi.bloc3.atlj.skyjo.server.specification;

/**
 *
 * @author Jonathan Lenders (53188)
 */
public class GameSpecification {
    
    private final int gameID;
    private final int player1ID;
    private final int player2ID;
    private int winner;

    public GameSpecification(int gameID, int player1ID, int player2ID) {
        this.gameID = gameID;
        this.player1ID = player1ID;
        this.player2ID = player2ID;
        this.winner = 0;
    }

    /**
     * 
     * @return 
     */
    public int getGameID() {
        return gameID;
    }
    
    /**
     * 
     * @return 
     */
    public int getPlayer1ID() {
        return player1ID;
    }

    /**
     * 
     * @return 
     */
    public int getPlayer2ID() {
        return player2ID;
    }

    /**
     * 
     * @return 
     */
    public int getWinner() {
        return winner;
    }

    /**
     * 
     * @param winner 
     */
    public void setWinner(int winner) {
        this.winner = winner;
    }
    
    
}
