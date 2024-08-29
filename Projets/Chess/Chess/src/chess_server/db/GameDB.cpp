#include <db/GameDB.h>
using namespace std;
void GameDB::deleteDB(int id)
{
    QString queryArg = "DELETE from game WHERE gameID=" +
                       QString::number(id);
    const auto & sql = DBManager::getConnection();
    QSqlQuery query(queryArg, sql);
    if (query.exec())
    {
        qDebug() << "Succesfully deleted from player !";

    }
    qDebug() << "An error occured while deleting from player !";
}
int GameDB::insertDB(GameDto record)
{
    int num = SequenceDB::getNextNum(SequenceDB::GAME);
    record.setID(num);
    const auto & sql = DBManager::getConnection();
    QSqlQuery query(sql);
    query.prepare("INSERT into game(gameID, playerID, moves, dateString, winnerID, difficulty) "
                  "VALUES(:gID,:pID,:moves,:date,:wID,:diff)");
    query.bindValue(":gID", num);
    query.bindValue(":pID", record.getID());
    query.bindValue(":moves", QString::fromStdString(record.getMoves()));
    query.bindValue(":date", QString::fromStdString(record.getDate()));
    query.bindValue(":wID", record.getID());
    query.bindValue(":diff",
                    QString::fromStdString(record.getDifficulty()));
    if (query.exec())
    {
        qDebug() << "Succesfully inserted player ! ";
        return num;
    }
    qDebug() << "An error occured while inserting a player ! ";
    return 0;
}

vector<GameDto> GameDB::getCollection(GameSpecification sel)
{
    vector<GameDto> al;
    QString query =
        "SELECT gameID, playerID, moves, dateString, winnerID, difficulty"
        " FROM GAME ";
    QString where = "";

    if (sel.getID() != 0)
    {
        where = where + " gameID = :gID";
    }

    if (sel.getPlayerID() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " playerID = :pID ";
    }
    if (sel.getMoves().size() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " moves = :moves ";
    }
    if (sel.getWinnerID() != 0 )
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " winnerID = :wID ";
    }
    if (sel.getDifficulty().size() != 0)
    {
        if (where.size() != 0)
        {
            where = where + " AND ";
        }
        where = where + " difficulty = :diff";
    }
    QSqlQuery sQ;
    if (where.size() != 0)
    {
        where = " where " + where + " order by dateString ";
        query = query + where;

        sQ.prepare(query);
        int i = 1;
        if (sel.getID() != 0)
        {
            sQ.bindValue(":gID", i);
            i++;
        }
        if (sel.getPlayerID() != 0)
        {
            sQ.bindValue(":pID", sel.getPlayerID());
            i++;
        }
        if (sel.getMoves().size() != 0)
        {
            sQ.bindValue(":moves", QString::fromStdString(sel.getMoves()) + "%");
            i++;
        }
        if (sel.getDate().size() != 0)
        {
            sQ.bindValue(":date", QString::fromStdString(sel.getDate()) + "%");
            i++;
        }
        if (sel.getWinnerID() != 0)
        {
            sQ.bindValue(":wID", sel.getWinnerID());
            i++;
        }
        if (sel.getDifficulty().size() != 0)
        {
            sQ.bindValue(":diff",
                         QString::fromStdString(sel.getDifficulty()) + "%");
            i++;
        }
    }
    else
    {
        query = query + " Order by dateString";;

    }
    if (sQ.prepare(query)) throw
        std::runtime_error("Cant prepare query for Player getCollection()");
    if (sQ.exec()) throw
        std::runtime_error("Cant execute for Player getCollection()");
    while (sQ.next())
    {
        al.push_back(GameDto(sQ.value("gameID").toInt(),
                             sQ.value("playerID").toInt(),
                             sQ.value("moves").toString().toStdString(),
                             sQ.value("dateString").toString().toStdString(),
                             sQ.value("winnerID").toInt(),
                             sQ.value("difficulty").toString().toStdString()));
    }
    return al;
}
