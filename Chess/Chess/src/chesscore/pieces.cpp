#include "pieces.h"

Pieces::Pieces(Side color, Position pos, PieceType type) : color{color}, pos{pos}, type{type}
{
    if(pos.x < 0 || pos.y < 0) {
        throw std::invalid_argument("pos negatif");
    }
}

Pieces::Pieces() {
    //std::cout<<"default constructor";
}

Pawn::Pawn(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::PAWN;
}

None::None(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::NONE;
}

King::King(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::KING;
}

Bishop::Bishop(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::BISHOP;
}

Knight::Knight(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::KNIGHT;
}

Queen::Queen(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::QUEEN;
}

Rook::Rook(Side side, Position start) {
    color = side;
    pos = start;
    type = PieceType::ROOK;
}

std::string Pieces::to_string() {
    std::string table = "Color : ";
    if(color == Side::EMPTY)
        table += "Empty";
    else if (color == Side::BLACK)
        table += "Black";
    else
        table += "White";
    table += "\n";
    table += "Type : ";
    switch (type)
    {
    case PieceType::PAWN:
        table += "Pawn";
        break;
    case PieceType::BISHOP:
        table += "Bishop";
        break;
    case PieceType::KING:
        table += "King";
        break;
    case PieceType::KNIGHT:
        table += "Knight";
        break;
    case PieceType::QUEEN:
        table += "Queen";
        break;
    case PieceType::ROOK:
        table += "Rook";
        break;
    case PieceType::NONE:
        table += "None";
        break;
    }
    table += "\n";
    table += "Position : " +  std::to_string(pos.x);
    table += ",";
    table += std::to_string(pos.y);
    table += "\n";
    return table;
}

