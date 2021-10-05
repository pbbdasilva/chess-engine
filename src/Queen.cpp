#include "Queen.hpp"
using namespace std;

Queen::Queen(Player who, int i, int j) : Piece(who, i, j) {}

PieceType Queen::whichType() { return QUEEN; }


bool Queen::validMove(int i, int j, MoveType type, Player turn) { // 7, 3
    if(verifyOwnership(turn) == false)
        throw runtime_error("this piece does not belong to this player\n");

    if((i + j != currX + currY and i - currX != j - currY) and (i != currX and j != currY))
        return false;

    else return true;
}

vector<pair<int,int>> Queen::genMoves(const vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;
    Player pieceColor = whichColor();

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if((i + j) == (currX + currY) or (i - currX) == (j - currY)) {
                if(t[i][j] != nullptr and t[i][j]->whichColor() == pieceColor) continue;
                moves.push_back({i, j});
            }
        }
    }

    for(int k = 0; k < 8; k++) {
        if(t[currX][k] == nullptr or t[currX][k]->whichColor() != pieceColor) moves.push_back({currX, k});
        if(t[k][currY] == nullptr or t[k][currY]->whichColor() != pieceColor) moves.push_back({k, currY});
    }

    return moves;
}