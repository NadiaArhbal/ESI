#ifndef HISTORY_H
#define HISTORY_H

#include "observer/observer.h"
#include "observer/subject.h"
#include "game.h"
#include "../tui/ChessPro.h"

#include <QUndoStack>
#include <QTableWidget>
#include <sstream>

class History : public nvs::Observer
{
private:
    ChessPro * _moves;
    QTableWidget * _tw;

public:
    /**
     * @brief History Constructor of the History of the Chess game
     * @param tw the QTableWidget to display
     * @param moves all the moves of the Game
     */
    History(QTableWidget * tw, ChessPro * moves);

    /**
     * @brief update update the view
     * @param subject the Game
     */
    virtual void update(const nvs::Subject * subject);

    /**
     * @brief getNbMoves Getter of the number of moves in the current Game
     * @param moves all the moves of the current game
     * @return the number of the moves of the Game
     */
    int getNbMoves(std::string moves);

    /**
     * @brief clear clear all the history
     */
    void clear();

    /**
     * @brief init Initialize the Table Widget to get the moves
     * @param moves all the moves of the Game
     */
    void init(std::string moves);

    /**
     * @brief getMoves Getter of the Moves
     * @return the moves
     */
    ChessPro * getMoves();

    /**
     * @brief ~History Destructor of the History
     */
    virtual ~History();
};

#endif // HISTORY_H
