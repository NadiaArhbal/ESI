#ifndef SERVERVIEW_H
#define SERVERVIEW_H
#include <ChessServer.h>
#include <iostream>
#include <observer_pattern/observer.h>
class ChessServer;
class ServerView : public Observer
{
    ChessServer * _chessServer;
  public:
    ServerView(ChessServer * server) : _chessServer(server) { }
    inline void startServer();
    inline void sendToClient(const std::string & msg);
    void update() ;
};
inline void ServerView::startServer()
{
    if (_chessServer->listen(QHostAddress::Any, 1234))
    {
        std::cout << "Server started" << std::endl;
        while (!_chessServer->waitForNewConnection());
    }
    else
    {
        std::cout << "Server error occured ! " << std::endl;
        std::cout << _chessServer->errorString().toStdString() << std::endl;
    }
    std::cout << "Connected ! ";
}

void ServerView::update()
{
    std::cout << "Incoming message from Client : " <<
              _chessServer->getClientMessage();
}
#endif // SERVERVIEW_H
