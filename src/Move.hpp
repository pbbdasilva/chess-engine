# pragma once

#include "Piece.hpp"

struct Move {
    std::pair<int,int> currPos, nxtPos;
public:
    Move();
    Move(std::pair<int,int> a, std::pair<int,int> b);
    Move(const Move& otherMove);
    Move operator=(const Move& move);
};