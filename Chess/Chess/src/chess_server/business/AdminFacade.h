#ifndef ADMINFACADE_H
#define ADMINFACADE_H
#include <db/DBManager.h>
#include <dto/PlayerDto.h>
#include <dto/GameDto.h>
#include <optional>
#include <business/PlayerBusinessLogic.h>
#include <business/GameBusinessLogic.h>
#include <iostream>
#include <string>
using namespace std;
class AdminFacade
{
  public:
    /**
     * Returns the unique player with the given id.
     *
     * @param id player's id.
     * @return the dto as optional if its nullopt then the player doesnt exist
     *
     */
    virtual optional<PlayerDto> getPlayerByID(int id)
    {
        std::cout << "ID : " << to_string(id);
        return nullopt;
    };
    /**
     * @brief getPlayerLogin Used in the login process
     * @param pseudo the unique pseudo of the user
     * @param password the password of the user
     * @return gives the playerDTO record
     */
    virtual optional<PlayerDto> getPlayerLogin(string pseudo,
            string password)
    {
        pseudo + password;
        return nullopt;
    };
    /**
     * @brief addPlayer used in the user creation process
     * @param player the Player in a dto form
     * @return something greater than 1 if the player has been added succesfully
     */
    virtual int addPlayer(PlayerDto player)
    {
        std::cout << player.to_string();
        return 0;
    };
    /**
     * @brief addGame used in the game storage phase (when the client send the end game arguments)
     * Creates a game and inserts it in the database
     * based on the given gameDto
     */
    virtual int addGame(GameDto game)
    {
        std::cout << game.to_string();
        return 0;
    }
    /**
     * Updates the given player e.g ELO value
     *
     * @param current player to update
     * @return true if the update has been done succesfully !
     */
    virtual bool updatePlayer(PlayerDto player)
    {
        std::cout << player.to_string();
        return 0;
    };
};


#endif //ADMINFACADE.H
