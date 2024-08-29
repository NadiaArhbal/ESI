#ifndef SEQUENCEDB_H
#define SEQUENCEDB_H
#include "DBManager.h"
namespace std
{
/**
 * @brief The SequenceDB class interacts with the SEQUENCE table
 * wich holds all of the current ID indexes of other DATA tables
 */
class SequenceDB
{
  public:
    inline static const string PLAYER = "PLAYER";
    inline static const string GAME = "GAME";
    /**
     * @brief getNextNum increments the ID index for a given TABLE and
     * returns it for table inserts methods
     * @param sequence indicates the SQL's table name
     * @return the id of the next id that a method needs
     */
    static int getNextNum(string sequence);
};
}


#endif // SEQUENCEDB_H
