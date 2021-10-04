#include "Queen.hpp"

Queen::Queen(Player who, int i, int j) : Piece(who, i, j) {}

bool Queen::validMove(int i, int j, MoveType type, Player turn) { // 7, 3
    if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
    if((i + j != currX + currY and i - currX != j - currY) and (i != currX and j != currY)) return false;
    else return true;
}

PieceType Queen::whichType() { return QUEEN; }

vector<pair<int,int>> Queen::genMoves(vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i + j == currX + currY and i - currX == j - currY) moves.push_back({i, j});
        }
    }

    for(int k = 0; k < 8; k++) {
        moves.push_back({currX, k});
        moves.push_back({k, currY});
    }

    return moves;
}