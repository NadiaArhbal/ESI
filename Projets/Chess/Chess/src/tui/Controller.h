#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include "View.h"
#include <vector>
#include <QProcess>
#include <ChessPro.h>
#include <QtCore/QtCore>


const QString folder ("../../libs/Stockfish/");
const QString prog ("stockfish_14.1_win_x64_avx2.exe");
const QByteArray moveCmd ("position startpos moves");
const QByteArray movetimeCmd ("go movetime ");

class Controller : public QObject
{
    Q_OBJECT

    View _view;
    Game _game;
    QProcess * _stockfish;
  public :
    static ChessPro _moves;
    Controller() = default;
    Controller(View view, Game game);
    Controller(View view, Game game, QProcess * stockfish,
               QObject * parent = 0);
    /**
     * @brief sendToStockFish is the method responsible for the proccesing of the stockfish
     * standart output, this method extracts the move stockfish generated for black
     * and detects if no moves where provided from the engine (Stalemate or Checkmate)
     * This method will provide a string for a method call
     * @param chesspro the moves of the current game in long algebraic notation
     */
    void sendToStockFish(const std::string & chesspro);
    void showCheckersStockFish();
    void start();
    void endGameStockFish(Side winner);
  public slots:
    void    error(QProcess::ProcessError error);
    void    finished(int exitCode, QProcess::ExitStatus exitStatus);
    void    readyReadStandardError();
    void    readyReadStandardOutput();
    void    started();
};



#endif // CONTROLLER_H
