package esi.bloc3.atlj.skyjo.server.dto;

import esi.bloc3.atlj.skyjo.server.exception.DtoException;

/**
 *
 * @author Jonathan Lenders (53188)
 */
public class GameDto extends EntityDto<Integer> {

    private int winner;
    private int player1ID;
    private int player2ID;
    private int winnerScore;
    private int loserScore;

    public GameDto(int id, int player1ID, int player2ID) throws DtoException {
        this.id = 0;
        if (player1ID == 0 || player2ID == 0) {
            throw new DtoException("les attributs player1ID "
                    + "et player2ID sont obligatoires");
        }
        this.player1ID = player1ID;
        this.player2ID = player2ID;
        this.winner = 0;
    }

    public GameDto(int player1ID, int player2ID, int winner,
            int winnerScore, int loserScore) throws DtoException {
        this.id = 0;
        if (player1ID == 0 || player2ID == 0) {
            throw new DtoException("les attributs player1ID "
                    + "et player2ID sont obligatoires");
        }
        this.player1ID = player1ID;
        this.player2ID = player2ID;
        this.winner = winner;
        this.winnerScore = winnerScore;
        this.loserScore = loserScore;
    }

    public int getWinner() {
        return winner;
    }

    public int getPlayer1ID() {
        return player1ID;
    }

    public Integer getID() {
        return id;
    }

    public int getPlayer2ID() {
        return player2ID;
    }

    public int getWinnerScore() {
        return winnerScore;
    }

    public int getLoserScore() {
        return loserScore;
    }

}
