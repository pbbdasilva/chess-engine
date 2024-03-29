#include "Knight.hpp"
using namespace std;

Knight::Knight(Player who, int i, int j) : Piece(who, i, j) {}

PieceType Knight::whichType() { return KNIGHT; }


bool Knight::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false)
        throw runtime_error("this piece does not belong to this player\n");

    vector<int> dx = {2,  2, 1, -1,  1, -1, -2, -2};
    vector<int> dy = {1, -1, 2,  2, -2, -2,  1, -1};

    for(int idx = 0; idx < dx.size(); idx++) {
        int nextX = currX + dx[idx];
        int nextY = currY + dy[idx];

        if(nextX < 0 || nextX >= 8) continue;
        if(nextY < 0 || nextY >= 8) continue;
        if(nextX == i and nextY == j) return true;
    }

    return false;
}

vector<pair<int,int>> Knight::genMoves(const vector<vector<Piece*>>& t) {
    vector<int> dx = {2,  2, 1, -1,  1, -1, -2, -2};
    vector<int> dy = {1, -1, 2,  2, -2, -2,  1, -1};
    vector<pair<int,int>> moves;
    Player pieceColor = whichColor();

    for(int idx = 0; idx < dx.size(); idx++) {
        int nextX = currX + dx[idx];
        int nextY = currY + dy[idx];

        if(nextX < 0 || nextX >= 8) continue;
        if(nextY < 0 || nextY >= 8) continue;

        if(t[nextX][nextY] != nullptr and
           t[nextX][nextY]->whichColor() == pieceColor) continue;

        moves.push_back({nextX, nextY});
    }

    return moves;
}

int Knight::mobilityMultiplier() { return 1; }