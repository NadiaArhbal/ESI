#include <catch2/catch.hpp>
#include <iostream>
#include <pieces.h>
#include <board.h>
#include <Side.h>
#include <Position.h>

TEST_CASE("Testing Board constructor", "[fancy]")
{
    try
    {
        Board b = Board();
        b.displayBoard();
        SUCCEED();

    }
    catch (const std::exception & e)
    {
        FAIL();
    }
}

TEST_CASE("Testing black pawn deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,1), Position(2,1), Side::BLACK);
    REQUIRE(b.getBoard().at(1).at(1).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(1).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(2).at(1).getType() == PieceType::PAWN);
    REQUIRE(b.getBoard().at(2).at(1).getColor() == Side::BLACK);
}

TEST_CASE("Testing white pawn deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,1), Position(5,1), Side::WHITE);
    REQUIRE(b.getBoard().at(6).at(1).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(6).at(1).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(5).at(1).getType() == PieceType::PAWN);
    REQUIRE(b.getBoard().at(5).at(1).getColor() == Side::WHITE);
}

TEST_CASE("Testing white pawn eat black pawn deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,1), Position(5,1), Side::WHITE);
    b.deplacementPieces(Position(5,1), Position(4,1), Side::WHITE);
    b.deplacementPieces(Position(4,1), Position(3,1), Side::WHITE);
    b.deplacementPieces(Position(3,1), Position(2,1), Side::WHITE);
    b.deplacementPieces(Position(2,1), Position(1,2), Side::WHITE);
    REQUIRE(b.getBoard().at(1).at(2).getType() == PieceType::PAWN);
    REQUIRE(b.getBoard().at(1).at(2).getColor() == Side::WHITE);
}

TEST_CASE("Testing white pawn promotion", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,1), Position(5,1), Side::WHITE);
    b.deplacementPieces(Position(1,1), Position(2,1), Side::BLACK);
    b.deplacementPieces(Position(5,1), Position(4,1), Side::WHITE);
    b.deplacementPieces(Position(4,1), Position(3,1), Side::WHITE);
}

TEST_CASE("Testing white pawn out of board deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,1), Position(5,1), Side::WHITE);
    b.deplacementPieces(Position(1,1), Position(2,1), Side::BLACK);
    b.deplacementPieces(Position(5,1), Position(4,1), Side::WHITE);
    b.deplacementPieces(Position(4,1), Position(3,1), Side::WHITE);
    REQUIRE(b.getBoard().at(3).at(1).getColor() == Side::WHITE);
}

TEST_CASE("Testing black knight deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(0,1), Position(2,0), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(1).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(2).at(0).getColor() == Side::BLACK);
}

TEST_CASE("Testing black pawn eat white pawn pieces deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,2), Position(5,2), Side::WHITE);
    b.deplacementPieces(Position(5,2), Position(4,2), Side::WHITE);
    b.deplacementPieces(Position(4,2), Position(3,2), Side::WHITE);
    b.deplacementPieces(Position(3,2), Position(2,2), Side::WHITE);
    b.deplacementPieces(Position(0,1), Position(2,2), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(1).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(2).at(2).getColor() == Side::BLACK);
}


TEST_CASE("Testing black rook deplacement deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,0), Position(3,0), Side::BLACK);
    b.deplacementPieces(Position(0,0), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(2,0), Position(2,7), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(7).getColor() == Side::BLACK);
}

TEST_CASE("Testing black rook eat horizontale white pawn deplacement deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,0), Position(3,0), Side::BLACK);
    b.deplacementPieces(Position(0,0), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(2,0), Position(2,7), Side::BLACK);
    b.deplacementPieces(Position(2,7), Position(2,5), Side::BLACK);
    b.deplacementPieces(Position(2,5), Position(6,5), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(6).at(5).getColor() == Side::BLACK);
}

TEST_CASE("Testing black rook horizontale impossible deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,0), Position(3,0), Side::BLACK);
    b.deplacementPieces(Position(0,0), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(2,0), Position(2,7), Side::BLACK);
    b.deplacementPieces(Position(2,7), Position(2,5), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(5).getColor() == Side::BLACK);
}

TEST_CASE("Testing black rook eat verticale white pawn deplacement deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,0), Position(3,0), Side::BLACK);
    b.deplacementPieces(Position(0,0), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(2,0), Position(2,7), Side::BLACK);
    b.deplacementPieces(Position(2,7), Position(2,5), Side::BLACK);
    b.deplacementPieces(Position(2,5), Position(6,5), Side::BLACK);
    b.deplacementPieces(Position(6,5), Position(6,4), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(6).at(4).getColor() == Side::BLACK);
}

TEST_CASE("Testing black rook verticale impossible deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,0), Position(3,0), Side::BLACK);
    b.deplacementPieces(Position(0,0), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(2,0), Position(2,7), Side::BLACK);
    b.deplacementPieces(Position(2,7), Position(2,5), Side::BLACK);
    b.deplacementPieces(Position(2,5), Position(6,5), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(6).at(5).getColor() == Side::BLACK);
}

TEST_CASE("Testing black bishop eat diagonale white pawn deplacement deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,3), Position(3,3), Side::BLACK);
    b.deplacementPieces(Position(0,2), Position(4,6), Side::BLACK);
    b.deplacementPieces(Position(4,6), Position(6,4), Side::BLACK);
    REQUIRE(b.getBoard().at(1).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(0).at(2).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(3).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(6).at(4).getColor() == Side::BLACK);
}

TEST_CASE("Testing black bishop diagonale impossible deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,3), Position(3,3), Side::BLACK);
    b.deplacementPieces(Position(0,2), Position(4,6), Side::BLACK);
    REQUIRE(b.getBoard().at(1).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(0).at(2).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(3).getColor() == Side::BLACK);
}


TEST_CASE("Testing black rook impossible deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,0), Position(3,0), Side::BLACK);
    b.deplacementPieces(Position(0,0), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(2,0), Position(2,7), Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(0).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(7).getColor() == Side::BLACK);
}

TEST_CASE("Testing WHITE great rocket deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(7,1), Position(5,2), Side::WHITE);
    b.deplacementPieces(Position(6,1), Position(5,1), Side::WHITE);
    b.deplacementPieces(Position(7,2), Position(6,1), Side::WHITE);
    b.deplacementPieces(Position(6,3), Position(5,3), Side::WHITE);
    b.deplacementPieces(Position(7,3), Position(6,3), Side::WHITE);
    b.deplacementPieces(Position(7,4), Position(7,2), Side::WHITE);
    REQUIRE(b.getBoard().at(5).at(2).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(5).at(1).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(6).at(1).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(7).at(2).getType() == PieceType::KING);
    REQUIRE(b.getBoard().at(7).at(3).getType() == PieceType::ROOK);
}

TEST_CASE("Testing BLACK great rocket deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,3), Position(2,3), Side::BLACK);
    b.deplacementPieces(Position(0,2), Position(1,3), Side::BLACK);
    b.deplacementPieces(Position(1,3), Position(2,4), Side::BLACK);
    b.deplacementPieces(Position(0,1), Position(2,0), Side::BLACK);
    b.deplacementPieces(Position(0,3), Position(1,3), Side::BLACK);
    b.deplacementPieces(Position(0,4), Position(0,2), Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(3).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(4).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(0).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(2).getType() == PieceType::KING);
    REQUIRE(b.getBoard().at(0).at(3).getType() == PieceType::ROOK);
}

TEST_CASE("Testing BLACK little rocket deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(0,6), Position(2,5), Side::BLACK);
    b.deplacementPieces(Position(1,6), Position(2,6), Side::BLACK);
    b.deplacementPieces(Position(0,5), Position(1,6), Side::BLACK);
    b.deplacementPieces(Position(0,4), Position(0,6), Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(5).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(6).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(1).at(6).getColor() == Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(6).getType() == PieceType::KING);
    REQUIRE(b.getBoard().at(0).at(5).getType() == PieceType::ROOK);
}

TEST_CASE("Testing WHITE little rocket deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(7,6), Position(5,7), Side::WHITE);
    b.deplacementPieces(Position(6,6), Position(5,6), Side::WHITE);
    b.deplacementPieces(Position(7,5), Position(6,6), Side::WHITE);
    b.deplacementPieces(Position(7,4), Position(7,6), Side::WHITE);
    REQUIRE(b.getBoard().at(5).at(7).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(5).at(6).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(6).at(6).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(7).at(6).getType() == PieceType::KING);
    REQUIRE(b.getBoard().at(7).at(5).getType() == PieceType::ROOK);
}

TEST_CASE("Testing white bishop deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,4), Position(4,4), Side::WHITE);
    b.deplacementPieces(Position(7,5), Position(5,3), Side::WHITE);
    REQUIRE(b.getBoard().at(6).at(4).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(6).at(4).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(4).at(4).getColor() == Side::WHITE);
    REQUIRE(b.getBoard().at(5).at(3).getColor() == Side::WHITE);
}

TEST_CASE("Testing white queen deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,3), Position(4,3), Side::WHITE);
    b.deplacementPieces(Position(7,3), Position(5,3), Side::WHITE);
    b.deplacementPieces(Position(5,3), Position(5,4), Side::WHITE);
    REQUIRE(b.getBoard().at(6).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(6).at(3).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(5).at(4).getColor() == Side::WHITE);
}

TEST_CASE("Testing black Queen diagonale deplacement who eats a pawn","[board]"){
    Board b = Board();
    b.deplacementPieces(Position(1,3),Position(3,3),Side::BLACK);
    b.deplacementPieces(Position(0,3),Position(2,3),Side::BLACK);
    b.deplacementPieces(Position(2,3),Position(6,7),Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(3).getType()==PieceType::NONE);
    REQUIRE(b.getBoard().at(1).at(3).getType()==PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(3).getType()==PieceType::PAWN);
    REQUIRE(b.getBoard().at(6).at(7).getType()==PieceType::QUEEN);
}

TEST_CASE("Testing black queen horizontal deplacement","[board]"){
    Board b = Board();
    b.deplacementPieces(Position(1,3),Position(3,3),Side::BLACK);
    b.deplacementPieces(Position(6,3),Position(4,3),Side::WHITE);
    b.deplacementPieces(Position(0,3),Position(2,3),Side::BLACK);
    REQUIRE(b.getBoard().at(0).at(3).getType()==PieceType::NONE);
    REQUIRE(b.getBoard().at(2).at(3).getType()==PieceType::QUEEN);
}

TEST_CASE("Testing black queen horizontal","[board]"){
    Board b = Board();
    b.deplacementPieces(Position(1,3),Position(3,3),Side::BLACK);
    b.deplacementPieces(Position(0,3),Position(2,3),Side::BLACK);
    b.deplacementPieces(Position(6,7),Position(5,7),Side::WHITE);
    b.deplacementPieces(Position(5,7),Position(4,7),Side::WHITE);
    b.deplacementPieces(Position(4,7),Position(3,7),Side::WHITE);
    b.deplacementPieces(Position(3,7),Position(2,7),Side::WHITE);
    b.deplacementPieces(Position(2,3),Position(2,7),Side::BLACK);
    REQUIRE(b.getBoard().at(2).at(7).getType()==PieceType::QUEEN);
    REQUIRE(b.getBoard().at(6).at(7).getType()==PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(3).getType()==PieceType::PAWN);
}

TEST_CASE("Testing white Queen diagonale deplacement who eats a pawn","[board]"){
    Board b = Board();
    b.deplacementPieces(Position(6,3),Position(4,3),Side::WHITE);
    b.deplacementPieces(Position(7,3),Position(5,3),Side::WHITE);
    b.deplacementPieces(Position(1,4),Position(3,4),Side::BLACK);
    b.deplacementPieces(Position(3,4),Position(4,4),Side::BLACK);
    b.deplacementPieces(Position(5,3),Position(4,4),Side::WHITE);
    REQUIRE(b.getBoard().at(5).at(3).getType()==PieceType::NONE);
    REQUIRE(b.getBoard().at(4).at(4).getType()==PieceType::QUEEN);
}

TEST_CASE("Testing white Queen vertical deplacement who eats a queen","[board]"){
    Board b = Board();
    b.deplacementPieces(Position(6,3),Position(4,3),Side::WHITE);
    b.deplacementPieces(Position(1,3),Position(3,3),Side::BLACK);
    b.deplacementPieces(Position(1,4),Position(3,4),Side::BLACK);
    b.deplacementPieces(Position(4,3),Position(3,4),Side::WHITE);
    b.deplacementPieces(Position(7,3),Position(4,3),Side::WHITE);
    b.deplacementPieces(Position(4,3),Position(3,3),Side::WHITE);
    REQUIRE(b.getBoard().at(4).at(3).getType()==PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(3).getType()==PieceType::QUEEN);
}

TEST_CASE("Testing white king deplacement", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,4), Position(5,4), Side::WHITE);
    b.deplacementPieces(Position(7,4), Position(6,4), Side::WHITE);
    b.deplacementPieces(Position(5,4), Position(4,4), Side::WHITE);
    b.deplacementPieces(Position(6,4), Position(5,5), Side::WHITE);
    REQUIRE(b.getBoard().at(7).at(4).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(6).at(4).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(5).at(5).getColor() == Side::WHITE);
}

TEST_CASE("Testing enPassant white", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,3), Position(4,3), Side::WHITE);
    b.deplacementPieces(Position(4,3), Position(3,3), Side::WHITE);
    b.deplacementPieces(Position(1,2), Position(3,2), Side::BLACK);
    b.deplacementPieces(Position(3,3), Position(2,2), Side::WHITE);
    REQUIRE(b.getBoard().at(3).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(2).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(2).at(2).getColor() == Side::WHITE);
}

TEST_CASE("Testing enPassant white v2", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(6,3), Position(4,3), Side::WHITE);
    b.deplacementPieces(Position(4,3), Position(3,3), Side::WHITE);
    b.deplacementPieces(Position(1,4), Position(3,4), Side::BLACK);
    b.deplacementPieces(Position(3,3), Position(2,4), Side::WHITE);
    REQUIRE(b.getBoard().at(3).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(3).at(4).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(2).at(4).getColor() == Side::WHITE);
}

TEST_CASE("Testing enPassant black", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,3), Position(3,3), Side::BLACK);
    b.deplacementPieces(Position(3,3), Position(4,3), Side::BLACK);
    b.deplacementPieces(Position(6,4), Position(4,4), Side::WHITE);
    b.deplacementPieces(Position(4,3), Position(5,4), Side::BLACK);
    REQUIRE(b.getBoard().at(4).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(4).at(4).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(5).at(4).getColor() == Side::BLACK);
}

TEST_CASE("Testing enPassant black V2", "[board]") {
    Board b = Board();
    b.deplacementPieces(Position(1,3), Position(3,3), Side::BLACK);
    b.deplacementPieces(Position(3,3), Position(4,3), Side::BLACK);
    b.deplacementPieces(Position(6,2), Position(4,2), Side::WHITE);
    b.deplacementPieces(Position(4,3), Position(5,2), Side::BLACK);
    REQUIRE(b.getBoard().at(4).at(3).getType() == PieceType::NONE);
    REQUIRE(b.getBoard().at(4).at(2).getColor() == Side::EMPTY);
    REQUIRE(b.getBoard().at(5).at(2).getColor() == Side::BLACK);
}



