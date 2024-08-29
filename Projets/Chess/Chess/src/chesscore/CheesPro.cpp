#include <ChessPro.h>

bool checkCorrectLetters(char c){
    std::string authorized="ABCDEFGHabcdefgh";

    for(size_t j=0;j<authorized.length();j++){
        if(c==authorized.at(j)){
            return true;
        }
    }
    return false;
}

bool checkCorrectNumbers(char c){
    std::string authorized="12345678";

    for(size_t j=0;j<authorized.length();j++){
        if(c==authorized.at(j)){
            return true;
        }
    }
    return false;
}

int getXFromChar(char c){
    char b =std::toupper(c);
    switch (b) {
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;
    case 'D':
        return 4;
    case 'E':
        return 5;
    case 'F':
        return 6;
    case 'G':
        return 7;
    case 'H':
        return 8;
    default:throw std::invalid_argument("Invalid input letters");
    }
}

//à vérif pr les +
int getYFromChar(char lettre,char  nombre){

    auto getX = getXFromChar(lettre);

    switch (nombre) {
    case '1':
        return getX-3;
    case '2':
        return getX-2;
    case '3':
        return getX-1;
    case '4':
        return getX;
    case '5':
        return getX+1;
    case '6':
        return getX+2;
    case '7':
        return getX+3;
    case '8':
        return getX+4;
    default:throw std::invalid_argument("Invalid input numbers");
    }
}

std::vector<Position> findPositionFromChessPro(std::string chesspro){

    std::vector<Position> positions{};
    if(chesspro.length()!=4){
        std::cout<<"Invalid chesspro"<<std::endl;
        return positions;
    }


    for(size_t i=0;i<chesspro.length();i++){
        if(i%2==0) {
            if (!isalpha(chesspro.at(i))||!checkCorrectLetters(chesspro.at(i))){
                std::cout<<"Not alpha";
                return positions;
            }

        }else if(!checkCorrectNumbers(chesspro.at(i))){
            std::cout<<"Not digit"<<std::endl;
            return positions;
        }
    }


    int x,y,x2,y2;

    x=getXFromChar(chesspro.at(0));
    y = (getYFromChar(chesspro.at(0),chesspro.at(1)));

    positions.push_back(Position(x,y));

    x2 = (getXFromChar(chesspro.at(2)));
    y2=getYFromChar(chesspro.at(2),chesspro.at(3));

    positions.push_back(Position(x2,y2));

    return positions;
}






