package esi.bloc3.atlj.skyjo.server.business;

import esi.bloc3.atlj.skyjo.server.db.PlayerDB;
import esi.bloc3.atlj.skyjo.server.dto.PlayerDto;
import esi.bloc3.atlj.skyjo.server.exception.DbException;
import esi.bloc3.atlj.skyjo.server.specification.PlayerSpecification;
import java.util.Collection;
import java.util.List;

public class PlayerBusinessLogic {

    /**
     * Insert an player in the database. Returns the player's id.
     *
     * @param pseudo player's pseudo.
     * @param name player's name.
     * @return the player's id.
     * @throws SQLException if the query failed.
     */
    static int add(PlayerDto player) throws DbException {
        return PlayerDB.insertDb(player);
    }
    
    static boolean selectPassword(PlayerDto player) throws DbException {
        return PlayerDB.selectPasswordDb(player);
    }

    /**
     * Removes the given player.
     *
     * @param player player to delete.
     * @throws SQLException if the query failed.
     */
    static void delete(int id) throws DbException {
        PlayerDB.deleteDb(id);
    }

    /**
     * Updates the given player.
     *
     * @param player player to update.
     * @throws SQLException if the query failed.
     */
    static void update(PlayerDto player) throws DbException {
        PlayerDB.updateDb(player);
    }

    /**
     * Returns the unique player with the given pseudo.
     *
     * @param id player's pseudo.
     * @return the id of the user
     * @throws SQLException if the query failed.
     */
    static int findByPseudo(String pseudo) throws DbException {
        PlayerSpecification plSpec = new PlayerSpecification(pseudo);
        Collection<PlayerDto> col = PlayerDB.getCollection(plSpec);
        if (col.size() == 1) {
            return col.iterator().next().getId();
        } else {
            return 0;
        }
    }

    /**
     * Returns the unique player with the given id.
     *
     * @param id player's id.
     * @return the unique player with the given id.
     * @throws SQLException if the query failed.
     */
    static PlayerDto findById(int id) throws DbException {
        PlayerSpecification sel = new PlayerSpecification(id, null, null);
        Collection<PlayerDto> col = PlayerDB.getCollection(sel);
        if (col.size() == 1) {
            return col.iterator().next();
        } else {
            return null;
        }
    }
}
