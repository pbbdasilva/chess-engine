#include "Bishop.hpp"
using namespace std;

Bishop::Bishop(Player who, int i, int j) : Piece(who, i, j) {}

PieceType Bishop::whichType() { return BISHOP; }


bool Bishop::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false)
        throw runtime_error("this piece does not belong to this player\n");

    if(i + j != currX + currY and i - currX != j - currY) return false;

    return true;
}

vector<pair<int,int>> Bishop::genMoves(vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;
    Player pieceColor = whichColor();

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if((i + j) == (currX + currY) or (i - currX) == (j - currY)) {
                if(t[i][j] != nullptr and
                   t[i][j]->whichColor() == pieceColor) continue;

                moves.push_back({i, j});
            }
        }
    }

    return moves;
}