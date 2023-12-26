#ifndef GAME_H
#define GAME_H
#include <board.h>
#include <observer/subject.h>

/**
 * @brief The Game class represents the game of chess.
 */
class Game : public nvs::Subject
{
    Board board_;
    Side currentPlayer_ = WHITE;
    std::optional<bool> endGame;
    // This has three state = null -> game is not over
    // false -> game is drawn
    // true -> game is won

  public:
    /**
     * @brief Game constructor
     */
    Game();
    /**
     * @brief getBoard Getter of board
     * @return the board
     */
    inline Board & getBoard();
    /**
     * @brief getLittlerock indicates if we made a little rock
     * @return true if a little rock is performed otherwise false
     */
    inline bool getLittlerock();
    /**
     * @brief getGreatrock indicates if we made a great rock
     * @return true if a great rock is performed otherwise false
     */
    inline bool getGreatrock();
    /**
     * @brief getPassant indicates if we made a passant
     * @return true if a passant is performed otherwise false
     */
    inline bool getPassant();
    /**
     * @brief getPromotion indicates if we made a promotion
     * @return true if a promotion is performed otherwise false
     */
    inline bool getPromotion();
    /**
     * @brief getCurrentPlayer Getter of the current player
     * @return the color of the currentplayer
     */
    inline Side getCurrentPlayer();
    /**
     * @brief swapSide changes current player (passes the turn to the second player)
     */
    inline void swapSide();
    /**
     * @brief setEndGame is used by stockfish to set the endGame scenario
     * true if the game has been won by a player -> currentPlayer
     * false if the game has ended in a draw
     * @param option boolean representing the endgame option
     */
    inline void setEndGame(bool option);
    /**
     * @brief isEnded checks if the game is over based on if std::optional is empty or not
     * @return true if the game has ended and false if the game hasnt finished yet
     */
    inline bool isEnded();
    /**
     * @brief getEndGame returns the value std::optional
     * @return the value of the std::optional
     */
    inline bool getEndGame();
    /**
     * @brief move performs a movement under base from a base position and an end position
     * @param start a starting position
     * @param end a finish position
     * @param side the color of the pieces to be moved
     */
    void move(Position start, Position end, Side side);
    /**
     * @brief promotion perform the special promotion move
     * @param pos a position
     * @param side the color of the pieces
     */
    void promotion(Position pos, PieceType type);

};

inline Board & Game::getBoard()
{
    return board_;
}
inline bool Game::getLittlerock()
{
    return board_.getSpecialLittlerock();
}
inline bool Game::getGreatrock()
{
    return board_.getSpecialGreatrock();
}
inline bool Game::getPassant()
{
    return board_.getSpecialPassant();
}
inline bool Game::getPromotion()
{
    return board_.getSpecialPromotion();
}
inline Side Game::getCurrentPlayer()
{
    return this->currentPlayer_;
}
inline void Game::swapSide ()
{
    currentPlayer_ = currentPlayer_ == BLACK ? WHITE : BLACK;
}
inline void Game::setEndGame(bool option)
{
    if (!board_.hasNoLegalMoves()) throw
        std::runtime_error("Cannot set Endgame scenario because "
                           "there are still legal moves to play");
    endGame = option;
}
inline bool Game::isEnded()
{
    //notifyObservers();
    return board_.hasNoLegalMoves();
}
inline bool Game::getEndGame()
{
    return endGame.value();
}


#endif // GAME_H
