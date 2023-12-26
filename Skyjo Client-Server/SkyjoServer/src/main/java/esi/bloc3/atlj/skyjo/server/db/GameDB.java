package esi.bloc3.atlj.skyjo.server.db;

import esi.bloc3.atlj.skyjo.server.dto.GameDto;
import esi.bloc3.atlj.skyjo.server.exception.DbException;
import esi.bloc3.atlj.skyjo.server.exception.DtoException;
import esi.bloc3.atlj.skyjo.server.specification.GameSpecification;
import java.util.ArrayList;
import java.util.List;

/**
 * Classe d'accès au gestionnaire de persistance pour les Joueurs
 */
public class GameDB {

    //TODO
    static final String GAME = "GAME";

    public static List<GameDto> getAllGames() throws DtoException, DbException {
        List<GameDto> games = getCollection(new GameSpecification(0, 0, 0));
        return games;
    }

    public static List<GameDto> getCollection(GameSpecification plSpec) throws DbException {
        List<GameDto> al = new ArrayList<>();
        try {
            String query = "Select gameID, player1ID, player2ID FROM GAME ";
            java.sql.Connection connexion = DBManager.getConnection();
            java.sql.PreparedStatement stmt;
            String where = "";
            if (plSpec.getGameID() != 0) {
                where = where + " gameID = ? ";
            }
            if (plSpec.getPlayer1ID() != 0) {
                if (!where.isEmpty()) {
                    where = where + " AND ";
                }
                where = where + " player1ID = ? ";
            }

            if (plSpec.getPlayer2ID() != 0) {
                if (!where.isEmpty()) {
                    where = where + " AND ";
                }
                where = where + " player2ID = ? ";
            }

            if (where.length() != 0) {
                where = " where " + where + " order by gameID";
                query = query + where;
                stmt = connexion.prepareStatement(query);
                int i = 1;
                if (plSpec.getGameID() != 0) {
                    stmt.setInt(i, plSpec.getGameID());
                    i++;

                }
                if (plSpec.getPlayer1ID() != 0) {
                    stmt.setInt(i, plSpec.getPlayer1ID());
                    i++;
                }
                if (plSpec.getPlayer2ID() != 0) {
                    stmt.setInt(i, plSpec.getPlayer2ID());
                    i++;
                }
            } else {
                query = query + " Order by gameID";
                stmt = connexion.prepareStatement(query);
            }
            java.sql.ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                al.add(new GameDto(rs.getInt("gameID"),
                        rs.getInt("player1ID"), rs.getInt("player2ID")));
            }
        } catch (DtoException ex) {
            throw new DbException("Instanciation de " + GAME + " impossible:\nDTOException: " + ex.getMessage());
        } catch (java.sql.SQLException eSQL) {
            throw new DbException("Instanciation de " + GAME + " impossible:\nSQLException: " + eSQL.getMessage());
        }
        return al;
    }

    public static void deleteDb(int id) throws DbException {
        try {
            java.sql.Statement stmt = DBManager.getConnection().createStatement();
            stmt.execute("delete from GAME where id=" + id);
        } catch (Exception ex) {
            throw new DbException(GAME + ": suppression impossible\n" + ex.getMessage());
        }
    }

    public static void updateDb(GameDto record) throws DbException {
        try {
            java.sql.Connection connexion = DBManager.getConnection();
            java.sql.PreparedStatement update;
            String sql = "Update GAME set "
                    + "gameID=?, "
                    + "player1ID=? "
                    + "player2ID=? "
                    + "where gameID=?";
            update = connexion.prepareStatement(sql);
            update.setInt(1, record.getID());
            update.setInt(2, record.getPlayer1ID());
            update.setInt(3, record.getPlayer2ID());
            update.executeUpdate();
        } catch (Exception ex) {
            throw new DbException(GAME + ", modification impossible:\n" + ex.getMessage());
        }
    }

    public static int insertDb(GameDto record) throws DbException {
        try {
            int num = SequenceDB.getNextNum(SequenceDB.GAME);
            java.sql.Connection connexion = DBManager.getConnection();
            java.sql.PreparedStatement insert;
            insert = connexion.prepareStatement(
                    "Insert into GAME (gameID, playerID1, playerID2, winner"
                    + ", winnerScore, loserScore) "
                    + "values(?, ?, ?, ?, ?, ?)");
            insert.setInt(1, num);
            insert.setInt(2, record.getPlayer1ID());
            insert.setInt(3, record.getPlayer2ID());
            insert.setInt(4, record.getWinner());
            insert.setInt(5, record.getWinnerScore());
            insert.setInt(6, record.getLoserScore());
            insert.executeUpdate();
            return record.getID();
        } catch (Exception ex) {
            throw new DbException(GAME + ": ajout impossible\n" + ex.getMessage());
        }
    }

}
