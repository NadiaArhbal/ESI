package esi.bloc3.atlj.skyjo.server.model;

import esi.bloc3.atlj.skyjo.server.AbstractServer;
import esi.bloc3.atlj.skyjo.model.Facade;
import esi.bloc3.atlj.skyjo.model.Model;
import esi.bloc3.atlj.skyjo.server.ConnectionToClient;
import esi.bloc3.atlj.skyjo.users.Players;
import esi.bloc3.atlj.skyjo.users.User;
import esi.bloc3.atlj.skyjo.messages.Message;
import esi.bloc3.atlj.skyjo.messages.MessageEndConnection;
import esi.bloc3.atlj.skyjo.messages.MessageExistingPseudo;
import esi.bloc3.atlj.skyjo.messages.MessagePasswordFalse;
import esi.bloc3.atlj.skyjo.messages.MessageProfile;
import esi.bloc3.atlj.skyjo.messages.MessageSendModel;
import esi.bloc3.atlj.skyjo.messages.MessageWait;
import esi.bloc3.atlj.skyjo.messages.Type;
import esi.bloc3.atlj.skyjo.server.controller.Controller;
import esi.bloc3.atlj.skyjo.server.exception.BusinessException;
import esi.bloc3.atlj.skyjo.server.exception.DbException;
import esi.bloc3.atlj.skyjo.server.exception.DtoException;
import esi.bloc3.atlj.skyjo.util.EndGameSpec;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * SkyjoServer main class
 *
 * @author Christophe Rische Reda Choho
 */
public class SkyjoServer extends AbstractServer {

    static final String ID_MAPINFO = "ID";
    static final String GAMEINFO = "GAME";
    Facade gameSpec;
    private int clientId;
    private final Players players;
    private int ID;
    private Controller controller;

    public SkyjoServer(int port, Controller controller) throws IOException {
        super(port);
        players = new Players();
        this.controller = controller;
        clientId = 0;
        this.listen();
    }

    private static InetAddress getLocalAddress() {
        try {
            Enumeration<NetworkInterface> b
                    = NetworkInterface.getNetworkInterfaces();
            while (b.hasMoreElements()) {
                for (InterfaceAddress f
                        : b.nextElement().getInterfaceAddresses()) {
                    if (f.getAddress().isSiteLocalAddress()) {
                        return f.getAddress();
                    }
                }
            }
        } catch (SocketException e) {
            Logger.getLogger(SkyjoServer.class.getName()).log(Level.SEVERE,
                    "NetworkInterface error", e);
        }
        return null;
    }

    /**
     * Return the list of connected users.
     *
     * @return the list of connected users.
     */
    public Players getPlayers() {
        return players;
    }

    /**
     * Return the server IP address.
     *
     * @return the server IP address.
     */
    public String getIP() {
        if (getLocalAddress() == null) {
            return "Unknown";
        }
        return getLocalAddress().getHostAddress();
    }

    /**
     * Return the number of connected users.
     *
     * @return the number of connected users.
     */
    public int getNbConnected() {
        return getNumberOfClients();
    }

    /**
     * Quits the server and closes all aspects of the connection to clients.
     *
     * @throws IOException
     */
    public void quit() throws IOException {
        this.stopListening();
        this.close();
    }

    /**
     * Return the next client id.
     *
     * @return the next client id.
     */
    final synchronized int getNextId() {
        clientId++;
        return clientId;
    }

    @Override
    protected void handleMessageFromClient(Object msg,
            ConnectionToClient client) {
        Message message = (Message) msg;
        Type type = message.getType();
        int playerId = (int) client.getInfo(ID_MAPINFO);
        Facade game = (Model) client.getInfo(GAMEINFO);

        User author = message.getAuthor();
        switch (type) {
            case PROFILE:
                players.changeName(author.getName(), playerId);
                Message messageName = new MessageProfile(playerId,
                        author.getName(), author.getPassword());
                sendToClient(messageName, playerId);
                if (players.size() == 2) {
                    MessageSendModel messageGame
                            = new MessageSendModel(User.ADMIN,
                                    User.EVERYBODY, game);
                    game.start();
                    gameSpec = game;
                    sendToAllClients(messageGame);
                } else if (players.size() == 1) {
                    MessageWait messageWait
                            = new MessageWait(User.ADMIN, author);
                    sendToClient(messageWait, 1);

                } else if (players.size() > 2) {
                    for (int i = 3; i <= clientId; i++) {
                        MessageSendModel messageGame
                                = new MessageSendModel(User.ADMIN,
                                        User.PROFILE, gameSpec);
                        sendToClient(messageGame, i);
                    }
                }
                sendToDatabase(author);
                break;

            case SEND_MODEL:
                game = (Facade) message.getContent();
                gameSpec = game;
                for (User player : players) {
                    if (player.getId() != message.getAuthor().getId()) {
                        MessageSendModel messageFromServer
                                = new MessageSendModel(User.ADMIN, player, game);
                        sendToClient(messageFromServer, player);
                    }
                }
                break;
            case SEND_ENDGAME:
                sendToDatabase((EndGameSpec) message.getContent());

        }
        setChanged();
        notifyObservers(message);
    }

    @Override
    protected void clientConnected(ConnectionToClient client) {
        super.clientConnected(client);
        int playerId = players.add(getNextId(), client.getName(),
                client.getInetAddress(), null);
        client.setInfo(ID_MAPINFO, playerId);
        Facade game = new Model();
        client.setInfo(GAMEINFO, game);
        ID = (int) client.getInfo(ID_MAPINFO);
        setChanged();
        notifyObservers();
    }

    @Override
    protected synchronized void clientDisconnected(ConnectionToClient client) {
        try {
            super.clientDisconnected(client);
            players.remove((int) client.getInfo(ID_MAPINFO));
            client.close();
            MessageEndConnection msg = new MessageEndConnection(User.ADMIN, User.EVERYBODY);
            sendToAllClients(msg);
            setChanged();
            notifyObservers();
        } catch (IOException ex) {
            Logger.getLogger(SkyjoServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    protected synchronized void clientException(ConnectionToClient client,
            Throwable exception) {
        super.clientException(client, exception);
        try {
            if (client.isConnected()) {
                client.sendToClient(new IllegalArgumentException(
                        "Message illisible " + exception.getMessage()));
            }
        } catch (IOException ex) {
            Logger.getLogger(SkyjoServer.class.getName())
                    .log(Level.SEVERE,
                            "Impossible d envoyer erreur au client", ex);
        }
    }

    /**
     * Sends a message to a Client thanks to the recipient
     *
     * @param message to send
     * @param recipient of the User
     */
    private void sendToClient(Message message, User recipient) {
        sendToClient(message, recipient.getId());
    }

    /**
     * Sends a message to a Client thanks to the client ID
     *
     * @param message to send
     * @param clientId ID of the client
     */
    private void sendToClient(Message message, int clientId) {
        try {
            ((ConnectionToClient) getClientConnections().get(clientId - 1))
                    .sendToClient(message);
        } catch (Exception ex) {
        }
    }
    /**
     * Sends user profile to the database based on his username and password
     * 
     * @param user 
     */
    private void sendToDatabase(User user) {
        boolean passwordExist = false;
        try {
            passwordExist = controller.getModel().selectPassword(
                    user.getName(), user.getPassword());
            controller.getModel().addPlayer(user.getName(), user.getPassword());
        } catch (BusinessException ex) {
            // Integrety violtion
            if (passwordExist) {
            } else if (!passwordExist) {
                Message MessagePasswordFalse = new MessagePasswordFalse(
                        ID, user.getName());
                sendToClient(MessagePasswordFalse, ID);
            } else {
                Message MessageExistingPseudo = new MessageExistingPseudo(
                        ID, user.getName());
                sendToClient(MessageExistingPseudo, ID);
            }
        }
    }

    /**
     * Send the endgame arguments to the database
     *
     * @param endgame the endgame object
     * @param winner the user that did send the message is the winner
     */
    private void sendToDatabase(EndGameSpec endgame) {
        try {
            int p1Id = controller.getModel().getPlayerID(players.getName(1));
            int p2Id = controller.getModel().getPlayerID(players.getName(2));
            int winnerID = controller.getModel()
                    .getPlayerID(players.getName(endgame.getWinner()));
            controller.getModel().addGame(p1Id, p2Id, winnerID,
                    endgame.getWinnerScore(), endgame.getLoserScore());
        } catch (BusinessException e) {
            System.out.println(e.getMessage());
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
    }
}
