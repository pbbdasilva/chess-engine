#pragma once

#include "Piece.hpp"

class Queen : public Piece {
public:
    Queen(Player who, int i, int j);
    PieceType whichType();

    bool validMove(int i, int j, MoveType type, Player turn);
    std::vector<std::pair<int,int>> genMoves(std::vector<std::vector<Piece*>>& t);
};