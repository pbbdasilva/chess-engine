#pragma once

#include "Piece.hpp"

class Bishop : public Piece {
public:
    Bishop(Player who, int i, int j);

    bool validMove(int i, int j, MoveType type, Player turn);

    PieceType whichType();

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);
};