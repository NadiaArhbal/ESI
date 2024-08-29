#ifndef PIECES_H
#define PIECES_H
#include <Side.h>
#include <Position.h>
#include <iostream>
#include <PieceType.h>
#include <string.h>

/**
 * @brief The Pieces class represents the pieces of the game
 */
class Pieces
{
protected :
    Side color;
    Position pos;
    PieceType type;

public:
    /**
    * @brief Pieces constructor
    */
    Pieces();
    /**
     * @brief Pieces constructor with parameters
     * @param color the piece color
     * @param pos the piece position
     * @param type the piecetype
     */
    Pieces(Side color, Position pos, PieceType type);
    /**
     * @brief getColor Getter of color piece
     * @return the color piece
     */
    inline Side getColor();
    /**
     * @brief setColor Setter of color piece
     * @param newColor the new color
     * @return the color changed
     */
    inline Side setColor(Side newColor);
    /**
     * @brief getPos Getter of position piece
     * @return the position piece
     */
    inline Position getPos();
    /**
     * @brief getType Getter of piecetype
     * @return the piecetype
     */
    inline PieceType getType();
    /**
     * @brief setType Setter of piecetype
     * @param type the newtype of the piece
     * @return the type changed
     */
    inline PieceType setType(PieceType type);
    inline bool operator == (const Pieces &p1);
    /**
     * @brief to_string displays the type, color and position of the piece
     * @return the string containing all this information
     */
    std::string to_string();
};

inline Side Pieces::getColor() {
    return color;
}

inline Side Pieces::setColor(Side newColor) {
    return color = newColor;
}

inline Position Pieces::getPos() {
    return pos;
}

inline PieceType Pieces::getType() {
    return type;
}

inline PieceType Pieces::setType(PieceType newType) {
    return type = newType;
}

inline bool Pieces::operator==(const Pieces &p1) {
    return this->color == p1.color && this->type == p1.type;
}

#endif // PIECES_H

#ifndef PAWN_H
#define PAWN_H
/**
 * @brief The Pawn class representing the pawn pieces
 */
class Pawn : public Pieces
{
public:
    /**
     * @brief Pawn pieces constructor
     * @param color the color
     * @param pos the position
     */
    Pawn(Side color, Position pos);
};
#endif // PAWN_H

#ifndef NONE_H
#define NONE_H
/**
 * @brief The None class represents when there are no pieces
 */
class None : public Pieces
{
public:
    /**
     * @brief None constructor
     * @param color the color
     * @param pos the position
     */
    None(Side color, Position pos);
};
#endif // NONE_H

#ifndef KING_H
#define KING_H

/**
 * @brief The King class representing the King pieces
 */
class King : public Pieces
{
public:
    /**
     * @brief King pieces constructor
     * @param color the color
     * @param pos the position
     */
    King(Side color, Position pos);
};

#endif // KING_H

#ifndef BISHOP_H
#define BISHOP_H
/**
 * @brief The Bishop class representing the Bishop pieces
 */
class Bishop : public Pieces
{
public:
    /**
     * @brief Bishop pieces constructor
     * @param color the color
     * @param pos the position
     */
    Bishop(Side color, Position pos);
};

#endif // BISHOP_H

#ifndef KNIGHT_H
#define KNIGHT_H
/**
 * @brief The Knight class representing the Knight pieces
 */
class Knight : public Pieces
{
public:
    /**
     * @brief Knight pieces constructor
     * @param color the color
     * @param pos the position
     */
    Knight(Side color, Position pos);
};

#endif // KNIGHT_H

#ifndef QUEEN_H
#define QUEEN_H

/**
 * @brief The Queen class representing the Queen pieces
 */
class Queen : public Pieces
{
public:
    /**
     * @brief Queen pieces constructor
     * @param color the color
     * @param pos the position
     */
    Queen(Side color, Position pos);
};
#endif // QUEEN_H

#ifndef ROOK_H
#define ROOK_H

/**
 * @brief The Rook class representing the Rook pieces
 */
class Rook : public Pieces
{
public:
    /**
     * @brief Rook pieces constructor
     * @param color the color
     * @param pos the position
     */
    Rook(Side color, Position pos);
};

#endif // ROOK_H




