#pragma once

#include "Piece.hpp"
using namespace std;

class Pawn : public Piece { 
    bool firstMove = true;
    MoveType type;

public:    
    Pawn(Player who, int i, int j);

    bool validMove(int i, int j, MoveType type, Player turn);

    PieceType whichType();

    void setEnPassantStatus(bool updatedStatus);

    void setCoordEnPassant(pair<int,int> coords);

    void setCoordEnPassantCapture(pair<int,int> coords);

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);
};