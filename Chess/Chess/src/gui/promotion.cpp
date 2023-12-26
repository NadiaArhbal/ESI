#include "promotion.h"
#include "ui_promotion.h"

Promotion::Promotion(Game * game, Position pos, QWidget *parent) :
    QDialog(parent),
    _game(game),
    _position(pos),
    _ui(new Ui::Promotion)
{
    _ui->setupUi(this);
    setWindowIcon(QIcon(":/icon_chess/ChessIcon.ico"));
    setWindowTitle("Promotion");

    QGraphicsScene * scene = new QGraphicsScene(this);
    _pieces = std::vector<PieceItem *>{};
    std::string path = ":/pieces/";
    std::string ext = ".png";

    switch (_game->getCurrentPlayer()){
    case WHITE:
        path += "b";
        break;
    case BLACK:
        path += "w";
        break;
    default:
        path = "";
    }

    _pieces.push_back(new PieceItem(path+"q"+ext, 0, Point(0,0), true)); //Queen
    _pieces.push_back(new PieceItem(path+"n"+ext, 1, Point(125,0), true)); //Knight
    _pieces.push_back(new PieceItem(path+"b"+ext, 2, Point(250,0), true)); //Bishop
    _pieces.push_back(new PieceItem(path+"r"+ext, 3, Point(375,0), true)); //Rook

    for(auto p : _pieces) scene->addItem(p);

    _ui->gvPromotion->setScene(scene);
}

Promotion::~Promotion()
{
    delete _ui;
}

void Promotion::on_buttonBox_accepted()
{
    //_game->getBoard().setSpecialPromotion(true);
    switch (getIDSelected()) {
    case 0:
        _game->promotion(_position, QUEEN);
        break;
    case 1:
        _game->promotion(_position, KNIGHT);
        break;
    case 2:
        _game->promotion(_position, BISHOP);
        break;
    case 3:
        _game->promotion(_position, ROOK);
        break;
    }
}

int Promotion::getIDSelected()
{
    for(auto pi : _pieces){
        if(pi->isSelected()) return pi->getId();
    }
    return -1;
}

