#pragma once

#include "Piece.hpp"

class Queen : public Piece {
public:
    Queen(Player who, int i, int j);

    bool validMove(int i, int j, MoveType type, Player turn);

    PieceType whichType();

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);
};