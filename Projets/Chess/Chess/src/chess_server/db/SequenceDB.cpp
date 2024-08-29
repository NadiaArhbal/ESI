#include "SequenceDB.h"
using namespace std;

int SequenceDB::getNextNum(string sequence)
{
    const auto & db = DBManager::getConnection();
    QString query = "UPDATE SEQUENCES set sValue = sValue+1 where id='"
                    + QString::fromStdString(sequence) + "'";
    QSqlQuery updateQuery(db);
    if (!updateQuery.prepare(query) || !updateQuery.exec())
    {
        qDebug() << "Sequence nextNum update did not work !";
        // throw exception
    }
    query = "SELECT sValue FROM Sequences  where id='" +
            QString::fromStdString(sequence) + "'";
    QSqlQuery selectQuery(query, db);
    selectQuery.exec();
    if (selectQuery.next())
    {
        int value = selectQuery.value("sValue").toInt();
        return value;
    }
    else
    {
        qDebug() << "No values have been found in Sequence query";
        return 0;
        // throw exception !
    }
}
