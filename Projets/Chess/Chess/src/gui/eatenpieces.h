#ifndef EATENPIECES_H
#define EATENPIECES_H

#include "observer/observer.h"
#include "observer/subject.h"
#include "game.h"
#include "pieceitem.h"
#include <QGraphicsScene>
#include <algorithm>

class EatenPieces : public nvs::Observer
{
private:
    Game * _game;
    QGraphicsScene * _eatenBlackScene;
    QGraphicsScene * _eatenWhiteScene;
    std::vector<Pieces> _blackEatenVec;
    std::vector<Pieces> _whiteEatenVec;

    std::vector<Pieces> _pieces;

    int _indexPawn = 0;
    int _indexSpec = 0;

    double SIZE_IMG = 800;
    double WANTED_SIZE = 32;
    double SCALE = WANTED_SIZE / SIZE_IMG;

public:
    /**
     * @brief EatenPieces Constructor of the eaten piece part of the GUI.
     * It display the pieces eaten by player Black and White
     * @param game the game of chess
     */
    EatenPieces(Game * game);

    /**
     * @brief update Update the view
     * @param subject the Game
     */
    virtual void update(const nvs::Subject * subject);

    /**
     * @brief getEatenBlackScene Getter of the QGraphicsScene of the pieces eaten by Black.
     * @return the QGraphicsScene of the pieces eaten by Black.
     */
    QGraphicsScene * getEatenBlackScene();

    /**
     * @brief getEatenWhiteScene Getter of the QGraphicsScene of the pieces eaten by White.
     * @return the QGraphicsScene of the pieces eaten by White.
     */
    QGraphicsScene * getEatenWhiteScene();

    /**
     * @brief getAllPieces Getter of all the pieces of the game
     * @return all the pieces of the game
     */
    std::vector<Pieces> getAllPieces();

    /**
     * @brief piecesToPieceItem Make a PieceItem from a Pieces
     * @param piece the piece to transform
     * @return the pointer of the new PieceItem
     */
    PieceItem * piecesToPieceItem(Pieces piece);

    /**
     * @brief addPiecesToScene Add a PieceItem to one of the Scene
     */
    void addPiecesToScene();

    /**
     * @brief deleteEatenPiece Delete all the pieces in the Scenes
     */
    void deleteEatenPiece();

    /**
     * @brief ~EatenPieces Desctructor of EatenPiece
     */
    virtual ~EatenPieces();
};

#endif // EATENPIECES_H
