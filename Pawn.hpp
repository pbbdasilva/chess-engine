#pragma once

#include "Piece.hpp"

class Pawn : public Piece {
    bool firstMove = true;
    MoveType type;
public:
    Pawn(Player who, int i, int j);
    PieceType whichType();

    void setEnPassantStatus(bool updatedStatus);
    void setCoordEnPassant(std::pair<int,int> coords);
    void setCoordEnPassantCapture(std::pair<int,int> coords);

    bool validMove(int i, int j, MoveType type, Player turn);
    std::vector<std::pair<int,int>> genMoves(std::vector<std::vector<Piece*>>& t);
};