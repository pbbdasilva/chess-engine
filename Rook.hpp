#pragma once

#include "Piece.hpp"

class Rook : public Piece {
public:
    Rook(Player who, int i, int j);

    bool validMove(int i, int j, MoveType type, Player turn);

    PieceType whichType();

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);
};