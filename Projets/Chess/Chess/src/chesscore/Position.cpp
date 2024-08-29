#include <Position.h>

Position operator-(Position pos,Position pos2){
   return Position(pos.x-pos2.x,pos.y-pos2.y);
}

Position operator+(Position pos,Position pos2){
   return Position(pos.x+ pos2.x,pos.y+pos2.y);
}


bool operator==(Position pos,Position pos2){
   return ((pos.x == pos2.x)&&(pos.y == pos2.y));
}


bool operator!=(Position pos,Position pos2){
   return ! (pos==pos2);
}
