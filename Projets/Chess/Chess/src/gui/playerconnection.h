#ifndef PLAYERCONNECTION_H
#define PLAYERCONNECTION_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include "newaccount.h"
#include "playerinfo.h"

namespace Ui {
class PlayerConnection;
}

class PlayerConnection : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief PlayerConnection Constructor of the Player Connection Window
     * @param parent the parent
     */
    explicit PlayerConnection(QTcpSocket*, PlayerInfo*, QWidget *parent = nullptr);
    ~PlayerConnection();

    /**
     * @brief makeJson Make a JSON Document with the data of the user connection
     */
 //   void makeJson();

private slots:
    /**
     * @brief on_pushButton_clicked When the user click on the "Create New Account" button
     */
    void on_pushButton_clicked();

    /**
     * @brief on_btnLogIn_accepted When the user click on the "OK" button
     */
    void on_btnLogIn_accepted();
   // void onReadyRead();


signals:
    void login();
    void newAccount();

private:
//    void handleServerLogin(const QJsonObject & message );
//    QJsonObject attemptConversion(QByteArray server);
    Ui::PlayerConnection *_ui;

    QTcpSocket *_socket;
    PlayerInfo *_playerInfo;

    QString _user;
    QString _pwd;

    QJsonDocument _jsonDoc;
    QJsonObject _jsonObj;
};

#endif // PLAYERCONNECTION_H
