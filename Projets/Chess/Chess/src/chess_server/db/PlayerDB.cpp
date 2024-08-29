#include "PlayerDB.h"
using namespace std;

void PlayerDB::deleteDB(int id)
{
    QString queryArg = "DELETE from player WHERE playerID=" +
                       QString::number(id);
    const auto & sql = DBManager::getConnection();
    QSqlQuery query(queryArg, sql);
    if (query.exec())
    {
        qDebug() << "Succesfully deleted from player !";

    }
    qDebug() << "An error occured while deleting from player !";
}
int PlayerDB::insertDB(PlayerDto record)
{
    int num = SequenceDB::getNextNum(SequenceDB::PLAYER);
    record.setID(num);
    const auto & sql = DBManager::getConnection();
    QSqlQuery query(sql);
    query.prepare("INSERT into player(playerID, pseudo, password, img, nationality, elo) "
                  "VALUES(:play,:pseudo,:pswd,:img,:nat,:elo)");
    query.bindValue(":play", num);
    query.bindValue(":pseudo",
                    QString::fromStdString(record.getPseudo()));
    query.bindValue(":pswd",
                    QString::fromStdString(record.getPassword()));
    query.bindValue(":img", record.getImage());
    query.bindValue(":nat",
                    QString::fromStdString(record.getNationality()));
    query.bindValue(":elo", record.getElo());
    if (query.exec())
    {
        qDebug() << "Succesfully inserted player ! ";

        return num;
    }
    qDebug() << "An error occured while inserting a player ! ";
    return 0;
}
bool PlayerDB::updateDB(PlayerDto record)
{
    const auto & sql = DBManager::getConnection();
    QSqlQuery query(sql);
    query.prepare("UPDATE player set pseudo=:pseudo password=:pswd img=:img "
                  " nationality=:nat elo=:elo WHERE playerID =:id");
    query.bindValue(":pseudo",
                    QString::fromStdString(record.getPseudo()));
    query.bindValue(":pswd",
                    QString::fromStdString(record.getPassword()));
    query.bindValue(":img", record.getImage());
    query.bindValue(":nat",
                    QString::fromStdString(record.getNationality()));
    query.bindValue(":elo", record.getElo());
    query.bindValue(":id", record.getID());
    if (query.exec())
    {
        qDebug() << "Succesfully inserted player ! ";

        return true;
    }
    qDebug() << "An error occured while inserting a player ! ";
    return false;
}
vector<PlayerDto> PlayerDB::getCollection(PlayerSpecification sel)
{
    vector<PlayerDto> al;
    QString query =
        "SELECT playerID, pseudo, password, img, nationality, elo"
        " FROM PLAYER ";
    QString where = "";
    if (sel.getID() != 0)
    {
        where = where + " playerID = :pID";
    }

    if (sel.getPseudo().size() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " pseudo like :pseudo ";
    }

    if (sel.getPassword().size() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " password like :pswd ";
    }
    if (sel.getImage() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " img = :img ";
    }
    if (sel.getNationality().size() != 0 )
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " nationality = :nat ";
    }
    if (sel.getElo() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " elo = :elo";
    }
    QSqlQuery sQ(DBManager::getConnection());
    if (where.size() != 0)
    {
        where = " where " + where + " order by playerID, pseudo";
        query = query + where;
        if (!sQ.prepare(query)) throw
            std::runtime_error("Cant prepare statement for players collection");
        int i = 1;
        if (sel.getID() != 0)
        {
            sQ.bindValue(":pID", i);
            i++;
        }
        if (sel.getPseudo().size() != 0)
        {
            sQ.bindValue(":pseudo",
                         QString::fromStdString(sel.getPseudo()));
            i++;
        }
        if (sel.getPassword().size() != 0)
        {
            sQ.bindValue(":pswd",
                         QString::fromStdString(sel.getPassword()));
            i++;
        }
        if (sel.getImage() != 0)
        {
            sQ.bindValue(":img", sel.getImage());
            i++;
        }
        if (sel.getNationality().size() != 0)
        {
            sQ.bindValue(":nat", QString::fromStdString(sel.getNationality()));
            i++;
        }
        if (sel.getElo() != 0)
        {
            sQ.bindValue(":elo", sel.getElo());
            i++;
        }
    }
    else
    {
        query = query + " Order by playerID, pseudo";;

    }
    if (!sQ.exec())
        std::runtime_error("Cant execute for Player getCollection");
    while (sQ.next())
    {
        al.push_back(PlayerDto(sQ.value("playerID").toInt(),
                               sQ.value("pseudo").toString().toStdString(),
                               sQ.value("password").toString().toStdString(),
                               sQ.value("img").toInt(),
                               sQ.value("nationality").toString().toStdString(),
                               sQ.value("elo").toInt()));
    }
    return al;
}


