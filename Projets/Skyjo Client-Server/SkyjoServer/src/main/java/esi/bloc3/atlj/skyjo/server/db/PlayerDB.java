package esi.bloc3.atlj.skyjo.server.db;

import esi.bloc3.atlj.skyjo.messages.Message;
import esi.bloc3.atlj.skyjo.server.dto.PlayerDto;
import esi.bloc3.atlj.skyjo.server.exception.BusinessException;
import esi.bloc3.atlj.skyjo.server.exception.DbException;
import esi.bloc3.atlj.skyjo.server.exception.DtoException;
import esi.bloc3.atlj.skyjo.server.specification.PlayerSpecification;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author jlc
 */
public class PlayerDB {

    private static final String recordName = "PLAYER";

    /**
     *
     * @param id
     * @throws DbException
     */
    public static void deleteDb(int id) throws DbException {
        try {
            java.sql.Statement stmt = DBManager.getConnection().createStatement();
            stmt.execute("delete from PLAYER where id=" + id);
        } catch (Exception ex) {
            throw new DbException(recordName + ": suppression impossible\n" + ex.getMessage());
        }
    }

    /**
     *
     * @param record
     * @throws DbException
     */
    public static void updateDb(PlayerDto record) throws DbException {
        try {
            java.sql.Connection connexion = DBManager.getConnection();

            java.sql.PreparedStatement update;
            String sql = "Update PLAYER set "
                    + "pseudo=?, "
                    + "password=? "
                    + "where id=?";
            update = connexion.prepareStatement(sql);
            update.setString(1, record.getPseudo());
            update.setString(2, record.getPassword());
            update.setInt(3, record.getId());
            update.executeUpdate();
        } catch (Exception ex) {
            throw new DbException(recordName + ", modification impossible:\n" + ex.getMessage());
        }
    }

    /**
     *
     * @param record
     * @throws DbException
     */
    public static int insertDb(PlayerDto record) throws DbException {
        try {
            int num = SequenceDB.getNextNum(SequenceDB.PLAYER);
            java.sql.Connection connexion = DBManager.getConnection();
            java.sql.PreparedStatement insert;
            insert = connexion.prepareStatement(
                    "Insert into PLAYER(playerID, pseudo, password) "
                    + "values(?, ?, ? )");
            insert.setInt(1, num);
            insert.setString(2, record.getPseudo());
            insert.setString(3, record.getPassword());
            insert.executeUpdate();
            return num;
        } catch (Exception ex) {
            throw new DbException(recordName + ": pseudo existe déjà\n" + ex.getMessage());
        }
    }

    public static boolean selectPasswordDb(PlayerDto record) throws DbException {
        java.sql.Connection connexion = DBManager.getConnection();
        String sql = "SELECT password FROM PLAYER WHERE password = ? AND pseudo = ?";
        try (PreparedStatement pstmt = connexion.prepareStatement(sql)) {
            pstmt.setString(1, record.getPassword());
            pstmt.setString(2, record.getPseudo());
            ResultSet rs = pstmt.executeQuery();
            int count = 0;
            if (rs.next()) {
                return true;
            }
        } catch (Exception ex) {
            throw new DbException(recordName + ": connexion impossible\n" + ex.getMessage());
        }
        return false;
    }

//    public static Message errorDatabase(PlayerDto record) throws DbException {
//        String sql = "SELECT playerID FROM STUDENTS WHERE playerID = ?";
//        java.sql.PreparedStatement select = null;
//        java.sql.Connection connexion = DBManager.getConnection();
//        try (Statement stmt = connexion.createStatement();
//                ResultSet rs = stmt.executeQuery(sql)) {
//        } catch (SQLException ex) {
//            throw new DbException(recordName+": player already exist\n" + ex.getMessage());
//        }
//    }
    //faire une methode sur un attribut particulier un boolean active par exemple
    /**
     *
     * @param sel
     * @return
     * @throws DbException
     */
    public static List<PlayerDto> getCollection(PlayerSpecification sel) throws DbException {
        List<PlayerDto> al = new ArrayList<>();
        try {
            String query = "Select playerID, pseudo, password, nbPlayed, nbWin"
                    + " FROM PLAYER ";
            java.sql.Connection connexion = DBManager.getConnection();
            java.sql.PreparedStatement stmt;
            String where = "";

            if (sel.getPseudo() != null && !sel.getPseudo().isEmpty()) {
                where = where + " pseudo like ? ";
            }

            if (sel.getPassword() != null && !sel.getPassword().isEmpty()) {
                if (!where.isEmpty()) {
                    where = where + " AND ";
                }
                where = where + " password like ? ";
            }
            if (sel.getNbPlayed() != 0) {
                if (!where.isEmpty()) {
                    where = where + " AND ";
                }
                where = where + " nbPlayed = ? ";
            }
            if (sel.getNbWin() != 0) {
                if (!where.isEmpty()) {
                    where = where + " AND ";
                }
                where = where + " nbWin = ? ";
            }
            if (where.length() != 0) {
                where = " where " + where + " order by pseudo";
                query = query + where;
                stmt = connexion.prepareStatement(query);
                int i = 1;
                if (sel.getId() != 0) {
                    stmt.setInt(i, sel.getId());
                    i++;
                }
                if (sel.getPseudo() != null && !sel.getPseudo().isEmpty()) {
                    stmt.setString(i, sel.getPseudo() + "%");
                    i++;
                }
                if (sel.getPassword() != null && !sel.getPassword().isEmpty()) {
                    stmt.setString(i, sel.getPassword() + "%");
                    i++;
                }
            } else {
                query = query + " Order by pseudo";;
                stmt = connexion.prepareStatement(query);
            }
            java.sql.ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                al.add(new PlayerDto(rs.getInt("playerID"),
                        rs.getString("pseudo"), rs.getString("password"),
                        rs.getString("nbPlayed"), rs.getString("nbWin")));
            }
        } catch (DtoException ex) {
            throw new DbException("Instanciation de " + recordName + " impossible:\nDTOException: " + ex.getMessage());
        } catch (java.sql.SQLException eSQL) {
            throw new DbException("Instanciation de " + recordName + " impossible:\nSQLException: " + eSQL.getMessage());
        }
        return al;
    }
}
