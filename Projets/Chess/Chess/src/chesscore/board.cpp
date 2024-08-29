#include "board.h"
#include <fstream>

Board::Board()
{
    std::ifstream is;
    try {
        is.open("..\\..\\resources\\board_init.txt", std::ios::in);
    }  catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    char current;
    int i = 0, j = -1;
    Side currentSide = Side::BLACK;
    while (is.get(current))
    {
        j++;
        switch (current)
        {
        case '0':
            board[i][j] = (None(Side::EMPTY,Position(i, j)));
            break;
        case '1':
            board[i][j] = (King(currentSide, Position(i, j)));
            break;
        case '2':
            board[i][j] = (Queen(currentSide, Position(i, j)));
            break;
        case '3':
            board[i][j] = (Rook(currentSide, Position(i, j)));
            break;
        case '4':
            board[i][j] = (Bishop(currentSide, Position(i, j)));
            break;
        case '5':
            board[i][j] = (Knight(currentSide, Position(i, j)));
            break;
        case '6':
            board[i][j] = (Pawn(currentSide, Position(i, j)));
            break;
        case '|': // side switching char + line incr
            currentSide = Side::WHITE;
            [[fallthrough]]; // allows to exeecute the code bellow without warning
        default:
            j = -1;
            i++;
        }
    }
}

void Board::displayBoard() {
    for(unsigned i = 0; i < board.size(); i ++) {
        for(unsigned j = 0; j < board[i].size(); j ++) {
            PieceType type = board.at(i).at(j).getType();
            switch (type)
            {
            case PieceType::PAWN:
                std::cout<<"P";
                break;
            case PieceType::BISHOP:
                std::cout<<"B";
                break;
            case PieceType::KING:
                std::cout<<"R";
                break;
            case PieceType::KNIGHT:
                std::cout<<"C";
                break;
            case PieceType::QUEEN:
                std::cout<<"Q";
                break;
            case PieceType::ROOK:
                std::cout<<"T";
                break;
            case PieceType::NONE:
                std::cout<<"N";
                break;
            }
        }
        std::cout<<""<<std::endl;
    }
}

bool Board::isInside(Position pos) {
    return pos.x >= 0 && pos.x < 8 && pos.y < 8 && pos.y >= 0;
}

bool Board::checkPlayer(Position start, Side side) {
    Side color = board.at(start.x).at(start.y).getColor();
    return (side == Side::WHITE && color == Side::WHITE)
           || (side == Side::BLACK && color == Side::BLACK);
}

std::vector<Position> Board::diagonalListMove(Position start) {
    std::vector<Position> Movesdiagonal;
    Side colorStart = board.at(start.x).at(start.y).getColor();
    int X[4] = {-1, -1, 1, 1};
    int Y[4] = {-1, 1, -1, 1};
    Side colorBeforeEnd;
    for(int i = 0; i < 4; i++) {
        for(int j = 1; j < 8; j++) {
            int x = start.x + X[i] * j;
            int y = start.y + Y[i] * j;
            int directionX = start.x - x;
            int directionY = start.y - y;
            if(isInside(Position(x,y))) {
                Side colorEnd = board.at(x).at(y).getColor();
                if(directionX < 0 && directionY < 0)
                    colorBeforeEnd = board.at(x - 1).at(y - 1).getColor();
                else if (directionX > 0 && directionY > 0)
                    colorBeforeEnd = board.at(x + 1).at(y + 1).getColor();
                else if (directionX < 0 && directionY > 0)
                    colorBeforeEnd = board.at(x - 1).at(y + 1).getColor();
                else if (directionX > 0 && directionY < 0)
                    colorBeforeEnd = board.at(x + 1).at(y - 1).getColor();
                if(colorEnd != colorStart) {
                    if(colorEnd != Side::EMPTY && colorEnd != colorStart) {
                        if(colorBeforeEnd != colorEnd) {
                            Movesdiagonal.push_back(Position(x,y));
                        }
                    } else if (colorEnd == Side::EMPTY && colorEnd != colorStart &&
                               colorBeforeEnd != colorStart && colorBeforeEnd != colorEnd) {
                        break;
                    }
                    else {
                        Movesdiagonal.push_back(Position(x,y));
                    }
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    return Movesdiagonal;
}

std::vector<Position> Board::horizontalListMove(Position start) {
    std::vector<Position> Moveshorizontal;
    Side colorBeforeEnd;
    Side colorStart = board.at(start.x).at(start.y).getColor();
    int X[2] = {-1, 1};
    for(int i = 0; i < 2; i++) {
        for(int j = 1; j < 8; j++) {
            int x = start.x + X[i] * j;
            int y = start.y;
            int direction = start.x - x;
            if(isInside(Position(x,y))) {
                Side colorEnd = board.at(x).at(y).getColor();
                if(direction < 0)
                    colorBeforeEnd = board.at(x - 1).at(y).getColor();
                else if (direction > 0)
                    colorBeforeEnd = board.at(x + 1).at(y) .getColor();
                if(colorEnd != colorStart) {
                    if(colorEnd != Side::EMPTY && colorEnd != colorStart) {
                        if(colorBeforeEnd != colorEnd) {
                            Moveshorizontal.push_back(Position(x,y));
                        }
                    }else if (colorEnd == Side::EMPTY && colorEnd != colorStart &&
                               colorBeforeEnd != colorStart && colorBeforeEnd != colorEnd) {
                        break;
                    }
                    else {
                        Moveshorizontal.push_back(Position(x,y));
                    }
                }  else {
                    break;
                }
            } else {
                break;
            }
        }
    }
    return Moveshorizontal;
}

std::vector<Position> Board::verticalListMove(Position start) {
    std::vector<Position> Movesvertical;
    Side colorStart = board.at(start.x).at(start.y).getColor();
    int Y[2] = {-1, 1};
    Side colorBeforeEnd;
    for(int i = 0; i < 2; i++) {
        for(int j = 1; j < 8; j++) {
            int x = start.x;
            int y = start.y + Y[i] * j;
            int direction = start.y - y;
            if(isInside(Position(x,y))) {
                Side colorEnd = board.at(x).at(y).getColor();
                if(direction < 0)
                    colorBeforeEnd = board.at(x).at(y - 1).getColor();
                else if (direction > 0)
                    colorBeforeEnd = board.at(x).at(y + 1).getColor();
                if(colorEnd != colorStart) {
                    if(colorEnd != Side::EMPTY && colorEnd != colorStart) {
                        if(colorBeforeEnd != colorEnd) {
                            Movesvertical.push_back(Position(x,y));
                        }
                    } else if (colorEnd == Side::EMPTY && colorEnd != colorStart &&
                               colorBeforeEnd != colorStart && colorBeforeEnd != colorEnd) {
                        break;
                    }
                    else {
                        Movesvertical.push_back(Position(x,y));
                    }
                }  else {
                    break;
                }
            } else {
                break;
            }
        }
    }
    return Movesvertical;
}

std::vector<Position> Board::knightListMove(Position start) {
    std::vector<Position> Moves;
    int cpt = 0;
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    Side colorStart = board.at(start.x).at(start.y).getColor();
    for (int i = 0; i < 8; i++) {
        int x = start.x + X[i];
        int y = start.y + Y[i];
        if (isInside(Position(x,y))) {
            Side colorEnd = board.at(x).at(y).getColor();
            if (colorEnd != colorStart) {
                Moves.push_back(Position(x,y));
                cpt++;
            }
        }
    }
    return Moves;
}

std::vector<Position> Board::bishopListMove(Position start) {
    return diagonalListMove(start);;
}

std::vector<std::vector<Position>> Board::queenListMove(Position start) {
    std::vector<std::vector<Position>> Moves;
    Moves.push_back(diagonalListMove(start));
    Moves.push_back(verticalListMove(start));
    Moves.push_back(horizontalListMove(start));
    return Moves;
}

std::vector<Position> Board::kingSpecialMoves(Position start) {
    std::vector<Position> Moves;
    Side color = board.at(start.x).at(start.y).getColor();
    int cpt = 0;
    bool side;
    color == Side::BLACK ? cpt = cptKingBlackMoves : cpt = cptKingWhiteMoves;
    color == Side::BLACK ? side = rookBlackDeplacement : side = rookWhiteDeplacement;
    if((start.x == 0  || start.x == 7) && start.y == 4 && cpt == 0 && !side) {
        if(board.at(start.x).at(start.y+2).getColor() == Side::EMPTY &&
            board.at(start.x).at(start.y+1).getColor() == Side::EMPTY) {
            Moves.push_back(Position(start.x,start.y+2));
        }
        if(board.at(start.x).at(start.y-2).getColor() == Side::EMPTY &&
            board.at(start.x).at(start.y-1).getColor() == Side::EMPTY) {
            Moves.push_back(Position(start.x,start.y-2));
        }
    }
    return Moves;
}

std::vector<Position> Board::kingListMove(Position start) {
    std::vector<Position> Moves;
    std::vector<Position> tempo;
    std::vector<Position> specialMoves = kingSpecialMoves(start);
    Side colorStart = board.at(start.x).at(start.y).getColor();
    std::vector<Position> MovesEchec = allAdversaryMoves(colorStart);
    for(int i = 0; i < 4; i++) {
        int X[4] = {-1, -1, 1, 1};
        int Y[4] = {-1, 1, -1, 1};
        for(int j = 1; j < 2; j++) {
            int x = start.x + X[i] * j;
            int y = start.y + Y[i] * j;
            tempo.push_back(Position(x,y));
        }
    }
    for(int i = 0; i < 2; i++) {
        int Y[2] = {-1, 1};
        for(int j = 1; j < 2; j++) {
            int x = start.x;
            int y = start.y + Y[i] * j;
            tempo.push_back(Position(x,y));
        }
    }
    for(int i = 0; i < 2; i++) {
        int X[2] = {-1, 1};
        for(int j = 1; j < 2; j++) {
            int x = start.x + X[i] * j;
            int y = start.y;
            tempo.push_back(Position(x,y));
        }
    }
    for (size_t i = 0; i < specialMoves.size(); i++)
        tempo.push_back(Position(specialMoves.at(i).x,specialMoves.at(i).y));
    for (Position echec : MovesEchec) {
        for (Position moves : tempo) {
            if(Position(echec.x,echec.y) == Position(7,3)) {
                tempo.erase(std::remove(tempo.begin(), tempo.end(), Position(7,2)), tempo.end());
            }
            if(Position(echec.x,echec.y) == Position(7,5)) {
                tempo.erase(std::remove(tempo.begin(), tempo.end(), Position(7,6)), tempo.end());
            }
            if(Position(echec.x,echec.y) == Position(0,3)) {
                tempo.erase(std::remove(tempo.begin(), tempo.end(), Position(0,2)), tempo.end());
            }
            if(Position(echec.x,echec.y) == Position(0,5)) {
                tempo.erase(std::remove(tempo.begin(), tempo.end(), Position(0,6)), tempo.end());
            }
            if(Position(echec.x,echec.y) == Position(moves.x,moves.y)) {
                tempo.erase(std::remove(tempo.begin(), tempo.end(), Position(moves.x,moves.y)), tempo.end());
            }
        }
    }
    for (size_t i = 0; i < tempo.size(); i++) {
        if(isInside(Position(tempo.at(i).x,tempo.at(i).y))) {
            Side colorEnd = board.at(tempo.at(i).x).at(tempo.at(i).y).getColor();
            if(colorEnd != colorStart) {
                Moves.push_back(Position(tempo.at(i).x,tempo.at(i).y));
            }
        }
    }

    return Moves;
}

std::vector<Position> Board::allAdversaryMoves(Side side) {
    std::vector<std::vector<Position>> Tempo;
    std::vector<std::vector<Position>> Queen;
    std::vector<std::vector<Position>> Rook;
    std::vector<Position> Moves;
    for(unsigned i = 0; i < board.size(); i ++) {
        for(unsigned j = 0; j < board[i].size(); j ++) {
            PieceType type = board.at(i).at(j).getType();
            Side color = board.at(i).at(j).getColor();
            if(color != side && color!= Side::EMPTY) {
                switch (type)
                {
                case PieceType::PAWN:
                    Tempo.push_back(pawnSpecialMoves(board.at(i).at(j).getPos()));
                    Tempo.push_back(pawnDiagonal(board.at(i).at(j).getPos()));
                    break;
                case PieceType::BISHOP:
                    Tempo.push_back(bishopListMove(board.at(i).at(j).getPos()));
                    break;
                case PieceType::KING:
                    break;
                case PieceType::KNIGHT:
                    Tempo.push_back(knightListMove(board.at(i).at(j).getPos()));
                    break;
                case PieceType::QUEEN:
                    Queen = queenListMove(board.at(i).at(j).getPos());
                    break;
                case PieceType::ROOK:
                    Rook = rookListMove(board.at(i).at(j).getPos());
                    break;
                case PieceType::NONE:
                    break;
                }
            }
        }
    }
    for(unsigned i = 0; i < Tempo.size(); i ++) {
        for(unsigned j = 0; j < Tempo.at(i).size(); j ++) {
            Moves.push_back(Position(Tempo.at(i).at(j).x,Tempo.at(i).at(j).y));
        }
    }
    for(unsigned i = 0; i < Queen.size(); i ++) {
        for(unsigned j = 0; j < Queen.at(i).size(); j ++) {
            Moves.push_back(Position(Queen.at(i).at(j).x,Queen.at(i).at(j).y));
        }
    }
    for(unsigned i = 0; i < Rook.size(); i ++) {
        for(unsigned j = 0; j < Rook.at(i).size(); j ++) {
            Moves.push_back(Position(Rook.at(i).at(j).x,Rook.at(i).at(j).y));
        }
    }
    return Moves;
}

std::vector<std::vector<Position>> Board::rookListMove(Position start) {
    std::vector<std::vector<Position>> Moves;
    Moves.push_back(verticalListMove(start));
    Moves.push_back(horizontalListMove(start));
    return Moves;
}

std::vector<Position> Board::pawnDiagonal(Position start) {
    std::vector<Position> Moves;
    Side colorStart = board.at(start.x).at(start.y).getColor();
    Position eatWhite1 = Position(start.x-1,start.y+1);
    Position eatWhite2 = Position(start.x-1,start.y-1);
    Position eatBlack1 = Position(start.x+1,start.y+1);
    Position eatBlack2 = Position(start.x+1,start.y-1);
    if(start.x < 7 && start.y < 7) {
        if(colorStart == Side::BLACK) {
                Moves.push_back(eatBlack1);
        }
    }
    if(start.x < 7 && start.y > 0) {
        if(colorStart == Side::BLACK) {
                Moves.push_back(eatBlack2);
        }
    }
    if(start.x > 0 && start.y > 0) {
        if(colorStart == Side::WHITE) {
                Moves.push_back(eatWhite2);
        }
    }
    if(start.x > 0 && start.y < 7) {
        Side endEatWhite1 = board.at(eatWhite1.x).at(eatWhite1.y).getColor();
        if(colorStart == Side::WHITE) {
            if(endEatWhite1 == Side::BLACK)
                Moves.push_back(eatWhite1);
        }
    }
    return Moves;
}

std::vector<Position> Board::pawnSpecialMoves(Position start) {
    std::vector<Position> Moves;
    Side colorStart = board.at(start.x).at(start.y).getColor();
    Position eatWhite1 = Position(start.x-1,start.y+1);
    Position eatWhite2 = Position(start.x-1,start.y-1);
    Position eatBlack1 = Position(start.x+1,start.y+1);
    Position eatBlack2 = Position(start.x+1,start.y-1);
    Position enPassant1 = Position(start.x,start.y+1);
    Position enPassant2 = Position(start.x,start.y-1);
    if(start.x < 7 && start.y < 7) {
        Side endEatBlack1 = board.at(eatBlack1.x).at(eatBlack1.y).getColor();
        Side colorEnPassant1 = board.at(enPassant1.x).at(enPassant1.y).getColor();
        if(colorStart == Side::BLACK) {
            if(endEatBlack1 == Side::WHITE)
                Moves.push_back(eatBlack1);
            if(colorEnPassant1 == Side::WHITE && ifEnPassantStriker(start,eatBlack1))
                Moves.push_back(eatBlack1);
        }
    }
    if(start.x < 7 && start.y > 0) {
        Side endEatBlack2 = board.at(eatBlack2.x).at(eatBlack2.y).getColor();
        Side colorEnPassant2 = board.at(enPassant2.x).at(enPassant2.y).getColor();
        if(colorStart == Side::BLACK) {
            if(endEatBlack2 == Side::WHITE)
                Moves.push_back(eatBlack2);
            if(colorEnPassant2 == Side::WHITE && ifEnPassantStriker(start,eatBlack2))
                Moves.push_back(eatBlack2);
        }
    }
    if(start.x > 0 && start.y > 0) {
        Side endEatWhite2 = board.at(eatWhite2.x).at(eatWhite2.y).getColor();
        Side colorEnPassant2 = board.at(enPassant2.x).at(enPassant2.y).getColor();
        if(colorStart == Side::WHITE) {
            if(endEatWhite2 == Side::BLACK)
                Moves.push_back(eatWhite2);
            if(colorEnPassant2 == Side::BLACK && ifEnPassantStriker(start,eatWhite2))
                Moves.push_back(eatWhite2);
        }
    }
    if(start.x > 0 && start.y < 7) {
        Side endEatWhite1 = board.at(eatWhite1.x).at(eatWhite1.y).getColor();
        Side colorEnPassant1 = board.at(enPassant1.x).at(enPassant1.y).getColor();
        if(colorStart == Side::WHITE) {
            if(endEatWhite1 == Side::BLACK)
                Moves.push_back(eatWhite1);
            if(colorEnPassant1 == Side::BLACK && ifEnPassantStriker(start,eatWhite1))
                Moves.push_back(eatWhite1);
        }
    }
    return Moves;
}

std::vector<Position> Board::pawnListMove(Position start)  {
    std::vector<Position> Moves;
    std::vector<Position> specialMoves = pawnSpecialMoves(start);
    int X;
    int max;
    Side colorStart = board.at(start.x).at(start.y).getColor();
    (start.x == 1 || start.x == 6) ? max = 3 : max = 2;
    colorStart == Side::BLACK ? X = 1 : X = -1;
    for(int i = 0; i < 2; i++) {
        for(int j = 1; j < max; j++) {
            int x = start.x + X * j;
            int y = start.y;
            if(isInside(Position(x,y))) {
                Side colorEnd = board.at(x).at(y).getColor();
                if(colorEnd == Side::EMPTY) {
                    Moves.push_back(Position(x,y));
                }
                else {
                    break;
                }
            } else {
                break;
            }

        }
    }
    for (size_t i = 0; i < specialMoves.size(); i++)
        Moves.push_back(Position(specialMoves.at(i).x,specialMoves.at(i).y));
    return Moves;
}

bool Board::checkPawnDeplacement(Position start, Position end)  {
    std::vector<Position> Moves = pawnListMove(start);
    for(unsigned i = 0; i < Moves.size(); i ++) {
        if(end.x == Moves.at(i).x && end.y == Moves.at(i).y) {
            return true;
        }
    }
    return false;
}

bool Board::checkKnightDeplacement(Position start, Position end)  {
    std::vector<Position> Moves = knightListMove(start);
    for(unsigned i = 0; i < Moves.size(); i ++) {
        if(end.x == Moves.at(i).x && end.y == Moves.at(i).y) {
            return true;
        }
    }
    return false;
}

bool Board::checkRookDeplacement(Position start, Position end)  {
    std::vector<std::vector<Position>> Moves = rookListMove(start);
    Side color = board.at(start.x).at(start.y).getColor();
    for(unsigned i = 0; i < Moves.size(); i ++) {
        for(unsigned j = 0; j < Moves.at(i).size(); j ++) {
            if(end.x == Moves.at(i).at(j).x && end.y == Moves.at(i).at(j).y) {
                color == Side::BLACK ? rookBlackDeplacement = true : rookWhiteDeplacement = true;
                return true;
            }
        }
    }
    return false;
}

bool Board::checkBishopDeplacement(Position start, Position end)  {
    std::vector<Position> Moves = bishopListMove(start);
    for(unsigned i = 0; i < Moves.size(); i ++) {
        if(end.x == Moves.at(i).x && end.y == Moves.at(i).y) {
            return true;
        }
    }
    return false;
}

bool Board::checkQueenDeplacement(Position start, Position end)  {
    std::vector<std::vector<Position>> Moves = queenListMove(start);
    for(unsigned i = 0; i < Moves.size(); i ++) {
        for(unsigned j = 0; j < Moves.at(i).size(); j ++) {
            if(end.x == Moves.at(i).at(j).x && end.y == Moves.at(i).at(j).y) {
                return true;
            }
        }
    }
    return false;
}

bool Board::checkKingDeplacement(Position start, Position end)  {
    std::vector<Position> Moves = kingListMove(start);
    Side color = board.at(start.x).at(start.y).getColor();
    for(unsigned i = 0; i < Moves.size(); i ++) {
        if(end.x == Moves.at(i).x && end.y == Moves.at(i).y) {
            color == Side::BLACK ? cptKingBlackMoves++ : cptKingWhiteMoves++;
            return true;
        }
    }
    return false;
}

bool Board::checkAllDeplacement(Position start, Position end, Side side) {
    PieceType type = board.at(start.x).at(start.y).getType();
    if(!checkPlayer(start,side)) {
        return false;
    }
    switch (type)
    {
    case PieceType::PAWN:
        return checkPawnDeplacement(start,end);
        break;
    case PieceType::BISHOP:
        return checkBishopDeplacement(start,end);
        break;
    case PieceType::KING:
        return checkKingDeplacement(start,end);
        break;
    case PieceType::KNIGHT:
        return checkKnightDeplacement(start,end);
        break;
    case PieceType::QUEEN:
        return checkQueenDeplacement(start,end);
        break;
    case PieceType::ROOK:
        return checkRookDeplacement(start,end);
        break;
    case PieceType::NONE:
        return false;
        break;
    }
    return false;
}

bool Board::checkPromotion(Position end, Side side) {
    PieceType type = board.at(end.x).at(end.y).getType();
    if((type == PieceType::PAWN && side == Side::BLACK && end.x == 7)
        || (type == PieceType::PAWN && side == Side::WHITE && end.x == 0)) {
        return true;
    }
    return false;
}

void Board::givePromotion(Position pos, PieceType type) {
    board.at(pos.x).at(pos.y).setType(type);
    specialPromo = true;
}

bool Board::nonePiecesRock(Position start, Position end) {
    Side color = board.at(start.x).at(start.y).getColor();
    int cpt = 0;
    bool side;
    color == Side::BLACK ? cpt = cptKingBlackMoves : cpt = cptKingWhiteMoves;
    color == Side::BLACK ? side = rookBlackDeplacement : side = rookWhiteDeplacement;
    if(cpt == 1 && !side) {
        std::vector deplacement = verticalListMove(end);
        if(end.y < 4) {
            int i = end.y + 1;
            while(i < 4) {
                if(board.at(end.x).at(i).getType() != PieceType::NONE) {
                    return false;
                }
                i++;
            }
        } else  {
            int i = end.y - 1;
            while(i > 4) {
                if(board.at(end.x).at(i).getType() != PieceType::NONE) {
                    return false;
                }
                i--;
            }
        }
        return true;
    }
    return false;
}

bool Board::ifrock(Position start, Position end, Side side) {
    PieceType type = board.at(start.x).at(start.y).getType();
    return type == PieceType::KING && nonePiecesRock(start,end) &&
           ((side == Side::BLACK && end.x == 0 && (end.y == 6 || end.y == 2)) ||
            (side == Side::WHITE && end.x == 7 && (end.y == 6 || end.y == 2)));
}

void Board::rock(Position start, Position end) {
    Side color = board.at(start.x).at(start.y).getColor();
    board.at(start.x).at(start.y).setType(PieceType::NONE);
    board.at(start.x).at(start.y).setColor(Side::EMPTY);
    if(end.y == 6) {
        board.at(end.x).at(6).setType(PieceType::KING);
        board.at(end.x).at(6).setColor(color);
        board.at(start.x).at(5).setType(PieceType::ROOK);
        board.at(start.x).at(5).setColor(color);
        board.at(start.x).at(7).setType(PieceType::NONE);
        board.at(start.x).at(7).setColor(Side::EMPTY);
        specialGreatrock = true;
    } else if (end.y == 2) {
        board.at(end.x).at(2).setType(PieceType::KING);
        board.at(end.x).at(2).setColor(color);
        board.at(start.x).at(3).setType(PieceType::ROOK);
        board.at(start.x).at(3).setColor(color);
        board.at(start.x).at(0).setType(PieceType::NONE);
        board.at(start.x).at(0).setColor(color);
        specialLittlerock = true;
    }
}

void Board::ifEnPassant(Position start, Position end) {
    PieceType type = board.at(start.x).at(start.y).getType();
    if(type == PieceType::PAWN && (start.x == 1 || start.x == 6) && (end.x == 3 || end.x==4)) {
        enPassant = true;
    }
}

bool Board::ifEnPassantStriker(Position start, Position end) {
    int y = end.y;
    PieceType type = board.at(start.x).at(start.y).getType();
    if(enPassant && (type == PieceType::PAWN && (start.x == 3 || start.x == 4))
        && (end.x == 2 || end.x == 4 || end.x == 3 || end.x == 5)
        && (start.y == y + 1 || start.y == y - 1)) {
        enPassantStriker = true;
        return true;
    }
    return false;
}

void Board::EnPassant(Position start,Position end) {
    if(start.y > 0) {
        int y = start.y - 1;
        PieceType type = board.at(start.x).at(y).getType();
        if(board.at(start.x).at(start.y-1).getType() == PieceType::PAWN &&
            (type == PieceType::PAWN && end.y == start.y -1)) {
            board.at(start.x).at(start.y-1).setType(PieceType::NONE);
            board.at(start.x).at(start.y-1).setColor(Side::EMPTY);
            specialPassant = true;
            enPassant = false;
        }
    }
    if(start.y < 7) {
        int y2 = start.y + 1;
        PieceType type2 = board.at(start.x).at(y2).getType();
        if (board.at(start.x).at(start.y+1).getType() == PieceType::PAWN &&
            (type2 == PieceType::PAWN && end.y == start.y +1)) {
            board.at(start.x).at(start.y+1).setType(PieceType::NONE);
            board.at(start.x).at(start.y+1).setColor(Side::EMPTY);
            specialPassant = true;
            enPassant = false;
        }
    }
}

void Board::deplacementPieces(Position start, Position end, Side side) {
    Position pos;
    PieceType type = board.at(start.x).at(start.y).getType();
    Side color = board.at(start.x).at(start.y).getColor();
    if(checkAllDeplacement(start,end,side)) {
        ifEnPassant(start,end);
        if(enPassantStriker) {
            EnPassant(start,end);
            enPassantStriker = false;
        }
        if(ifrock(start,end,side)) {
            rock(start,end);
            specialLittlerock = false;
            specialGreatrock = false;
        }
        else {
            pos = end;
            board.at(pos.x).at(pos.y).setType(type);
            board.at(pos.x).at(pos.y).setColor(color);
            board.at(start.x).at(start.y).setType(PieceType::NONE);
            board.at(start.x).at(start.y).setColor(Side::EMPTY);
        }
    } else {
        throw std::runtime_error("check false ! \n Veuillez recommence le move");
    }
}
