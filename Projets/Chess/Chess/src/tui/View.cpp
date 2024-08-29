#include <View.h>
#include <QProcess>



std::vector<Position>View::findPosi(int x, int y, int x2, int y2)
{
    Position start = Position(x, y);
    Position end = Position(x2, y2);

    std::vector<Position> vecposi;
    vecposi.push_back(start);
    vecposi.push_back(end);
    return vecposi;
}

std::string View::askPositionUser()
{
    std::string pos;
    std::cout << "Player ";
    std::cout << " enter the move : " << std::endl;
    std::cin >> pos;
    return pos;
}

void View::displayBoard(Board & board)
{
    char letter = 0;
    char toLow = 0;
    for (int i = 0; i < 8; i ++)
    {
        for (int j = 0; j < 8; j ++)
        {
            Position position(i, j);
            displayLimiteAndLetter(i, j);
            PieceType type = board.getBoard().at(i).at(j).getType();
            if (board.getBoard().at(i).at(j).getColor() == Side::WHITE)
            {
                toLow = 32;
            }
            switch (type)
            {
                case PieceType::PAWN:
                    letter = 'P' + toLow;
                    std::cout << " " << letter << " ";
                    break;
                case PieceType::BISHOP:
                    letter = 'B' + toLow;
                    std::cout << " " << letter << " ";
                    break;
                case PieceType::KING:
                    letter = 'R' + toLow;
                    std::cout << " " << letter << " ";
                    break;
                case PieceType::KNIGHT:
                    letter = 'C' + toLow;
                    std::cout << " " << letter << " ";
                    break;
                case PieceType::QUEEN:
                    letter = 'Q' + toLow;
                    std::cout << " " << letter << " ";
                    break;
                case PieceType::ROOK:
                    letter = 'R' + toLow;
                    std::cout << " " << letter << " ";
                    break;
                case PieceType::NONE:
                    std::cout << " . ";
                    break;
            }
        }
        std::cout << "" << std::endl;

    }
    std::cout << " ---- a  b  c  d  e  f  g  h ---- " << std::endl;

}



void View::displayLimiteAndLetter(int & i, int & j)
{
    if (j == 0)
    {
        if (i == 0)
        {
            std::cout << " 8- |";
        }
        if (i == 1)
        {
            std::cout << " 7- |";
        }
        if (i == 2)
        {
            std::cout << " 6- |";
        }
        if (i == 3)
        {
            std::cout << " 5- |";
        }
        if (i == 4)
        {
            std::cout << " 4- |";
        }
        if (i == 5)
        {
            std::cout << " 3- |";
        }
        if (i == 6)
        {
            std::cout << " 2- |";
        }
        if (i == 7)
        {
            std::cout << " 1- |";
        }
    }
}

