#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include "pieceitem.h"

namespace Ui {
class NewAccount;
}

class NewAccount : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief NewAccount Constructor of the New Account Window
     * @param parent the parent
     */
    explicit NewAccount(QWidget *parent = nullptr);
    ~NewAccount();

    /**
     * @brief makeJson Make a JSON Document to send to the server
     * with the data of the new user
     */
    void makeJson();

private slots:

    /**
     * @brief on_buttonBox_accepted When the user click on the button "OK"
     */
    void on_buttonBox_accepted();

signals:
    void addNewAccount();

private:
    Ui::NewAccount *ui;

    std::vector<PieceItem *> _pics;

    QString _user;
    QString _pwd;
    std::string _nat;
    int _picNum;

    QJsonDocument _jsonDoc;
    QJsonObject _jsonObj;
};

#endif // NEWACCOUNT_H
