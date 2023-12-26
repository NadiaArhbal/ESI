#include <ChessPro.h>

std::string ChessPro::getType(PieceType type)
{
    switch (type)
    {
        case PAWN :
            return "";
        case BISHOP :
            return "B";
        case KNIGHT :
            return "N";
        case ROOK :
            return "R";
        case QUEEN :
            return "Q";
        case KING :
            return "K";
        default: throw std::invalid_argument("Invalid piecetype");
    }
}

char ChessPro::getX(int nb)
{
    switch (nb)
    {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        case 3:
            return 'd';
        case 4:
            return 'e';
        case 5:
            return 'f';
        case 6:
            return 'g';
        case 7:
            return 'h';
        default: throw std::invalid_argument("Invalid input letters");
    }
}

int ChessPro::getY(int ligne)
{
    return 8 - ligne;
}

std::string ChessPro::coupspe(Game game)
{
    std::string spec = "";
    if (game.getLittlerock())
    {
        spec += "0-0";
    }
    if (game.getGreatrock())
    {
        spec += "0-0-0";
    }
    if (game.getPromotion())
    {
        spec += ":";
    }
    if (game.getPassant())
    {
        spec += "e.p."; //à vérifier
    }
    //à rajouter echec (+),echec et mat(++ ou #) et pat()
    return spec;
}


std::string ChessPro::chess(Position posi, Board & board, Game game)
{
    std::string str = "";
    if (board.getBoard().at(posi.x).at(posi.y).getType() != NONE)
    {
        PieceType type = board.getBoard().at(posi.x).at(posi.y).getType();
        str += getType(type);
    }
    str += getX(posi.y);
    str += std::to_string(getY(posi.x));
    str += coupspe(game);

    return str;
}

std::pair<Position, Position> ChessPro::translateStrToPosi(
    std::string str)
{
    Position start;
    Position end;

    int startx = 8 - static_cast<int>(str.at(1)) +
                 48; //+48 pour pas avoir ascii
    int starty = str.at(0) -
                 'a'; //-a pour le rendre en int   ex: a = 65 donc 65-65=0

    start = Position(startx, starty);

    int endx = 8 - static_cast<int>(str.at(3)) + 48;
    int endy = str.at(2) - 'a';

    end = Position(endx, endy);

    return std::make_pair(start, end);
}
