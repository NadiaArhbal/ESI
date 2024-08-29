#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QProcess>
#include <QtCore/QtCore>
#include <QTcpSocket>
#include "chesscore.h"
#include "boardview.h"
#include "eatenpieces.h"
#include "history.h"
#include "promotion.h"
#include "playerinfo.h"
#include "paramstock.h"
#include "playerconnection.h"
#include "../tui/ChessPro.h"
#include "observer/observer.h"
#include "observer/subject.h"

#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class ChessView; }
QT_END_NAMESPACE

const QByteArray moveCmd ("position startpos moves");
const QByteArray movetimeCmd ("go movetime ");

class ChessView : public QMainWindow, nvs::Observer, nvs::Subject
{
    Q_OBJECT

public:
    /**
     * @brief ChessView Constructor of the main gui window
     * @param game the game to observe and update when there's changes
     * @param stockfish QProcess that will handle the black player
     * @param parent QWidget
     */
    ChessView(Game *game, QProcess *stockfish, QTcpSocket *socket, QWidget *parent = nullptr);

    /**
     * @brief ~ChessView Destructor
     */
    virtual ~ChessView();

    /**
     * @brief _moves this std::string will contain all the game's moves and will
     * be updated at each round
     */
    static ChessPro _moves;

    /**
     * @brief update the view
     * @param subject Game
     */
    virtual void update(const nvs::Subject *subject) override;

    /**
     * @brief getGame getter for the Game
     * @return Game*
     */
    Game * getGame();

    /**
     * @brief init method to start a ChessView, that initializes
     * the first connection window
     */
    void init();

private:

    //Basic ChessView attributes
    Ui::ChessView *_ui;
    QGraphicsScene *_scene;

    //Attributes needed to run a Game
    Game * _game;
    QProcess * _stockfish;
    QTcpSocket * _socket;

    //All childrens that will observe ChessView
    BoardView * _boardView;
    EatenPieces * _eatenPiece;
    History * _history;
    Promotion * _promotion;
    ParamStock * _paramStock;
    PlayerConnection * _playerConnection;
    NewAccount * _newAccount;

    //To display player infos
    PlayerInfo * _playerInfoW;
    PlayerInfo * _playerInfoB;

    bool _PvP;

    /**
     * @brief setupChildrens will initialize all elements needed to
     * construct the main window
     */
    void setupChildrens();

    /**
     * @brief setGameInfo sets the current player label that need to play
     */
    void setGameInfo();

    /**
     * @brief setPlayerInfo sets the player informations from database
     * on top right corner, such as name, picture, etc...
     */
    void setPlayerInfo();

    /**
     * @brief askParameters ask what type of game the Player want's to play,
     * PvP or not
     */
    void askParameters();

    /**
     * @brief connectionToServer displays the connection window for the player
     */
    void connectionToServer();

    //stockfish
    /**
     * @brief sendToStockFish is the method responsible for the proccesing of the stockfish
     * standart output, this method extracts the move stockfish generated for black
     * and detects if no moves where provided from the engine (Stalemate or Checkmate)
     * This method will provide a string for a method call
     * @param chesspro the moves of the current game in long algebraic notation
     */
    void sendToStockFish(const std::string & chesspro);

    /**
     * @brief showCheckersStockFish shows checkers for stockfish input
     */
    void showCheckersStockFish();

    /**
     * @brief moveToStr translates a move into string
     * @return std::string (4 digits)
     */
    std::string moveToStr(std::pair<Position, Position>);

    /**
     * @brief positionToStr translates a Position to a string
     * @return std::string (2 digits)
     */
    std::string positionToStr(Position);

    /**
     * @brief strToPosition translates a string (4 digits) to a ChessCore move,
     * with start and end Position
     * @return std::pair<Position, Position> pair of start and end position
     */
    std::pair<Position, Position> strToPosition(std::string);

    /**
     * @brief makePause makes a little pause when needed to display windows
     * correctly
     */
    void makePause();

    /**
     * @brief getCurrentString gets the current player string
     * @return Current player string, WHITE or BLACK
     */
    QString getCurrentString();

    /**
     * @brief sendJsonEndGame sens Json document to the server at the end of
     * the game with player informations such as id, win or lose,...
     */
    void sendJsonEndGame();

    /**
     * @brief displayEndGame displays an end game window
     */
    void displayEndGame();

public slots:
    /**
     * @brief start restarts a game
     * called when "New" button pressed
     */
    void start();

    /**
     * @brief exit the program
     * called when "exit" button pressed
     */
    void exit();

    //Player interaction
    /**
     * @brief gameParameters launchs the game if PvP enabled,
     * launches Player connection to server if disabled, to play
     * against stockfish
     */
    void gameParameters();

    /**
     * @brief login player connection to db
     */
    void login();

    /**
     * @brief newAccount displays new account window
     */
    void newAccount();

    /**
     * @brief addNewAccount adds a new account to the db
     */
    void addNewAccount();

    //stockfish
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();
};
#endif // CHESSVIEW_H
