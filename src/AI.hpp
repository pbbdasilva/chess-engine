# pragma once

#include "Game.hpp"
#include "Move.hpp"
#include <algorithm>
#include <random>

const int MAX_LAYER = 10;
const int INF = 1e9+5;
const int NUM_STEPS = 5;

class AI {
    Player color;
    std::vector<int> tree;
    std::unordered_map<std::string, int> storedEvals;
    std::default_random_engine RNG;

public:
    AI(Player _color);
    int getEval(Board& b);
    void processMove(Board& b, Move move);
    void unprocessMove(Board& b, Move move);
    std::vector<Move> getPossibleMoves(Board& b, Player turn);
    Move miniMax(Board& b, Player turn, bool maxTurn);
    int processMiniMax(Board& b, int steps, Player turn, bool maxTurn);
};
