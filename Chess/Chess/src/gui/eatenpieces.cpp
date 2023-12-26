#include "eatenpieces.h"

EatenPieces::EatenPieces(Game * g)
{
    _game = g;
    _blackEatenVec = std::vector<Pieces>{};
    _whiteEatenVec = std::vector<Pieces>{};
    _eatenWhiteScene = new QGraphicsScene();
    _eatenBlackScene = new QGraphicsScene();

    _pieces = getAllPieces();
}

void EatenPieces::update(const nvs::Subject * subject)
{
    if(subject == nullptr) return;
    deleteEatenPiece();

    std::vector<Pieces> current_pieces = getAllPieces();
    std::vector<Pieces> tmp_pieces = current_pieces;

    if (current_pieces.size() < _pieces.size()) { //s'il y a des pièces en moins par rapport au tour d'avant
        for (Pieces piece : _pieces) {
            auto firstItem = std::find(tmp_pieces.begin(), tmp_pieces.end(), piece); //1ere occurence de piece
            if (firstItem == tmp_pieces.end()) { //s'il n'a pas trouvé d'occurence
                //piece is eaten
                if (piece.getColor() == WHITE) {
                    _whiteEatenVec.push_back(piece);
                } else {
                    _blackEatenVec.push_back(piece);
                }
            } else {
                tmp_pieces.erase(firstItem);
            }
        }
    }
    _pieces = current_pieces;
    current_pieces.clear();

    addPiecesToScene();
}

std::vector<Pieces> EatenPieces::getAllPieces() {

    std::vector<Pieces> pieces = std::vector<Pieces>{};

    ChessBoard gameBoard = _game->getBoard().getBoard();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Pieces piece = gameBoard[i][j];
            if (piece.getType() != NONE) {
                pieces.push_back(piece);
            }
        }
    }
    return pieces;
}

PieceItem * EatenPieces::piecesToPieceItem(Pieces piece) {
    PieceType type = piece.getType();
    Side color = piece.getColor();
    std::string path = ":/pieces/";
    PieceItem * PI;
    if (color == WHITE) {
        path += "w";
    } else  {
        path += "b";
    }
    switch(type) {
    case PAWN:
        path += "p.png";
        PI = new PieceItem(path, 0, Point(_indexPawn * WANTED_SIZE, 40), false);
        ++_indexPawn;
        break;
    case BISHOP:
        path += "b.png";
        PI = new PieceItem(path, 0, Point(_indexSpec * WANTED_SIZE, 0), false);
        ++_indexSpec;
        break;
    case KNIGHT:
        path += "n.png";
        PI = new PieceItem(path, 0, Point(_indexSpec * WANTED_SIZE, 0), false);
        ++_indexSpec;
        break;
    case ROOK:
        path += "r.png";
        PI = new PieceItem(path, 0, Point(_indexSpec * WANTED_SIZE, 0), false);
        ++_indexSpec;
        break;
    case QUEEN:
        path += "q.png";
        PI = new PieceItem(path, 0, Point(_indexSpec * WANTED_SIZE, 0), false);
        ++_indexSpec;
        break;
    default:
        PI = nullptr;
        break;
    }

    return PI;
}

void EatenPieces::addPiecesToScene() {

    _indexPawn = 0;
    _indexSpec = 0;

//    if (_blackEatenVec.empty()) {
//        PieceItem * PI = piecesToPieceItem();
//    }
    for (Pieces piece : _blackEatenVec) {
        PieceItem * PI = piecesToPieceItem(piece);
        PI->setScale(SCALE);
        _eatenBlackScene->addItem(PI);
    }


    _indexPawn = 0;
    _indexSpec = 0;

    for (Pieces piece : _whiteEatenVec) {
        PieceItem * PI = piecesToPieceItem(piece);
        PI->setScale(SCALE);
        _eatenWhiteScene->addItem(PI);
    }
}

void EatenPieces::deleteEatenPiece()  {
    _eatenBlackScene->clear();
    _eatenWhiteScene->clear();
}

QGraphicsScene * EatenPieces::getEatenBlackScene() {
    return _eatenBlackScene;
}

QGraphicsScene * EatenPieces::getEatenWhiteScene() {
    return _eatenWhiteScene;
}

EatenPieces::~EatenPieces()
{

}
