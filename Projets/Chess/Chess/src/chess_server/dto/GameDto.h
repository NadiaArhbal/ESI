#ifndef GAMEDTO_H
#define GAMEDTO_H
#include "EntityDto.h"
namespace std
{
/**
 * @brief The GameDto class extends EntetyDto with an integer ID
 * a game is immuable it will not include setters
 */
class GameDto : public EntityDto<int>
{
    int _playerID;
    string  _moves;
    string _date;
    int _winnerID;
    string _difficulty;

  public:
    GameDto(int idArg, int playerID, string moves, string date,
            int winnerID, string difficulty) : _playerID(playerID), _moves(moves),
        _date(date)
        , _winnerID(winnerID), _difficulty(difficulty)
    {
        EntityDto<int>::_id = idArg;
    }
    /**
     * @brief getPlayerID gets the player's id
     * @return the id of the player
     */
    int getPlayerID()
    {
        return _playerID;
    }
    /**
     * @brief getMoves gets the moves in long algebraic form (can be quite long)
     * @return a constant reference to the string contained within this class
     */
    const string & getMoves()
    {
        return _moves;
    }
    /**
     * @brief getDate gets the Date that has been timestamped with QTdatetime
     * @return the date in the form Sun 09 2020 21:13
     */
    string getDate()
    {
        return _date;
    }
    /**
     * @brief getWinner gets the winner of the game
     * @return thhe ID of the winning player
     */
    int getWinner()
    {
        return _winnerID;
    }
    /**
     * @brief getDifficulty gets the difficulty either easy medium or hard
     * @return the const string string reference
     */
    const string & getDifficulty()
    {
        return _difficulty;
    }

    string to_string()
    {
        return "PlayerID: " + std::to_string(_playerID) + " Moves : " + _moves
               + " Date FORMAT : " +  _date + " WinnerID : " + std::to_string(
                   _winnerID) + " Difficulty : " + _difficulty;
    }
};
}
#endif //GAMEDTO_H
