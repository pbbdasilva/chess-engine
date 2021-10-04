#include "Piece.hpp"

Player operator! (Player p) { return (p == WHITE) ? BLACK : WHITE; }

Piece::Piece(Player who, int i, int j) { 
    currX = i;
    currY = j;
    color = who; 
}

bool Piece::validMove(int i, int j, MoveType type, Player turn) {
    cout << "DEU RUIM\n";
    return false;
}

PieceType Piece::whichType() { return NONE; }

Player Piece::whichColor() { return color; }

void Piece::updateCoord(int i, int j) {
    currX = i;
    currY = j;
}

bool Piece::verifyOwnership(Player playerColor) { return (playerColor == whichColor()); }

void Piece::setMoveStatus(bool status) { unMoved = status; }

bool Piece::getEnPassantStatus() { return enPassant; }

bool Piece::getMoveStatus() { return unMoved; }

pair<int,int> Piece::getCoordEnPassant() { return enPassantMove; }

pair<int,int> Piece::getEnPassantCapture() { return enPassantCapture; }

vector<pair<int,int>> Piece::genMoves(vector<vector<Piece*>>& t) { return {{}}; }

void Piece::setEnPassantStatus(bool updatedStatus) {}
    
void Piece::setCoordEnPassant(pair<int,int> coords) {}

void Piece::setCoordEnPassantCapture(pair<int,int> coords) {}