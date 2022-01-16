#include "Move.hpp"
using namespace std;

Move::Move() {}
Move::Move(pair<int,int> a, pair<int,int> b) : currPos(a), nxtPos(b) {}
Move::Move(const Move& otherMove) {
    currPos = otherMove.currPos;
    nxtPos = otherMove.nxtPos;
}

Move Move::operator=(const Move& move) {
    currPos = move.currPos;
    nxtPos = move.nxtPos;
    return *this;
}