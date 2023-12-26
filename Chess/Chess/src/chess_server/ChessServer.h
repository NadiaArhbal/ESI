#ifndef CHESSSERVER_H
#define CHESSSERVER_H
#include <business/AdminModel.h>
#include <business/AdminFacade.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>
#include <MessageType.h>
#include <observer_pattern/observer.h>
#include <observer_pattern/observable.h>
class ChessServer : public QTcpServer, observable
{
    Q_OBJECT
  public:
    ChessServer(Observer & obs, QObject * parent = 0);
    /**
     * @brief sendToClient sends a JSON built object back to the client
     * @param msg the message in the form of a JsonDocument
     */
    void sendToClient(const QJsonDocument & msg);
    /**
     * @brief getClientMessage simply gets what has been written in the socket
     * @return a string representing what the socket has
     */
    std::string getClientMessage();
  public slots:
    /**
     * @brief newConnection is triggered whenever a client decides to connect
     */
    void newConnection();
    /**
     * @brief readyRead receives a client message in a form of text that
     * represents a JSON this method tries to convert the message in a json format
     */
    void readyRead();
    /**
     * @brief disconnected is triggered whenever a client is disconnecte from the servers
     */
    void disconnected();
  private:
    /**
     * @brief handleClientMessage handles the JSON built object
     * in the readyRead method and interacts with the databases
     * @param message is the argument that needs to be mapped in order
     * to disect wich message has been sent
     */
    void handleClientMessage(QJsonObject message);
    /**
     * @brief convertString allows to give the corresponding enum
     * based on the string of the message
     * @param value string representing the message
     * @return the corresponding enum
     */
    MessageType  convertString(const std::string & value);
    /**
     * @brief generateLoginResponse generates the Jsondocument based the playerDTO
     * that has been found and needs to be relayed via JSON to the client
     * @param loginInfo a const reference to the playerDTO
     * @return the QjsonDocument to send to the client
     */
    QJsonDocument generateLoginResponse(const optional<PlayerDto> &
                                        loginInfo);
    /**
     * @brief generateIDResponse generates the Jsondocument based on the ID
     * that has been and needs to be relayed via JSON to the client
     * @param id the found id after user insertion
     * @return the QjsonDocument to send to the client
     */
    QJsonDocument generateIDResponse(int id);
    QTcpSocket * mSocket;
    AdminModel facade;
};

#endif // CHESSSERVER_H
