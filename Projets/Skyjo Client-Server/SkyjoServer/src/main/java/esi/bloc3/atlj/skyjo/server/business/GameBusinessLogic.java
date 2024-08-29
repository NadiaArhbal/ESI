package esi.bloc3.atlj.skyjo.server.business;

import esi.bloc3.atlj.skyjo.server.db.GameDB;
import esi.bloc3.atlj.skyjo.server.dto.GameDto;
import esi.bloc3.atlj.skyjo.server.exception.DbException;
import esi.bloc3.atlj.skyjo.server.specification.GameSpecification;
import java.util.Collection;
import java.util.List;

/**
 *
 * @author Jonathan Lenders (53188)
 */
public class GameBusinessLogic {
    /**
     * Insert an game in the database. Returns the game's id.
     * 
     * @return the game's id.
     * @throws SQLException if the query failed.
     */
    static int add(GameDto game) throws DbException {
        return GameDB.insertDb(game);
    }

    /**
     * Removes the given game.
     * 
     * @param id the game's id.
     * @throws DbException if the query failed.
     */
    static void delete(int id) throws DbException {
        GameDB.deleteDb(id);
    }

    /**
     * Updates the given game.
     *
     * @param game the game to update.
     * @throws SQLException if the query failed.
     */
    static void update(GameDto game) throws DbException {
        GameDB.updateDb(game);
    }

    /**
     * Returns the unique game with the given id.
     *
     * @param id game's id.
     * @return the unique game with the given id.
     * @throws SQLException if the query failed.
     */
    static GameDto findById(int id) throws DbException {
        GameSpecification gameSpec = new GameSpecification(id, 0, 0);
        Collection<GameDto> col = GameDB.getCollection(gameSpec);
        if (col.size() == 1) {
            return col.iterator().next();
        } else {
            return null;
        }
    }

}
