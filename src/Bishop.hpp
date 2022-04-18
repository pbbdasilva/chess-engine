#pragma once

#include "Piece.hpp"

class Bishop : public Piece {
public:
    Bishop(Player who, int i, int j);
    PieceType whichType();

    bool validMove(int i, int j, MoveType type, Player turn);
    std::vector<std::pair<int,int>> genMoves(const std::vector<std::vector<Piece*>>& t);
    int mobilityMultiplier();
};