#include "game.h"

Game::Game():
    board_{Board()},currentPlayer_{WHITE}
{}

void Game::move(Position start,Position end, Side side){
    board_.deplacementPieces(start,end, side);
    if(board_.checkPromotion(end, side)){
        board_.setSpecialPromotion(true);
    }
    swapSide();
    notifyObservers();
}

void Game::promotion(Position pos, PieceType type) {
    board_.givePromotion(pos, type);
    board_.setSpecialPromotion(false);
    //swapSide();
    notifyObservers();
}

