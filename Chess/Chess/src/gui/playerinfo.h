#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "observer/observer.h"
#include "observer/subject.h"
#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>

class PlayerInfo
{
private:
    QGraphicsScene * _scene;
    QString _name;
    QString _nat;
    QString _elo;
    int _id;
    int _numPic;

public:

    PlayerInfo();
    /**
     * @brief PlayerInfo Constructor of the Player information part of the GUI
     */
    PlayerInfo(int id, QString name, QString nat, int picNum, int elo);

    /**
     * @brief setUserProfile add the User Profile picture on the scene
     * @param numPic the number of the picture to be set
     */
    void setUserProfile(int numPic);

    /**
     * @brief getScene Getter of the Scene
     * @return the scene
     */
    QGraphicsScene * getScene();

    /**
     * @brief getName Getter of the name of the player
     * @return the name of the player
     */
    QString getName();

    /**
     * @brief getElo Getter of the elo of the Player
     * @return the elo of the player
     */
    QString getElo();

    /**
     * @brief getNat Getter of the nationality of the Player
     * @return the nationality of the player
     */
    QString getNat();

    /**
     * @brief getNumPic Getter Player's picture's number
     * @return the picture number of the player
     */
    int getNumPic();

    /**
     * @brief getId Getter Player's id
     * @return the id of the player
     */
    int getId();

    /**
     * @brief ~PlayerInfo Destructor of the PlayerInfo
     */
    virtual ~PlayerInfo();
};

#endif // PLAYERINFO_H
