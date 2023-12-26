#ifndef CHESSPRO_H
#define CHESSPRO_H
#include <Position.h>
#include <iostream>
#include <vector>

class ChessPro {
public:
};

std::vector<Position> findPositionFromChessPro(std::string chesspro);
bool checkCorrectLetters(char c);
bool checkCorrectNumbers(char c);
int getXFromChar(char c);
int getYFromChar(char c,char);


#endif // CHESSPRO_H
