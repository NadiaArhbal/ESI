#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H
#include <string>
/**
 * @brief The MessageType enum represents the messages type that the server can support
 */
enum MessageType
{
    NEW,
    LOGIN,
    ENDGAME,
    CONNECTED,
    UNDEFINED

};

#endif // MESSAGETYPE_H

