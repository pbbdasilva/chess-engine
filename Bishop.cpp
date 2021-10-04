#include "Bishop.hpp"

Bishop::Bishop(Player who, int i, int j) : Piece(who, i, j) {}

bool Bishop::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
    if(i + j != currX + currY and i - currX != j - currY) return false;
    else return true;
}

PieceType Bishop::whichType() { return BISHOP; }

vector<pair<int,int>> Bishop::genMoves(vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i + j == currX + currY and i - currX == j - currY) moves.push_back({i, j});
        }
    }

    return moves;
}