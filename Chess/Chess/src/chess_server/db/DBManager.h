#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QtDebug>
#include <QSqlQuery>
#include <string>
#include <vector>
/**
 * @brief The DBManager class allows us to interact
 * with the Database file
 */
class DBManager
{
    inline static QSqlDatabase m_db =
        QSqlDatabase::addDatabase("QSQLITE");
  public:
    /**
     * @brief getConnection connects to the database by setting the
     * path towards it and returning
     * @return the Qsqldatabase object
     */
    static inline QSqlDatabase getConnection();
    /**
     * @brief startTransaction starts a transaction of the contained static DB object
     */
    static inline void startTransaction();
    /**
     * @brief validateTransaction commits a transaction of the DB object and sets autocommit back to true
     */
    static inline void validateTransaction();
    /**
     * @brief cancelTransaction cancels the transaction and sets autocommit back to true
     */
    static inline void cancelTransaction();
};
inline QSqlDatabase DBManager::getConnection()
{
    m_db.setDatabaseName("../../resources/sql/db/ChessDB.db");
    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
        // throw exepction once its implemented !
    }
    else
    {
        qDebug() << "Database is now open !";
    }
    return m_db;

}
inline void DBManager::startTransaction()
{
    if (!getConnection().transaction())
    {
        qDebug() << "Error cant start transaction !";
        // throw exepction once its implemented !
    }
    else
    {
        qDebug() << "Transaction has begun !";
    }
}
inline void DBManager::validateTransaction()
{
    getConnection().commit();
    QSqlQuery qry("SET autocommit = 1", m_db);
    qry.exec();
}
inline void DBManager::cancelTransaction()
{
    getConnection().rollback();
    QSqlQuery qry("SET autocommit = 1", m_db);
    qry.exec();
}
#endif // DBMANAGER_H
