#include "Pawn.hpp"
using namespace std;

Pawn::Pawn(Player who, int i, int j) : Piece(who, i, j) {}

PieceType Pawn::whichType() { return PAWN; }


void Pawn::setEnPassantStatus(bool updatedStatus) { enPassant = updatedStatus; }

void Pawn::setCoordEnPassant(pair<int,int> coords) { enPassantMove = coords; }

void Pawn::setCoordEnPassantCapture(pair<int,int> coords) { enPassantCapture = coords; }


bool Pawn::validMove(int i, int j, MoveType type, Player turn) {
    if(verifyOwnership(turn) == false)
        throw runtime_error("this piece does not belong to this player\n");

    pair<int,int> candMove = {i, j};
    if(enPassant and  candMove == enPassantMove) return true;

    if(type == MOVE) {
        if(j != currY) return false;
        if(i > currX and turn == BLACK) return false;
        if(i < currX and turn == WHITE) return false;

        if(abs(i - currX) == 1) return true;
        if(abs(i - currX) == 2 and firstMove) {
            firstMove = false;
            return true;
        }

        return false;
    } else if(type == ATTACK) {
        if(abs(i - currX) == 1 and abs(j - currY) == 1) return true;

        return false;
    } else {
        cout << "Invalid parameter\n";
        return false;
    }
}

vector<pair<int,int>> Pawn::genMoves(const vector<vector<Piece*>>& t) {
    vector<pair<int,int>> moves;

    if(this->whichColor() == WHITE) {
        if(firstMove and t[currX+1][currY] == nullptr) moves.push_back({currX+2, currY});
        if(currX + 1 < 8) moves.push_back({currX+1, currY});

        if(currY + 1 < 8 and t[currX+1][currY+1] != nullptr and
           t[currX+1][currY+1]->whichColor() == BLACK) moves.push_back({currX+1, currY+1});

        if(currY - 1 >= 0 and t[currX+1][currY-1] != nullptr and
           t[currX+1][currY-1]->whichColor() == BLACK) moves.push_back({currX+1, currY-1});

    } else {
        if(firstMove and t[currX-1][currY] == nullptr) moves.push_back({currX-2, currY});

        if(currX - 1 < 8) moves.push_back({currX-1, currY});

        if(currY + 1 < 8 and t[currX-1][currY+1] != nullptr and
           t[currX-1][currY+1]->whichColor() == BLACK) moves.push_back({currX-1, currY+1});

        if(currY - 1 >= 0 and t[currX-1][currY-1] != nullptr and
           t[currX-1][currY-1]->whichColor() == BLACK) moves.push_back({currX-1, currY-1});
    }

    if(enPassant) moves.push_back(enPassantMove);

    return moves;
}