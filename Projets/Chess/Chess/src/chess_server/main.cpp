#include <QCoreApplication>
#include <iostream>
#include "ServerView.h"
#include <db/DBManager.h>
using namespace std;

int main(int argc, char * argv[])
{
    QCoreApplication a(argc, argv);
    ServerView v = nullptr;
    ChessServer server = ChessServer(v = ServerView(&server));
    v.startServer();
    return a.exec();
}
