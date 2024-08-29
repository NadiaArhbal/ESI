#include "chessview.h"
#include "playerconnection.h"
#include "promotion.h"
#include "paramstock.h"

#include <QApplication>
#include <QCoreApplication>
#include <iostream>
#include <QProcess>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <qdebug.h>

const QString folder ("../../libs/Stockfish/");
const QString prog ("stockfish_14.1_win_x64_avx2.exe");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game *game = new Game();

    QProcess stockfish;
    stockfish.start(folder + prog);
    stockfish.waitForStarted();
    stockfish.setInputChannelMode(QProcess::ForwardedInputChannel);
    QTcpSocket *socket = nullptr;
    ChessView chessView(game, &stockfish, socket);
    chessView.init();
    QObject::connect(&stockfish, SIGNAL(finished(int,QProcess::ExitStatus)), &chessView, SLOT(finished(int,QProcess::ExitStatus)));
    QObject::connect(&stockfish, SIGNAL(readyReadStandardOutput()), &chessView, SLOT(readyReadStandardOutput()));
    QObject::connect(&stockfish, SIGNAL(started()), &chessView, SLOT(started()));

//    Promotion p = Promotion(game, Position(0,7));
//    p.show();

//    chessView.show();
//    chessView.hide();
    return a.exec();
}
