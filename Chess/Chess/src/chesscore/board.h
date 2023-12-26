#ifndef BOARD_H
#define BOARD_H
#include "pieces.h"
#include <array>
#include <vector>
#include <Position.h>
#include <algorithm>
/**
 * @brief ChessBoard shortens an array of array expression into ChessBoard type
 * an array of array is preferable since the number of elements contained in a
 * chess board is static 8 X 8
 */
typedef std::array<std::array<Pieces, 8 >, 8> ChessBoard;
class Board
{
    ChessBoard board;
    int cptKingBlackMoves = 0;
    int cptKingWhiteMoves = 0;
    bool rookBlackDeplacement = false;
    bool rookWhiteDeplacement = false;
    bool enPassant = false;
    bool enPassantStriker = false;
    bool specialPassant = false;
    bool specialLittlerock = false;
    bool specialGreatrock = false;
    bool specialPromo = false;
    bool noLegalMoves = false;
public:
    /**
     * @brief Board initializes the board based of a text file -> board_init.txt
     * where each supposed line of the chess board is delimited by a "/" char
     * and each value is correspondant to a piece type
     * the "|" char indicated the switch to change the color of the piece for
     * the last two lines
     * a fallthrough switch has been implemented for the case of "|"
     * so that it can also go to the next line
     *
     */
    Board();
    /**
     * @brief getBoard Guetter of Board
     * @return the board
     */
    inline ChessBoard getBoard();
    /**
     * @brief displayBoard display the board
     */
    void displayBoard();
    /**
     * @brief deplacementPieces make the deplacement of the piece
     * @param start the start position of the piece
     * @param end the end position of the piece the end position of the piece
     * @param side the side of the piece
     */
    void deplacementPieces(Position start, Position end, Side side);
    /**
     * @brief checkPawnDeplacement check if the pawn can move
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return true if the pawn can move
     */
    bool checkPawnDeplacement(Position start, Position end);
    /**
     * @brief checkKnightDeplacement check if the knight can move
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return true if the knight can move
     */
    bool checkKnightDeplacement(Position start, Position end);
    /**
     * @brief checkRookDeplacement check if the rook can move
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return true if the rook can move
     */
    bool checkRookDeplacement(Position start, Position end);
    /**
     * @brief checkBishopDeplacement check if the bishop can move
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return true if the bishop can move
     */
    bool checkBishopDeplacement(Position start, Position end);
    /**
     * @brief checkQueenDeplacement check if the queen can move
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return true if the queen can move
     */
    bool checkQueenDeplacement(Position start, Position end);
    /**
     * @brief checkKingDeplacement check if the king can move
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return return true if the king can move
     */
    bool checkKingDeplacement(Position start, Position end);
    /**
     * @brief checkAllDeplacement check the deplacement of all pieces
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @param side the side of the piece
     * @return true if the piece can move
     */
    bool checkAllDeplacement(Position start, Position end, Side side);
    /**
     * @brief isInside check if the piece is in the board
     * @param pos the position of the piece
     * @return return if the piece is in the board
     */
    bool isInside(Position pos);
    /**
     * @brief verticallyListMove check all vertical moves
     * @param start the start position of the piece
     * @return a vector of all vertical possible moves
     */
    std::vector<Position> verticalListMove(Position start);
    /**
     * @brief horizontallyListMove check all horizontal moves
     * @param start the start position of the piece
     * @return a vector of all horizontal possible moves
     */
    std::vector<Position> horizontalListMove(Position start);
    /**
     * @brief diagonallyListMove check all diagonal moves
     * @param start the start position of the piece
     * @return a vector of all diagonal possible moves
     */
    std::vector<Position> diagonalListMove(Position start);
    /**
     * @brief pawnSpecialMoves create a list of special moves of the pawn
     * @param start the start position of the
     * @return a list of special moves of the pawn
     */
    std::vector<Position> pawnSpecialMoves(Position start);
    /**
    * @brief pawnListMove check all pawn moves
    * @param start the start position of the piece
    * @param end the end position of the piece
    * @return a vector of all pawn possible moves
    */
    std::vector<Position> pawnListMove(Position start);
    /**
     * @brief knightListMove check knight moves
     * @param start the start position of the piece
     * @return a vector of knight possible moves
     */
    std::vector<Position> knightListMove(Position start);
    /**
     * @brief bishopListMove check bishop moves
     * @param start the start position of the piece
     * @return a vector of bishop possible moves
     */
    std::vector<Position> bishopListMove(Position start);
    /**
     * @brief rookListMove check rook moves
     * @param start the start position of the piece
     * @return a vector of rook possible moves
     */
    std::vector<std::vector<Position> > rookListMove(Position start);

    /**
    * @brief pawnDiagonal create a list of diagonal moves of the pawn
    * @param start the start position of the
    * @return a list of diagonal moves of the pawn
    */
    std::vector<Position> pawnDiagonal(Position start);
    /**
     * @brief queenListMove check queen moves
     * @param start the start position of the piece
     * @return a vector of queen possible moves
     */
    std::vector<std::vector<Position> > queenListMove(Position start);
    /**
     * @brief kingSpecialMoves create a list of special moves of the king
     * @param start the start position of the king
     * @return a list of special moves of the king
     */
    std::vector<Position> kingSpecialMoves(Position start);
    /**
     * @brief allAdversaryMoves get a list of all adversary pieces moves
     * @param side the side of the king
     * @return a list of all adversary pieces moves
     */
    std::vector<Position> allAdversaryMoves(Side side);
    /**
     * @brief kingListMove check king moves
     * @param start the start position of the piece
     * @return a vector of king possible moves
     */
    std::vector<Position>kingListMove(Position start);
    /**
     * @brief checkPlayer check the player side
     * @param start the start position of the piece
     * @param side the side of the piece
     * @return true if the player select his side
     */
    bool checkPlayer(Position start, Side side);
    /**
     * @brief checkPromotion check if the promotion is possible
     * @param end the end position of the piece
     * @param side the side of the piece
     * @return true if the player can make a promotion
     */
    bool checkPromotion(Position end, Side side);
    /**
     * @brief givePromotion make the promotion
     * @param pos position of the piece
     * @param type piece type of the piece
     */
    void givePromotion(Position pos, PieceType type);
    /**
     * @brief nonePiecesRock checks if there is no piece between the rook and the king
     * @param start the start position of the king
     * @param end the end position of the king
     * @return true if there is no piece between the rook and the king false if not
     */
    bool nonePiecesRock(Position start, Position end);
    /**
     * @brief ifrock check if the rock is possble
     * @param start the start position of the piece
     * @param side the side of the piece
     * @return true if the player can make a rock
     */
    bool ifrock(Position start, Position end, Side side);
    /**
     * @brief rock make the rock
     * @param start the start position of the piece
     */
    void rock(Position start, Position end);
    /**
     * @brief ifEnPassant check if the opponent piece is in position for a rock
     * @param start the start position of the piece
     * @param end the end position of the piece
     */
    void ifEnPassant(Position start, Position end);
    /**
     * @brief ifEnPassantStriker check if the piece is in position for a rock
     * @param start the start position of the piece
     * @param end the end position of the piece
     * @return return true if the piece is in position for a rock
     */
    bool ifEnPassantStriker(Position start, Position end);
    /**
     * @brief EnPassant make the shot passant
     * @param start the start position of the piece
     * @param end the end position of the piece
     */
    void EnPassant(Position start, Position end);
    /**
     * @brief getSpecialPassant Guetter of the special shot passant
     * @return true if the special shot passant is possible
     */
    inline bool getSpecialPassant();
    /**
     * @brief setSpecialPromotion Setter of the special shot passant
     * @param newBool set the the special shot passant
     */
    inline void setSpecialPromotion(bool newBool);
    /**
     * @brief getSpecialPromotion Guetter of the special shot passant
     * @return true if the special shot promotion is possible
     */
    inline bool getSpecialPromotion();
    /**
     * @brief getSpecialLittlerock Guetter of the special shot little rock
     * @return true if the special shot little rock is possible
     */
    inline bool getSpecialLittlerock();
    /**
     * @brief getSpecialGreatrock Guetter of the special shot great rock
     * @return true if the special shot great rock is possible
     */
    inline bool getSpecialGreatrock();
    /**
    * @brief setNolegalMoves The stockfish process is the one
    * responsible for the detection of the inability to continue
    * the game from a game of chess, hence this method
    * simply sets the variable to true
    */
    inline void setNolegalMoves();
    /**
    * @brief hasNoLegalMoves checks if the board is at a point
    * where no moves can be done anymore
    */
    inline bool hasNoLegalMoves();
};
inline ChessBoard Board::getBoard(){return board;}
inline bool Board::getSpecialPassant(){return specialPassant;}
inline bool Board::getSpecialPromotion(){return specialPromo;}
inline void Board::setSpecialPromotion(bool newBool){specialPromo = newBool;}
inline bool Board::getSpecialLittlerock(){return specialLittlerock;}
inline bool Board::getSpecialGreatrock(){return specialGreatrock;}

inline void Board::setNolegalMoves()
{
    if (noLegalMoves) throw
        std::runtime_error("No legal moves already set !");
    noLegalMoves = true;
}
inline bool Board::hasNoLegalMoves()
{
    return noLegalMoves;
}

#endif // BOARD_H
