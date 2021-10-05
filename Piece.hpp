#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <iostream>
#include <stack>

#include "Enums.hpp"

class Piece {
private:
    Player color;
protected:
    int currX, currY;
    bool enPassant = false;
    bool unMoved = true;

    std::pair<int,int> enPassantMove;
    std::pair<int,int> enPassantCapture;
public:
    Piece(Player who, int i, int j);
    virtual PieceType whichType();
    Player whichColor();
    bool verifyOwnership(Player playerColor);

    void updateCoord(int i, int j);
    bool getMoveStatus();
    void setMoveStatus(bool status);

    virtual void setEnPassantStatus(bool updatedStatus);
    virtual void setCoordEnPassant(std::pair<int,int> coords);
    virtual void setCoordEnPassantCapture(std::pair<int,int> coords);
    bool getEnPassantStatus();
    std::pair<int,int> getCoordEnPassant();
    std::pair<int,int> getEnPassantCapture();

    virtual bool validMove(int i, int j, MoveType type, Player turn);
    virtual std::vector<std::pair<int,int>> genMoves(std::vector<std::vector<Piece*>>& t);
};
