#include "King.hpp"
using namespace std;

King::King(Player who, int i, int j) : Piece(who, i, j) {}

PieceType King::whichType() { return KING; }


bool King::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false)
        throw runtime_error("this piece does not belong to this player\n");

    if(unMoved and (i == currX) and (j == 2 or j == 6)) return true;

    vector<int> dx = {0,  0,  1, 1,  1, -1, -1, -1};
    vector<int> dy = {1, -1,  0, 1, -1,  0,  1, -1};

    for(int idx = 0; idx < dx.size(); idx++) {
        int nextX = currX + dx[idx];
        int nextY = currY + dy[idx];

        if(nextX < 0 || nextX >= 8) continue;
        if(nextY < 0 || nextY >= 8) continue;
        if(nextX == i and nextY == j) return true;
    }

    return false;
}

vector<pair<int,int>> King::genMoves(const vector<vector<Piece*>>& t) {
    vector<int> dx = {0,  0,  1, 1,  1, -1, -1, -1};
    vector<int> dy = {1, -1,  0, 1, -1,  0,  1, -1};
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

int King::mobilityMultiplier() { return 1; }