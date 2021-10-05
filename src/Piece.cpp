#include "Piece.hpp"
using namespace std;

Player operator! (Player p) { return (p == WHITE) ? BLACK : WHITE; }


Piece::Piece(Player who, int i, int j) {
    currX = i;
    currY = j;
    color = who;
}

PieceType Piece::whichType() { return NONE; }

Player Piece::whichColor() { return color; }

bool Piece::verifyOwnership(Player playerColor) { return (playerColor == whichColor()); }


void Piece::updateCoord(int i, int j) {
    currX = i;
    currY = j;
}

void Piece::setMoveStatus(bool status) { unMoved = status; }

bool Piece::getMoveStatus() { return unMoved; }


void Piece::setEnPassantStatus(bool updatedStatus) {}

void Piece::setCoordEnPassant(pair<int,int> coords) {}

void Piece::setCoordEnPassantCapture(pair<int,int> coords) {}

bool Piece::getEnPassantStatus() { return enPassant; }

pair<int,int> Piece::getCoordEnPassant() { return enPassantMove; }

pair<int,int> Piece::getEnPassantCapture() { return enPassantCapture; }


bool Piece::validMove(int i, int j, MoveType type, Player turn) {
    cout << "DEU RUIM\n";
    return false;
}

vector<pair<int,int>> Piece::genMoves(const vector<vector<Piece*>>& t) { return {{}}; }