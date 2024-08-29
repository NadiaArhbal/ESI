#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Position.h"
#include <QUndoCommand>

class moveCommand
{
private:
    QUndoCommand * _command;
    Position _start;
    Position _end;
public:
    moveCommand(Position start, Position end);
    QUndoCommand * getCommand();
    std::string to_string();
};

#endif // MOVECOMMAND_H
