#include "chessview.h"
#include "ui_chessview.h"
#include "promotion.h"
#include "paramstock.h"
#include "playerconnection.h"

ChessPro ChessView::_moves = ChessPro();

ChessView::ChessView(Game *game, QProcess *stockfish, QTcpSocket *socket, QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::ChessView)
    , _game(game)
    , _stockfish(stockfish)
    , _socket(socket)
{
    _ui->setupUi(this);
    _scene = new QGraphicsScene(this);
    _ui->graphicsView->setScene(_scene);
    QGraphicsView * view = new QGraphicsView(_scene);

    _game->registerObserver(this);

    //Icon + Title Window
    setWindowIcon(QIcon(":/icon_chess/ChessIcon.ico"));
    setWindowTitle("Chess");

    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::TextAntialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->update();
}

ChessView::~ChessView()
{
    delete _boardView;
    delete _history;
    delete _promotion;
    delete _playerConnection;
    delete _paramStock;
    delete _newAccount;
    //delete _socket;
    delete _scene;
    delete _ui;
    delete _playerInfoB;
    delete _playerInfoW;
}

void ChessView::update(const nvs::Subject *subject){
    if(subject == nullptr) return;

    //For History
    if(_boardView->getLastWhiteMove().first.x != -1
            && _game->getCurrentPlayer() == BLACK){
        _moves.addMove(moveToStr(_boardView->getLastWhiteMove()));
    }
    //TODO history with promotion
    if(_PvP && _game->getCurrentPlayer() == WHITE
            /*&& _moves.getMove().substr(_moves.getMove().size() - 4) != moveToStr(_boardView->getLastBlackMove())*/){
        _moves.addMove(moveToStr(_boardView->getLastBlackMove()));
    }

    setGameInfo();
    notifyObservers();
    if(!_game->isEnded()){
        if(!_PvP){
            if(_game->getCurrentPlayer() == BLACK){
                try {
                    makePause(); //let the BoardView refresh
                    sendToStockFish(_moves.getMove());
                    sendToStockFish(_moves.getMove()); //verification checkmate
                }
                catch (const std::runtime_error & e){
                    qDebug() << "Invalid Move ! error: " << e.what();
                }
            }
        }else if(_game->getPromotion()){
            std::string str = _moves.getMove().substr(_moves.getMove().size() - 4);
            auto positions = strToPosition(str);
            _promotion = new Promotion(_game, positions.second);
            _promotion->show();
            notifyObservers();
            //_moves.setMove(_moves.getMove().substr(0, _moves.getMove().size() - 5));
        }
    }else{
        showCheckersStockFish();
        sendJsonEndGame();
        displayEndGame();
    }
}

Game * ChessView::getGame(){
    return _game;
}

void ChessView::init()
{
    askParameters();

    connect(_ui->actionNew, &QAction::triggered, this, &ChessView::start);
    connect(_ui->actionExit, &QAction::triggered, this, &ChessView::exit);
    connect(_paramStock, SIGNAL(filled()), this, SLOT(gameParameters()));
}

void ChessView::setupChildrens()
{

    _boardView = new BoardView(_scene, _game, &_PvP);

    //EatenPieces
    _eatenPiece = new EatenPieces(_game);
    _ui->gvEatenByBlack->setScene(_eatenPiece->getEatenWhiteScene());
    _ui->gvEatenByWhite->setScene(_eatenPiece->getEatenBlackScene());

    //History
    _history = new History(_ui->twHistory, &_moves);

    setPlayerInfo();

    this->registerObserver(_boardView);
    this->registerObserver(_eatenPiece);
    this->registerObserver(_history);

    notifyObservers();
    this->show();
}

void ChessView::setGameInfo()
{
    _ui->lblInfoGame->setText(getCurrentString() + " it's your turn !");
}

void ChessView::setPlayerInfo()
{
    //PlayerInfo
    _playerInfoB = new PlayerInfo();
    _playerInfoW = new PlayerInfo();
    if (!_PvP) {
        _ui->lblInfoBlack->setText("1200"); //StockFish
        _ui->lblNameBlack->setText("StockFish"); //StockFish
        _playerInfoB->setUserProfile(0);
        _ui->gvIconBlack->setScene(_playerInfoB->getScene());

        _ui->lblInfoWhite->setText("");
        _ui->lblNameWhite->setText("Player White");
        _playerInfoW->setUserProfile(rand() % 39 + 1);
        _ui->gvIconWhite->setScene(_playerInfoW->getScene());
    } else {
        _ui->lblInfoBlack->setText("");
        _ui->lblNameBlack->setText("Player Black");
        _playerInfoB->setUserProfile(rand() % 39 + 1);
        _ui->gvIconBlack->setScene(_playerInfoB->getScene());

        _ui->lblInfoWhite->setText("");
        _ui->lblNameWhite->setText("Player White");
        _playerInfoW->setUserProfile(rand() % 39 + 1);
        _ui->gvIconWhite->setScene(_playerInfoW->getScene());
    }
}

void ChessView::askParameters()
{
    _paramStock = new ParamStock();
    _paramStock->show();
}

void ChessView::connectionToServer()
{
//    _socket = new QTcpSocket();
//    _socket->connectToHost("localhost", 1234);
//    _playerInfoW = nullptr;
    _playerConnection = new PlayerConnection(nullptr, _playerInfoW);
    _playerConnection->show();

    connect(_playerConnection, SIGNAL(login()), this, SLOT(login()));
    connect(_playerConnection, SIGNAL(newAccount()), this, SLOT(newAccount()));

}

void ChessView::sendToStockFish(const std::string & chesspro)
{
    std::cout << moveCmd.toStdString() << chesspro << std::endl;
    QByteArray command(moveCmd + QByteArray::fromStdString(chesspro));
    _stockfish->write(command);
    _stockfish->write("\n go movetime 1000 \n"); // AI can do move in specified time
    while (_stockfish->waitForReadyRead(1000));
    qDebug() << "EXITED";
}

void ChessView::showCheckersStockFish()
{
    qDebug() << "make d cmd ";
    _stockfish->write("\nd\n");
    //if(!_game->isEnded()) while (_stockfish->waitForReadyRead(100));
}

std::string ChessView::moveToStr(std::pair<Position, Position> move)
{
    return positionToStr(move.first) + positionToStr(move.second);

}

std::string ChessView::positionToStr(Position position)
{
    std::string str = "";
    switch (position.y)
    {
    case 0:
        str += 'a';
        break;
    case 1:
        str += 'b';
        break;
    case 2:
        str += 'c';
        break;
    case 3:
        str += 'd';
        break;
    case 4:
        str += 'e';
        break;
    case 5:
        str += 'f';
        break;
    case 6:
        str += 'g';
        break;
    case 7:
        str += 'h';
    }
    str += std::to_string(8 - position.x);
    return str;
}

std::pair<Position, Position> ChessView::strToPosition(std::string str)
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

void ChessView::error(QProcess::ProcessError error)
{
    qDebug() << "Error: " << error;
}

void ChessView::finished(int exitCode,
                         QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished: " << exitCode;
    qDebug() << exitStatus;
    qApp->exit();
}

void ChessView::readyReadStandardError()
{
    qDebug() << "ReadyError";
    std::cout << "Proc Started" << std::endl;
}

void ChessView::readyReadStandardOutput()
{
    //qDebug() << "readyOut";
    QProcess * p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();
    QByteArray token;
    if (buf.contains("bestmove"))
    {
        token = "bestmove ";
        QByteArray moveTok = buf.sliced(buf.indexOf(token) + token.size());
        if (moveTok.contains("(none)"))
        {
            _game->getBoard().setNolegalMoves();
            //showCheckersStockFish();
            this->update(_game);
            //notifyObservers();
        }
        else
        {
            if (_game->getCurrentPlayer() == Side::BLACK)
            {
                std::string move = moveTok.sliced(0, 4).toStdString();
                auto ok = strToPosition(move);
                qDebug() << "Move MADE : " << QString::fromStdString(move);
                _game->move(ok.first, ok.second, Side::BLACK);
                _moves.addMove(move);
                notifyObservers(); //for History
            }
        }
    }
    else if (_game->isEnded() && buf.contains("Checkers:"))
    {
        token = "Checkers:";
        QByteArray checkTok = buf.sliced(buf.indexOf(token) +
                                         token.size());
        qDebug() << "Checkers value :" << checkTok;
        if (checkTok.size() == 0)
        {
            _game->setEndGame(false);
        }
        else
        {
            _game->setEndGame(true);
        }
    }
}

//SIGNALS

void ChessView::start() {
    const QMessageBox::StandardButton ret
            = QMessageBox::information(this, tr("New game ?  :)"),
                                       tr("Do you want to start a new game ?\nThe current game will not be saved."),
                                       QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        //        _game->restart();
    }

}

void ChessView::exit() {
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("Do you want to kill me ?  :'("),
                                   tr("Are you sure to leave us ? The game will not be saved."),
                                   QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        this->close();
    }
}

void ChessView::gameParameters()
{
    std::cout << "SIGNAL RECIEVED : GAME PARAM" << std::endl;
    _PvP = _paramStock->isPvP();

    if(!_PvP){
        connectionToServer();
    }else{
        setupChildrens();
    }
}

void ChessView::login()
{
    std::cout << "SIGNAL RECIEVED : PLAYER CONNECTION" << std::endl;
//    _ui->lblNameWhite->setText(_playerInfoW->getName());
//    _ui->lblInfoWhite->setText(_playerInfoW->getElo());
//    //_ui->lblNatWhite->setText(_playerInfoW->getNat());
//    _playerInfoW->setUserProfile(_playerInfoW->getNumPic());
//    _ui->gvIconWhite->setScene(_playerInfoW->getScene());
    setupChildrens();
}

void ChessView::newAccount()
{
    std::cout << "SIGNAL RECIEVED : NEW PLAYER" << std::endl;
    _newAccount = new NewAccount();
    _newAccount->show();
    connect(_newAccount, SIGNAL(addNewAccount()), this, SLOT(addNewAccount()));
}

void ChessView::addNewAccount()
{
    //TODO add new player to db
    std::cout << "SIGNAL RECIEVED : ADD NEW ACCOUNT" << std::endl;
    setupChildrens();
}

void ChessView::started()
{
    qDebug() << "Proc Started";
    std::cout << "Proc Started" << std::endl;
}

void ChessView::makePause(){
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString ChessView::getCurrentString()
{
    return _game->getCurrentPlayer() == WHITE ? "WHITE" : "BLACK";
}

void ChessView::sendJsonEndGame()
{
    QJsonObject obj;
    obj.insert("message", QJsonValue::fromVariant("endgame"));
    obj.insert("id", QJsonValue::fromVariant(_playerInfoW->getId()));
    obj.insert("moves", QJsonValue::fromVariant(QString::fromStdString(_moves.getMove())));
    if (_game->isEnded()) { //Si la game est gagné par le player
        obj.insert("winnerID", QJsonValue::fromVariant(_playerInfoW->getId()));
    } else {
        obj.insert("winnerID", QJsonValue::fromVariant(1)); //StockFish
    }
    obj.insert("difficulty", QJsonValue::fromVariant("Medium"));
    QJsonDocument doc(obj);
    qDebug() << doc.toJson();
}

void ChessView::displayEndGame()
{
    QString winnerName;
    makePause();
    if(_game->getEndGame()) winnerName = _game->getCurrentPlayer() == WHITE ? "BLACK" : "WHITE";


    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("We got a winner !"), "Congratulations ! " + winnerName + " wins !",
                                   QMessageBox::Close | QMessageBox::Retry);
    if (ret == QMessageBox::Close) {
        this->close();
    } else if (ret == QMessageBox::Retry){
        this->start();
    }
}
