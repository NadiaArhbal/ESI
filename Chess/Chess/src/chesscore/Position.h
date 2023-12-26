#ifndef POSITION_H
#define POSITION_H
/**
 * @brief The Position struct that allows us to locate cells
 * in the board
 */
struct Position
{
    int x;
    int y;
    /**
     * @brief Position creates an 0,0 position
     */
    inline Position();
    /**
     * @brief Position constructs desired point
     * @param x desired x value
     * @param y desired y value
     */
    inline Position(int x, int y);
};
/**
 * @brief Position obligatory typedef to avoid adding struct keyword
 */
typedef struct Position Position ;

inline Position::Position()
{
    x = 0;
    y = 0;
}

inline Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}


/*!
 * \brief operator - redefinition of an operator
 * \return  Position
 */
Position operator- (Position pos,Position pos2);
/*!
 * \brief operator - redefinition of an operator
 * \return  Position
 */
Position operator+(Position pos,Position pos2);
/*!
 * \brief operator - redefinition of an operator
 * \return  Position
 */
bool operator==(Position pos,Position pos2);
/*!
 * \brief operator !- redefinition of an operator
 * \return  Position
 */
bool operator!=(Position pos,Position pos2);



#endif // POSITION_H
