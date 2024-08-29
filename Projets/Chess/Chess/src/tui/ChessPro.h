#ifndef CHESSPRO_H
#define CHESSPRO_H
#include <Position.h>
#include <iostream>
#include <string>
#include <vector>
#include <PieceType.h>
#include <board.h>
#include <game.h>

/**
 * @brief The ChessPro class corresponds to the coordinates of the chess game
 */
class ChessPro
{

    std::string moves;
  public:
    /**
     * @brief getX translates a number into a column
     * @param nb the number that we want to interpret in column
     * @return the corresponding column
     */
    char getX(int nb);
    /**
     * @brief getType returns for a given type of part a corresponding string of characters
     * @param type the piecetype
     * @return the corresponding string
     */
    std::string getType(PieceType type);
    /**
     * @brief getY we enter a line and this converts it to the corresponding line of the chess board
     * @param ligne the enter line
     * @return the corresponding line of the chess board
     */
    int getY(int ligne);
    /**
     * @brief chess from a position returns the associated chesspro notation
     * @param posi a position
     * @param board the board
     * @param game The game
     * @return a string corresponding to the chesspro notation
     */
    std::string chess(Position posi, Board & board, Game game);
    /**
     * @brief translateStrToPosi transforms a string taking a "number" position into a chesspro position
     * @param str the string the character string containing the number (position)
     * @return a pair of positions corresponding to the starting position and the finishing position
     */
    std::pair<Position, Position> translateStrToPosi(std::string str);
    /**
     * @brief coupspe takes care of the special notations for the special moves to add to the chesspro
     * @param game the game
     * @return the string of characters corresponding to the special move
     */
    std::string coupspe(Game game);
    inline void addMove(const std::string & move);
    inline const std::string & getMove();
    inline void setMove(std::string str);

};
inline void ChessPro::addMove(const std::string & move)
{
    moves += " " + move;
}
inline const std::string & ChessPro::getMove()
{
    return moves;
}
inline void ChessPro::setMove(std::string str)
{
    moves = str;
}
#endif // CHESSPRO_H
