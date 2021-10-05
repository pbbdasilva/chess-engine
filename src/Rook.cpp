#include "Rook.hpp"
using namespace std;

Rook::Rook(Player who, int i, int j) : Piece(who, i, j) {}

PieceType Rook::whichType() { return ROOK; }


bool Rook::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false)
        throw runtime_error("this piece does not belong to this player\n");

    if(i != currX and j != currY) return false;
    else return true;
}

vector<pair<int,int>> Rook::genMoves(const vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;
    Player pieceColor = whichColor();

    for(int k = 0; k < 8; k++) {
        if(t[currX][k] == nullptr or
           t[currX][k]->whichColor() != pieceColor) moves.push_back({currX, k});

        if(t[k][currY] == nullptr or
           t[k][currY]->whichColor() != pieceColor) moves.push_back({k, currY});
    }

    return moves;
}