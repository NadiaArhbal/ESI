#ifndef VIEW_H
#define VIEW_H
#include <board.h>
#include <Position.h>
#include <iostream>
#include <vector>
#include <game.h>
#include <string>

/**
 * @brief The View class represents the view of the MVC
 */
class View{

private:
    Game _game;

public:

    View()=default;
    /**
     * @brief displayLimiteAndLetter notation for each row of the board
     */
    void displayLimiteAndLetter(int &,int &);
    /**
     * @brief displayBoard display the board
     * @param board the board
     */
    void displayBoard(Board &board);
    /**
     * @brief askPositionUser ask a position from the player
     * @return the character string entered by the user
     */
    std::string askPositionUser();
    /**
     * @brief findPosi under base of 4 integers entered created 2 positions
     * @param x the parameter x of position one
     * @param y the parameter y of position one
     * @param x2 the parameter x of position two
     * @param y2 the parameter y of position two
     * @return a position vector taking the 2 positions(start and end)
     */
    std::vector<Position>findPosi(int x,int y,int x2,int y2);
};

#endif // VIEW_H
