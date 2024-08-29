
#include "playerconnection.h"
#include "ui_playerconnection.h"

PlayerConnection::PlayerConnection(QTcpSocket *socket, PlayerInfo *playerInfo, QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::PlayerConnection),
    _socket(socket),
    _playerInfo(playerInfo)
{
    _ui->setupUi(this);
    setWindowIcon(QIcon(":/icon_chess/ChessIcon.ico"));
    setWindowTitle("Connection");
    //connect(_socket,SIGNAL(readyRead()),this, SLOT(onReadyRead()));
}

PlayerConnection::~PlayerConnection()
{
    delete _ui;
}

void PlayerConnection::on_pushButton_clicked()
{
    emit newAccount();
    this->close();
}


void PlayerConnection::on_btnLogIn_accepted()
{
    _user = _ui->leUserName->text();
    _pwd = _ui->lePwd->text();
    emit login();
   // makeJson();

}

//void PlayerConnection::makeJson()
//{
//    QJsonObject obj;
//    obj.insert("message", QJsonValue::fromVariant("login"));
//    obj.insert("username", QJsonValue::fromVariant(_user));
//    obj.insert("password", QJsonValue::fromVariant(_pwd));
//    QJsonDocument doc(obj);
//     qDebug() << "from user : " << doc.toJson();
//    _socket->flush();
//    _socket->write(doc.toJson());
//    _socket->waitForBytesWritten(3000);


////    //qDebug() << "server response : " << _socket->readAll();
////    QJsonDocument docFromServ = QJsonDocument::fromJson(_socket->readAll());
////     qDebug() << "from server" << docFromServ.toJson();
////    handleServerLogin(docFromServ.object());
//}
//void PlayerConnection::handleServerLogin(const QJsonObject & message) {
//    QVariantMap json_map = message.toVariantMap();
//    _playerInfo = new PlayerInfo(
//                json_map["id"].toInt(),
//                _user,
//                json_map["nationalite"].toString(),
//                json_map["img"].toInt(),
//                json_map["elo"].toInt());
//    emit login();
//}
//void PlayerConnection::onReadyRead() {

//    QByteArray response = _socket->readAll();
//    qDebug() << "from serv "<< response;
//    if(!attemptConversion(response).empty()) {
//        handleServerLogin(attemptConversion(response));
//    }
//}
//QJsonObject PlayerConnection::attemptConversion(QByteArray server) {
//    qDebug() << "Incoming message from client ! : ";
//    auto json_doc = QJsonDocument::fromJson(server);
//    bool isValid = true;
//    if (json_doc.isNull())
//    {
//        qDebug() << "Cannot create JSON !";
//        isValid = false;
//    }
//    if (!json_doc.isObject())
//    {
//        qDebug() << "The given message is not in JSON format !";
//        isValid = false;
//    }
//    if (isValid)
//    {
//         qDebug() << "from server" << json_doc.toJson();
//        return json_doc.object();
//    }
//    return QJsonObject();
//}

