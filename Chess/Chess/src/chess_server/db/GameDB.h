#ifndef GAMEDB_H
#define GAMEDB_H
#include "DBManager.h"
#include "SequenceDB.h"
#include <dto/GameDto.h>
#include <specification/GameSpecification.h>

namespace std
{
/**
 * @brief The GameDB class interacts with GAME table
 * where only insertions and deletion can be operated
 */
class GameDB
{
    static inline const string recordName{"GAME"};
  public:
    /**
     * @brief deleteDB This method can delete a game based on its id
     * @param id given id
     */
    static void deleteDB(int id);
    /**
     * @brief insertDB
     * @param record
     * @return the id of the game that just has been inserted in the database
     */
    static int insertDB(GameDto record);
    /**
     * @brief getCollection gets all the possible lines conteined within the table
     * based on a specification wich indicated if we want to match a where clause
     * @param sel specification wich contains the specified attributes
     * @return a vector contained the PlayerDto that have been found
     */
    static vector<GameDto> getCollection(GameSpecification sel);
};
}
#endif // GAMEDB_H
