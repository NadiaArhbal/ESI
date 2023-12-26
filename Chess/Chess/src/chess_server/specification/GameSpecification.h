#ifndef GAMESPECIFICATION_H
#define GAMESPECIFICATION_H
#include <string>
namespace std
{
/**
 * @brief The GameSpecification class contains
 * the given arguments example here is if no arguments are given then
 * int is represented by 0 or strings with ""
 */
class GameSpecification
{
    int _gameId;
    int _playerID;
    string _moves;
    string _date;
    int _winnerID;
    string _difficulty;
  public:
    GameSpecification(int gameId, int playerID, string moves,
                      string date, int winnerID, string  difficulty) : _gameId(gameId),
        _playerID(playerID),
        _moves(moves), _date(date), _winnerID(winnerID),
        _difficulty(difficulty) {}
    /**
     * @brief getID simply gets the id of the game
     * @return the id if the game
     */
    inline int getID();
    /**
     * @brief getPlayerID gets the id of the player
     * @return the id of the player
     */
    inline int getPlayerID();
    /**
     * @brief getMoves gets the moves of the game e.g e2e4
     * @return the moves
     */
    inline const string & getMoves();
    /**
     * @brief getDate gets the date in a string formats
     * @return the date in the form of a string
     */
    inline const string & getDate();
    /**
     * @brief getWinnerID gets the winnerID equivalent to the id of a player
     * @return the winnerID
     */
    inline int getWinnerID();
    /**
     * @brief getDifficulty gets the difficulty in the form a string
     * @return the difficultys
     */
    inline const string & getDifficulty();
};
inline int GameSpecification::getID()
{
    return _gameId;
}
inline int GameSpecification::getPlayerID()
{
    return _playerID;
}
inline const string & GameSpecification::getMoves()
{
    return _moves;
}
inline const string & GameSpecification::getDate()
{
    return _date;
}
inline int GameSpecification::getWinnerID()
{
    return _winnerID;
}
inline const string & GameSpecification::getDifficulty()
{
    return _difficulty;
}
}
#endif //GAMESPECIFICATION_H
