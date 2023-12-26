#include "boardview.h"
#include "chesscore.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtWidgets>

BoardView::BoardView(QGraphicsScene * scene, Game * game, bool *PvP)
    : _scene(scene), _game(game), _PvP(PvP)
{
    _pieces = std::vector<PieceItem*>{};
    _lastWhiteMove = std::make_pair(Position(-1,-1), Position(-1,-1)); //valeure sentinelle
    _lastBlackMove = std::make_pair(Position(-1,-1), Position(-1,-1)); //valeure sentinelle
    setAvailableCoords();
    setAllGamePieces();

    //set background
    QPixmap bg_path(":/board/classic_board_num.png");
    QPixmap sc = bg_path.scaled(SIZE_GV, SIZE_GV);
    _scene->setBackgroundBrush(sc);
}

BoardView::~BoardView()
{

}

std::pair<Position, Position> BoardView::getLastWhiteMove()
{
    return _lastWhiteMove;
}

std::pair<Position, Position> BoardView::getLastBlackMove()
{
    return _lastBlackMove;
}

void BoardView::update(const nvs::Subject * subject){
    if(subject == nullptr) return;
    deletePieces();
    int avCoordIndex = 0;
    int pieceID = 0;
    bool selectable;
    ChessBoard gameBoard = _game->getBoard().getBoard();

    //selectable color
    Side selectableColor;
    if(*_PvP){
        selectableColor = _game->getCurrentPlayer();
    }else if(_game->getCurrentPlayer() == WHITE){
        selectableColor = WHITE;
    }else{
        selectableColor = EMPTY;
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Point p = _availableCoords.at(avCoordIndex);
            Pieces piece = gameBoard[i][j];
            if(piece.getType() != NONE){
                selectable = (piece.getColor() == selectableColor);
                PieceItem *PI = new PieceItem(
                            pieceToPath(piece),
                            pieceID,
                            p,
                            selectable,
                            this);
                _scene->addItem(PI);
                _pieces.push_back(PI);
                pieceID++;
            }
            avCoordIndex++;
        }
    }
}

void BoardView::newPieceSelected(int pieceID){
    std::cout << "selected piece id: " << pieceID << std::endl;
    deSelectOtherPieces(pieceID);//deselect all without the one clicked now
    _selectedPieceID = pieceID;
    setAllGamePieces();

    std::vector<Position> possiblePositions;
    possiblePositions = getPossibleLandings(_allGamePieces.at(_selectedPieceID));
    std::vector<Point> guiPoints = chessCorePositionsToGuiPoints(possiblePositions);

    setChips(guiPoints);
}

void BoardView::newChipSelected(int chipID){
    std::cout << "selected chip id: " << chipID << std::endl;
    Position start = pointToPosition(_pieces.at(_selectedPieceID)->getCoord());
    Position end = pointToPosition(_landingChips.at(chipID)->getCoord());
    Side side = _game->getBoard().getBoard()[start.x][start.y].getColor();

    deleteChips();
    if(_game->getCurrentPlayer() == WHITE){
        _lastWhiteMove = std::make_pair(start, end);
    }else{
        _lastBlackMove = std::make_pair(start, end);
    }

    _game->move(start, end, side);
}

void BoardView::deletePieces(){
    for(auto piece : _pieces){
        _scene->removeItem(piece);
    }
    _pieces = std::vector<PieceItem *>{};
}

void BoardView::deleteChips(){
    for(auto chip : _landingChips){
        _scene->removeItem(chip);
    }
    _landingChips = std::vector<LandingChipItem *>{};
}

void BoardView::deSelectOtherPieces(int IDToNotDeselect){
    int i = 0;
    for(auto piece : _pieces){
        if(i != IDToNotDeselect) piece->deSelect();
        i++;
    }
}

void BoardView::setChips(std::vector<Point> points){
    deleteChips();
    int chipID = 0;
    for(Point p : points){
        LandingChipItem *LCI = new LandingChipItem(chipID, p, this);
        _scene->addItem(LCI);
        _landingChips.push_back(LCI);
        chipID++;
    }
}

//TODO x et y inversés
Point BoardView::positionToPoint(Position position){
    double xAxis = position.y * SPACE_BTW_PIECES;
    double yAxis = position.x * SPACE_BTW_PIECES;

    return Point(xAxis, yAxis);
}

Position BoardView::pointToPosition(Point point){
    int x = point.Y() / SPACE_BTW_PIECES;
    int y = point.X() / SPACE_BTW_PIECES;

    return Position(x, y);
}

std::vector<Point> BoardView::chessCorePositionsToGuiPoints(std::vector<Position> positions){
    std::vector<Point> guiPoints = std::vector<Point>{};

    for(Position position : positions){
        guiPoints.push_back(positionToPoint(position));
    }
    return guiPoints;
}

std::vector<Position> BoardView::doubleVectorToVector(std::vector<std::vector<Position>> positions){
    std::vector<Position> vect = std::vector<Position>{};
    for(const auto &v : positions){
        for(Position p : v){
            vect.push_back(p);
        }
    }
    return vect;
}

std::vector<Position> BoardView::getPossibleLandings(Pieces piece){
    Board gameBoard = _game->getBoard();
    std::vector<Position> positions;


    switch (piece.getType()) {
    case PAWN:
        positions = gameBoard.pawnListMove(piece.getPos());
        break;
    case BISHOP:
        positions = gameBoard.bishopListMove(piece.getPos());
        break;
    case KNIGHT:
        positions = gameBoard.knightListMove(piece.getPos());
        break;
    case ROOK:
        positions = doubleVectorToVector(gameBoard.rookListMove(piece.getPos()));
        break;
    case QUEEN:
        positions = doubleVectorToVector(gameBoard.queenListMove(piece.getPos()));
        break;
    case KING:
        positions = gameBoard.kingListMove(piece.getPos());
        break;
    default:
        break;
    }
    return positions;
}

std::string BoardView::pieceToPath(Pieces piece){
    std::string path = ":/pieces/";

    switch (piece.getColor()){
    case WHITE:
        path += "w";
        break;
    case BLACK:
        path += "b";
        break;
    default:
        path = "";
    }

    switch (piece.getType()) {
    case PAWN:
        path += "p";
        break;
    case BISHOP:
        path += "b";
        break;
    case KNIGHT:
        path += "n";
        break;
    case ROOK:
        path += "r";
        break;
    case QUEEN:
        path += "q";
        break;
    case KING:
        path += "k";
        break;
    default:
        path = "p";
    }

    return path + ".png";
}

void BoardView::setAllGamePieces(){
    _allGamePieces = std::vector<Pieces>{};
    ChessBoard gameBoard = _game->getBoard().getBoard();
    //int pieceID = 0;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Pieces piece = gameBoard[i][j];
            if(piece.getType() != NONE){
                _allGamePieces.push_back(piece);
                //pieceID++;
            }
        }
    }
}

void BoardView::setAvailableCoords(){
    _availableCoords = std::vector<Point>();
    int xAxis = 0;
    int yAxis = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            _availableCoords.push_back(Point(xAxis, yAxis));
            xAxis += SPACE_BTW_PIECES;
        }
        xAxis = 0;
        yAxis += SPACE_BTW_PIECES;
    }
}



















