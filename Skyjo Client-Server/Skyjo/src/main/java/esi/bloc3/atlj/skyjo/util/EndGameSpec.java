package esi.bloc3.atlj.skyjo.util;

import java.io.Serializable;

/**
 * Is used to specify the arguments that can be sent to the server via message
 * when a game finishes so that it can be stored in DB
 *
 * @author Christophe Rische
 */
public class EndGameSpec implements Serializable {

    private final int winner;
    private final int winnerScore;
    private final int loserScore;

    /**
     * Constructs a endgame based on the winner not in boolean form but in int
     * and also gives winner score and loser score
     *
     * @param winner an integer either 1 or 2 based on the player ID if
     * implemented in a client server architecture
     * @param winnerScore the winner's score
     * @param loserScore the losers's score
     */
    public EndGameSpec(int winner, int winnerScore,
            int loserScore) {
        this.winner = winner;
        this.winnerScore = winnerScore;
        this.loserScore = loserScore;
    }

    /**
     * Simply gets the score of the losing player
     *
     * @return score in form of integer
     */
    public int getLoserScore() {
        return loserScore;
    }

    /**
     * Simply gets the winning player
     *
     * @return score in the form of a integer
     */
    public int getWinner() {
        return winner;
    }

    /**
     * Simply gets the score of the winning player
     *
     * @return score in form of integer
     */
    public int getWinnerScore() {
        return winnerScore;
    }

}
