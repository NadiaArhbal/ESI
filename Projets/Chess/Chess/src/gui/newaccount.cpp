#include "newaccount.h"
#include "ui_newaccount.h"

NewAccount::NewAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAccount)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon_chess/ChessIcon.ico"));
    setWindowTitle("New Account");

    QGraphicsScene * scene = new QGraphicsScene(this);
    PieceItem * pic;
    _pics = std::vector<PieceItem *>{};
    std::string path = "";
    int x = 0;
    int y = 0;
    for (int i = 0; i <= 39; ++i) {
        path = ":/pp/Profile" + std::to_string(i + 1) + ".png";
        if (i % 13 == 0) {
            y += 75;
            x -= 13;
        }
        pic = new PieceItem(path, i, Point(75 * x, y), true);
        pic->setScale(static_cast<double>(70) / static_cast<double>(512));
        _pics.push_back(pic);
        scene->addItem(pic);
        ++x;
    }
    ui->gvPP->setScene(scene);
}

NewAccount::~NewAccount()
{
    delete ui;
}

void NewAccount::makeJson()
{
    QJsonObject obj;
    obj.insert("message", QJsonValue::fromVariant("new"));
    obj.insert("username", QJsonValue::fromVariant(_user));
    obj.insert("password", QJsonValue::fromVariant(_pwd));
    obj.insert("elo", QJsonValue::fromVariant(1200));
    obj.insert("image", QJsonValue::fromVariant(_picNum));
    obj.insert("nationalite", QJsonValue::fromVariant(QString::fromStdString(_nat)));
    QJsonDocument doc(obj);
    qDebug() << doc.toJson();
}

void NewAccount::on_buttonBox_accepted()
{
    _user = ui->leUserName->text();
    _pwd = ui->lePwd->text();
    std::string acro = "";
    acro += ::toupper(ui->cbCountry->currentText().toStdString().at(0));
    acro += ::toupper(ui->cbCountry->currentText().toStdString().at(1));
    _nat = acro;
    for (auto pic : _pics) {
        if (pic->isSelected()) {
            _picNum = pic->getId();
            break;
        }
    }
    makeJson();
    emit addNewAccount();
}

