#include "Rook.hpp"

Rook::Rook(Player who, int i, int j) : Piece(who, i, j) {}

bool Rook::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
    if(i != currX and j != currY) return false;
    else return true;
}

PieceType Rook::whichType() { return ROOK; }

vector<pair<int,int>> Rook::genMoves(vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;

    for(int k = 0; k < 8; k++) {
        moves.push_back({currX, k});
        moves.push_back({k, currY});
    }

    return moves;
}