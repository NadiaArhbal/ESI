package esi.bloc3.atlj.skyjo.server.business;

import esi.bloc3.atlj.skyjo.server.dto.PlayerDto;
import esi.bloc3.atlj.skyjo.server.exception.BusinessException;

/**
 * Administrator facade.
 */
public interface AdminFacade {

    /**
     * Returns the unique player with the given id.
     *
     * @param id player's id.
     * @return the unique player with the given id.
     * @throws BusinessException
     */
    PlayerDto getPlayer(int id) throws BusinessException;

    /**
     * Returns the last player with the given pseudo.
     *
     * @param pseudo player's pseudo.
     * @return the id at given pseudo
     * @throws BusinessException
     */
    int getPlayerID(String pseudo) throws BusinessException;

    /**
     * Creates a player and insert it in the database
     *
     * @param pseudo player's pseudo.
     * @param pwd player's password.
     * @throws BusinessException
     */
    void addPlayer(String pseudo, String pwd) throws BusinessException;

    /**
     * Creates a game and inserts it in the database
     *
     * @param playerID1 id of the first player
     * @param playerID2 id of the second player
     * @param winner id of the winning player
     * @param winnerScore score of the winner
     * @param loserScore score of the loser
     * @return ID of the inserted tuple in GAME table
     * @throws BusinessException
     */
    int addGame(int playerID1, int playerID2, int winner, int winnerScore,
            int loserScore)
            throws BusinessException;

    /**
     * Removes the given player.
     *
     * @param player player to delete.
     * @throws BusinessException
     */
    void removePlayer(PlayerDto player) throws BusinessException;

    /**
     * Updates the given player.
     *
     * @param current player to update
     * @throws BusinessException
     */
    void updatePlayer(PlayerDto current) throws BusinessException;

    public boolean selectPassword(String playerPseudo, String playerPwd)
            throws BusinessException;

}
