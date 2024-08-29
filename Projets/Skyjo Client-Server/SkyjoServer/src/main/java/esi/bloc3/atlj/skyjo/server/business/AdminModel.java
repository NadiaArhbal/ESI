package esi.bloc3.atlj.skyjo.server.business;

import esi.bloc3.atlj.skyjo.server.db.DBManager;
import esi.bloc3.atlj.skyjo.server.dto.GameDto;
import esi.bloc3.atlj.skyjo.server.dto.PlayerDto;
import esi.bloc3.atlj.skyjo.server.exception.BusinessException;
import esi.bloc3.atlj.skyjo.server.exception.DbException;
import esi.bloc3.atlj.skyjo.server.exception.DtoException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Collections;
import java.util.List;

/**
 * Run the program fr the administrator.
 */
public class AdminModel implements AdminFacade {

    private static final String URL = "jdbc:sqlite:resources/sqliteDB/SkyjoDB";
    private static final String PLAYER_DB = "app";
    private static final String PASSWORD = "app";
    static final String PLAYERS = "PLAYERS";
    static final String GAME = "GAME";

    static int getNextNum(String sequence) throws SQLException {
        Connection connexion = DriverManager.getConnection(URL, PLAYER_DB, PASSWORD);
        String query = "Update SEQUENCES set sValue = sValue+1 where id='" + sequence + "'";
        java.sql.PreparedStatement update = connexion.prepareStatement(query);
        update.execute();
        java.sql.Statement stmt = connexion.createStatement();
        query = "Select sValue FROM Sequences where id='" + sequence + "'";
        java.sql.ResultSet rs = stmt.executeQuery(query);
        int nvId;
        if (rs.next()) {
            nvId = rs.getInt("sValue");
            return nvId;
        } else {
            throw new IllegalStateException("Nouveau n° de séquence inaccessible!");
        }
    }

    @Override
    public PlayerDto getPlayer(int id) throws BusinessException {
        try {
            DBManager.startTransaction();
            PlayerDto player = PlayerBusinessLogic.findById(id);
            DBManager.validateTransaction();
            return player;
        } catch (DbException eDB) {
            String msg = eDB.getMessage();
            try {
                DBManager.cancelTransaction();
            } catch (DbException ex) {
                msg = ex.getMessage() + "\n" + msg;
            } finally {
                throw new BusinessException("Liste des Players inaccessible! \n" + msg);
            }
        }
    }

    @Override
    public int getPlayerID(String playerPseudo) throws BusinessException {
        try {
            DBManager.startTransaction();
            int playerID = PlayerBusinessLogic.findByPseudo(playerPseudo);
            DBManager.validateTransaction();
            return playerID;
        } catch (DbException eDB) {
            String msg = eDB.getMessage();
            try {
                DBManager.cancelTransaction();
            } catch (DbException ex) {
                msg = ex.getMessage() + "\n" + msg;
            } finally {
                throw new BusinessException("Liste des Players inaccessible! \n" + msg);
            }
        }
    }

    @Override
    public void addPlayer(String playerPseudo, String playerPwd) throws BusinessException {
        try {
            DBManager.startTransaction();
            PlayerDto player = new PlayerDto(playerPseudo, playerPwd);
            PlayerBusinessLogic.add(player);
            DBManager.validateTransaction();
        } catch (DbException | DtoException ex) {
            try {
                DBManager.cancelTransaction();
                throw new BusinessException(ex.getMessage());
            } catch (DbException ex1) {
                throw new BusinessException(ex1.getMessage());
            }
        }
    }

    @Override
    public int addGame(int playerID1, int playerID2, int winner, int winnerScore,
             int loserScore) throws BusinessException {
        try {
            DBManager.startTransaction();
            GameDto player = new GameDto(playerID1, playerID2, winner, winnerScore,loserScore);
            int gameID = GameBusinessLogic.add(player);
            DBManager.validateTransaction();
            return gameID;
        } catch (DbException | DtoException ex) {
            try {
                DBManager.cancelTransaction();
                throw new BusinessException(ex.getMessage());
            } catch (DbException ex1) {
                throw new BusinessException(ex1.getMessage());
            }
        }
    }

    @Override
    public boolean selectPassword(String playerPseudo, String playerPwd) throws BusinessException {
        try {
            PlayerDto player = new PlayerDto(playerPseudo, playerPwd);
            return PlayerBusinessLogic.selectPassword(player);
        } catch (DbException | DtoException ex) {
            try {
                DBManager.cancelTransaction();
                throw new BusinessException(ex.getMessage());
            } catch (DbException ex1) {
                throw new BusinessException(ex1.getMessage());
            }
        }
    }

    @Override
    public void removePlayer(PlayerDto player) throws BusinessException {
        try {
            if (player.isPersistant()) {
                DBManager.startTransaction();
                PlayerBusinessLogic.delete(player.getId());
                DBManager.validateTransaction();
            } else {
                throw new BusinessException("Player: impossible de supprimer un player inexistant!");
            }
        } catch (DbException eDB) {
            String msg = eDB.getMessage();
            try {
                DBManager.cancelTransaction();
            } catch (DbException ex) {
                msg = ex.getMessage() + "\n" + msg;
            } finally {
                throw new BusinessException("Suppression de Player impossible! \n" + msg);
            }
        }
    }

    @Override
    public void updatePlayer(PlayerDto player) throws BusinessException {
        try {
            DBManager.startTransaction();
            PlayerBusinessLogic.update(player);
            DBManager.validateTransaction();
        } catch (DbException eDB) {
            String msg = eDB.getMessage();
            try {
                DBManager.cancelTransaction();
            } catch (DbException ex) {
                msg = ex.getMessage() + "\n" + msg;
            } finally {
                throw new BusinessException("Mise à jour de Player impossible! \n" + msg);
            }
        }
    }

}
