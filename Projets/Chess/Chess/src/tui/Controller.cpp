#include <Controller.h>
ChessPro Controller::_moves = ChessPro();
Controller::Controller(View v, Game g, QProcess * stock,
                       QObject * par)
    : QObject(par), _view(v), _game(g), _stockfish(stock)
{}


void Controller::sendToStockFish(const std::string & chesspro)
{
    std::cout << moveCmd.toStdString() << chesspro << std::endl;
    QByteArray command(moveCmd + QByteArray::fromStdString(chesspro));
    _stockfish->write(command);
    _stockfish->write("\n go movetime 1500 \n"); // AI can do move in specified time
    while (_stockfish->waitForReadyRead(1500));
    qDebug() << "EXITED";
}
void Controller::showCheckersStockFish()
{
    qDebug() << "make d cmd ";
    _stockfish->write("\nd\n");
    while (_stockfish->waitForReadyRead(100));
}


void Controller::start()
{
    while (!_game.isEnded())
    {
        std::vector<Position> posi;
        try
        {
            this-> _view.displayBoard(_game.getBoard());
            if (_game.getCurrentPlayer() == WHITE)
            {
                std::cout << "White ";
            }
            else if (_game.getCurrentPlayer() == BLACK)
            {
                std::cout << "Black ";
            }
            std::string po = _view.askPositionUser();
            _moves.addMove(po);
            auto ok = _moves.translateStrToPosi(po);
            posi = _view.findPosi((ok.first.x), (ok.first.y), (ok.second.x),
                                  (ok.second.y));
            _game.move(posi.at(0), posi.at(1), _game.getCurrentPlayer());
            sendToStockFish(_moves.getMove()); //MAKE IA MOVE from stockfish
            if (_game.getBoard().hasNoLegalMoves()) showCheckersStockFish();
        }
        catch (const std::runtime_error & e)
        {
            qDebug() << "Invalid Move !";
        }
    }
    _stockfish->close();
    if (_game.getEndGame())
    {
        qDebug() << "Game won by :" << _game.getCurrentPlayer();
    }
    else
    {
        qDebug() << "Game Drawn !";
    }
    qDebug() << "Game ENDED";
}
void Controller::error(QProcess::ProcessError error)
{
    qDebug() << "Error: " << error;
}

void Controller::finished(int exitCode,
                          QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished: " << exitCode;
    qDebug() << exitStatus;
    qApp->exit();
}

void Controller::readyReadStandardError()
{
    qDebug() << "ReadyError";
    std::cout << "Proc Started" << std::endl;
}

void Controller::readyReadStandardOutput()
{
    qDebug() << "readyOut";
    QProcess * p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();
    QByteArray token;
    if (buf.contains("bestmove"))
    {
        token = "bestmove ";
        QByteArray moveTok = buf.sliced(buf.indexOf(token) + token.size());
        if (moveTok.contains("(none)"))
        {
            _game.getBoard().setNolegalMoves();
        }
        else
        {
            std::string move = moveTok.sliced(0, 4).toStdString();
            qDebug() << "Move MADE : " << QString::fromStdString(move);
            auto ok = _moves.translateStrToPosi(move);
            _game.move(ok.first, ok.second, Side::BLACK);
            _moves.addMove(move);
        }
    }
    else if (_game.isEnded() && buf.contains("Checkers:"))
    {
        token = "Checkers:";
        QByteArray checkTok = buf.sliced(buf.indexOf(token) +
                                         token.size());
        qDebug() << "Checkers value :" << checkTok;
        if (checkTok.size() == 0)
        {
            _game.setEndGame(false);
        }
        else
        {
            _game.setEndGame(true);
        }
    }
}


void Controller::started()
{
    qDebug() << "Proc Started";
    std::cout << "Proc Started" << std::endl;
}

