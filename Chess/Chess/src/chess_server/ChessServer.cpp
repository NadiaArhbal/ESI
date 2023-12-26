#include "ChessServer.h"


ChessServer::ChessServer(Observer & obs,
                         QObject * parent) : QTcpServer(parent), facade(AdminModel())
{
    addObs(obs);
    connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
    mSocket = nullptr;
}
void ChessServer::sendToClient(const QJsonDocument & msg)
{
    qDebug() << msg;
    if (mSocket)
    {
        QTextStream T(mSocket);
        T << msg.toJson();
        mSocket->waitForBytesWritten(3000); //3 seconds waiting
        mSocket->flush();
    }
}
void ChessServer::newConnection()
{
    if (!mSocket)
    {
        mSocket = this->nextPendingConnection();
        connect(mSocket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(mSocket, SIGNAL(disconnected()), SLOT(disconnected()));
        mSocket->write("You are connected to me\r\n");
        mSocket->flush();
        mSocket->waitForBytesWritten(3000);
    }
    else
    {
        this->nextPendingConnection()->write("Server busy with other client !\r\n");
    }

}
void ChessServer::readyRead()
{
    qDebug() << "Incoming message from client ! : ";
    auto json_doc = QJsonDocument::fromJson(mSocket->readAll());
    bool isValid = true;
    if (json_doc.isNull())
    {
        qDebug() << "Cannot create JSON !";
        isValid = false;
    }
    if (!json_doc.isObject())
    {
        qDebug() << "The given message is not in JSON format !";
        isValid = false;
    }
    if (isValid)
    {
        QJsonObject json_obj = json_doc.object();
        handleClientMessage(json_obj);
    }
    notify();
}
void ChessServer::disconnected()
{
    delete mSocket;
}
std::string ChessServer::getClientMessage()
{
    std::string temp{mSocket->readAll()};
    mSocket->flush();
    return temp;
}
void ChessServer::handleClientMessage(QJsonObject message)
{
    QVariantMap json_map = message.toVariantMap();
    std::string messageType =
        json_map["message"].toString().toStdString();
    QJsonDocument response;
    switch (convertString(messageType))
    {
        case NEW:
            response = generateIDResponse(facade.addPlayer(PlayerDto(0,
                                          json_map["username"].toString().toStdString()
                                          , json_map["password"].toString().toStdString(),
                                          json_map["image"].toInt(),
                                          json_map["nationalite"].toString().toStdString(),
                                          json_map["elo"].toInt())));
            qDebug() << "Player Creation";
            break;
        case LOGIN:
            response = generateLoginResponse(facade.getPlayerLogin(
                                                 json_map["username"].toString().toStdString()
                                                 , json_map["password"].toString().toStdString()));
            qDebug() << "Player Login";
            break;
        case ENDGAME:
            facade.addGame(GameDto(0,
                                   json_map["username"].toString().toInt(),
                                   json_map["moves"].toString().toStdString(),
                                   QDateTime::currentDateTime().toString().toStdString(),
                                   json_map["winnerID"].toInt(),
                                   json_map["difficulty"].toString().toStdString()
                                  ));
            qDebug() << "Added Game !";
            break;
        default:
            qDebug() << "Error undefined message type !";
    }
    sendToClient(response);
}
MessageType ChessServer::convertString(const std::string & value)
{
    if (value == "new") return MessageType::NEW;
    if (value == "login") return MessageType::LOGIN;
    if (value == "endgame") return MessageType::ENDGAME;
    return MessageType::UNDEFINED;
}
QJsonDocument ChessServer::generateLoginResponse(
    const optional<PlayerDto> & loginInfo)
{
    if (!loginInfo) throw  std::runtime_error("no player logon found");
    PlayerDto  login = loginInfo.value();
    QJsonObject response;
    response.insert("message", QJsonValue::fromVariant("login"));
    response.insert("id", QJsonValue::fromVariant(login.getID()));
    response.insert("img", QJsonValue::fromVariant(login.getImage()));
    response.insert("nationalite",
                    QJsonValue::fromVariant(QString::fromStdString(
                            login.getNationality())));
    response.insert("elo", QJsonValue::fromVariant(login.getElo()));
    return QJsonDocument(response);
}
QJsonDocument ChessServer::generateIDResponse(int id)
{
    if (!id) throw  std::runtime_error("no ID found");
    QJsonObject response;
    response.insert("message", QJsonValue::fromVariant("new"));
    response.insert("id", QJsonValue::fromVariant(id));
    return QJsonDocument(response);
}
