#ifndef PLAYERBUSINESSLOGIC_H
#define PLAYERBUSINESSLOGIC_H
#include <db/PlayerDB.h>
#include <dto/PlayerDto.h>
#include <specification/PlayerSpecification.h>
#include <vector>
#include <optional>
namespace std
{

class PlayerBusinessLogic
{
  public:
    /**
     * @brief add a player when a client wants to create an account
     * @param player based on a new playerDTO
     * @return the id corresponding the the added player
     */
    inline static int add(PlayerDto player);
    /**
     * @brief update a player based on a modified dto for specified fields
     * @param player modified dto representing a pleyer
     * @return a booleaan that indicated if the player has been inserted with sucess
     */
    inline static bool update(PlayerDto player);
    /**
     * @brief findByLogin looks up a player in the database in the login phase based
     * on login arguments such as
     * @param pseudo the username of the user
     * @param password the password of the user
     * @return an optional record containing the player's record
     * that is nullopt if the arguments do not excactly match
     * the login arguments
     */
    inline static optional<PlayerDto> findByLogin(string pseudo,
            string password);
    /**
     * @brief findByID gets a playerdto based on its ID
     * usefull when the client sends its ID to the server
     * @param id specified ID
     * @return an optional record containing the player's record
     * that is nullopt if no user where found with that ID
     */
    inline static optional<PlayerDto> findByID(int id);
};
inline int PlayerBusinessLogic::add(PlayerDto player)
{
    return PlayerDB::insertDB(player);
}
inline bool PlayerBusinessLogic::update(PlayerDto player)
{
    return PlayerDB::updateDB(player);
}
inline optional<PlayerDto> PlayerBusinessLogic::findByLogin(
    string pseudo,
    string password)
{
    PlayerSpecification login(0, pseudo, password, 0, "", 0);
    const auto & col  = PlayerDB::getCollection(login);
    if (col.size() == 1)
    {
        return col.front();

    }
    else
    {
        qDebug() << "Cannot login user ! ";
        return nullopt;
    }
}
inline optional<PlayerDto> PlayerBusinessLogic::findByID(int id)
{
    PlayerSpecification login(id, "", "", 0, "", 0);
    const auto & col  = PlayerDB::getCollection(login);
    if (col.size() == 1)
    {
        return col.front();
    }
    else
    {
        qDebug() << "Cannot find specified user for given ID ! ";
        return nullopt;
    }
}
}
#endif //PLAYERBUSINESSLOGIC_H

