#include "playerinfo.h"

PlayerInfo::PlayerInfo()
{
    _scene = new QGraphicsScene();
}

PlayerInfo::PlayerInfo(int id, QString name, QString nat, int numPic, int elo)
{
    _scene = new QGraphicsScene();
    _id = id;
    _name = name;
    _nat = nat;
    _elo = QString::number(elo);
    _numPic = numPic;
    setUserProfile(_numPic);
}

void PlayerInfo::setUserProfile(int numPic)
{
    std::string path;
    if (numPic == 0)  {
        path = ":/pp/Bot.png";
    } else {
        path = ":/pp/Profile" + std::to_string(numPic) + ".png";
    }
    QPixmap * pix = new QPixmap(path.c_str());
    QGraphicsPixmapItem * pi = new QGraphicsPixmapItem(*pix);
    pi->setScale(0.125);
    _scene->addItem(pi);
}

QGraphicsScene *PlayerInfo::getScene()
{
    return _scene;
}

QString PlayerInfo::getName()
{
    return _name;
}

QString PlayerInfo::getElo()
{
    return _elo;
}

QString PlayerInfo::getNat()
{
    return _nat;
}

int PlayerInfo::getNumPic()
{
    return _numPic;
}

int PlayerInfo::getId()
{
    return _id;
}

PlayerInfo::~PlayerInfo()
{

}
