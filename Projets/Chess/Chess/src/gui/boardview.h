#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "observer/observer.h"
#include "observer/subject.h"
#include "game.h"
#include "pieceitem.h"
#include "landingchipitem.h"
#include "chesscore.h"
#include <QMouseEvent>
#include <vector>

class PieceItem;
class LandingChipItem;

/**
 * @brief The BoardView class will represent the game's board
 */
class BoardView : public nvs::Observer
{
private:
    QGraphicsScene * _scene;
    Game * _game;
    std::vector<PieceItem *> _pieces;
    std::vector<LandingChipItem *> _landingChips;
    std::vector<Point> _availableCoords;
    std::vector<Pieces> _allGamePieces;
    int _selectedPieceID;
    std::pair<Position, Position> _lastWhiteMove;
    std::pair<Position, Position> _lastBlackMove;

    const int SPACE_BTW_PIECES = 75;
    const int SIZE_GV = 600;
    const bool* _PvP;

    /**
     * @brief deletePieces deletes all the PieceItems of the scene
     */
    void deletePieces();

    /**
     * @brief deleteChips deletes all the LandingChipItems of the scene
     */
    void deleteChips();

    /**
     * @brief deSelectOtherPieces deselects all the PieceItems except the Piece
     * with the id given in parameters
     * @param ID piece id to not deselect
     */
    void deSelectOtherPieces(int ID);

    /**
     * @brief setAllGamePieces scans the game's board and store all the game's Pieces
     */
    void setAllGamePieces();

    /**
     * @brief setAvailableCoords gives to BoardView the available graphical coordinates
     * that a PieceItem can take
     */
    void setAvailableCoords();

    /**
     * @brief setChips sets the LandingChipsItems at the positions (Point) given
     * in parameters
     */
    void setChips(std::vector<Point>);

    /**
     * @brief getPossibleLandings returns a vector that will contain all the possible
     * Positions that a Piece given in parameters can go
     * @return std::vector<Position>
     */
    std::vector<Position> getPossibleLandings(Pieces);

    /**
     * @brief pieceToPath translates a Piece to the correct ressources path (.png)
     * @return std::string path
     */
    std::string pieceToPath(Pieces);

    /**
     * @brief chessCorePositionsToGuiPoints translates a vector of ChessCore Positions
     * into a vector of graphical Points
     * @return std::vector<Point> list of graphical points
     */
    std::vector<Point> chessCorePositionsToGuiPoints(std::vector<Position>);

    /**
     * @brief positionToPoint translates a Position given in parameters into a
     * graphical Point
     * @return Point
     */
    Point positionToPoint(Position);

    /**
     * @brief pointToPosition translates a graphical Point given in parameters into a
     * ChessCore Position
     * @return Position
     */
    Position pointToPosition(Point);

    /**
     * @brief doubleVectorToVector translates a double vector into a simple vector
     * @return std::vector<Positions>
     */
    std::vector<Position> doubleVectorToVector(std::vector<std::vector<Position>>);

public:
    /**
     * @brief BoardView constructor that takes a QGraphicsScene and a Game to represent
     * @param PvP boolean to know if player is going to play with another irl player or
     * against stockfish
     */
    BoardView(QGraphicsScene *, Game *, bool* PvP);

    /**
     * @brief update refresh the BoardView
     * @param subject to observe
     */
    virtual void update(const nvs::Subject * subject);// = 0

    /**
     * @brief ~BoardView Destructor
     */
    virtual ~BoardView();

    /**
     * @brief getLastWhiteMove getter for last White Player move
     * @return std::pair<Position, Position> pair of start and end Position
     */
    std::pair<Position, Position> getLastWhiteMove();

    /**
     * @brief getLastWhiteMove getter for last Black Player move
     * @return std::pair<Position, Position> pair of start and end Position
     */
    std::pair<Position, Position> getLastBlackMove();

    /**
     * @brief newPieceSelected called by a PieceItem to refresh the view and show
     * the LandingChipsItems corresponding to the selected Piece
     * @param pieceID selected
     */
    void newPieceSelected(int pieceID);

    /**
     * @brief newChipSelected called by a LandingChipItem to refresh the view and
     * do the move on the Game
     * @param chipID selected
     */
    void newChipSelected(int chipID);
};

#endif // BOARDVIEW_H
