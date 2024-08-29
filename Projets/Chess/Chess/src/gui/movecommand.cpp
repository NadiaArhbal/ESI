#include "movecommand.h"

moveCommand::moveCommand(Position start, Position end)
    : _start(start), _end(end)
{

}

QUndoCommand *moveCommand::getCommand()
{
    return _command;
}
