#ifndef GAMEBUSINESSLOGIC_H
#define GAMEBUSINESSLOGIC_H
#include <db/GameDB.h>
#include <dto/GameDto.h>
namespace std
{
class GameBusinessLogic
{
  public:
    /**
     * @brief insert allows us to insert game when a client has finished a chess game
     * @param player brand new game dto to insert
     * @return a non zero id if it managed to insert th player succesfully
     */
    inline static int insert(GameDto player);
};
int GameBusinessLogic::insert(GameDto player)
{
    return GameDB::insertDB(player);
}
}
#endif // GAMEBUSINESSLOGIC_H
