#ifndef PLAYERDB_H
#define PLAYERDB_H
#include "DBManager.h"
#include "dto/PlayerDto.h"
#include "SequenceDB.h"
#include "specification/PlayerSpecification.h"
namespace std
{
/**
 * @brief The PlayerDB class interacts with the PLAYER
 * table where data can be inserted updated and deleted
 */
class PlayerDB
{
    static inline const string recordName{"PLAYER"};
  public:
    /**
     * @brief deleteDB simply deletes a player of the database
     * @param id given id to delete the player
     */
    static void deleteDB(int id);
    /**
     * @brief updateDB updates a player based on a dto wich
     * is modified after getting it from the getCollection method
     * @param record is the updated record that the method is gonna base itself
     * to enter all of the neccesary values as an update query
     * @return true if the player has been updated succesfully
     */
    static bool updateDB(PlayerDto record);
    /**
     * @brief insertDB inserts a player based on a brand new dto
     * @param record the new dto in question
     * @return the ID of the newly added record
     */
    static int insertDB(PlayerDto record);
    /**
     * @brief getCollection gets all the possible lines conteined within the table
     * based on a specification wich indicated if we want to match a where clause
     * with matching arguments of the record
     * @param sel specification wich contains the specified attributes
     * @return a vector contained the PlayerDto that have been found
     */
    static vector<PlayerDto> getCollection(PlayerSpecification sel);
};
}

#endif // PLAYERDB_H
