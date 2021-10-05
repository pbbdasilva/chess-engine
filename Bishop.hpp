#pragma once

#include "Piece.hpp"

class Bishop : public Piece {
public:
    Bishop(Player who, int i, int j);
    PieceType whichType();

    bool validMove(int i, int j, MoveType type, Player turn);
    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);
};