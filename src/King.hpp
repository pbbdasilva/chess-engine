#pragma once

#include "Piece.hpp"

class King : public Piece {
public:
    King(Player who, int i, int j);
    PieceType whichType();

    bool validMove(int i, int j, MoveType type, Player turn);
    std::vector<std::pair<int,int>> genMoves(const std::vector<std::vector<Piece*>>& t);
};