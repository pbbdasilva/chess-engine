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
    std::unordered_map<std::string, float> storedEvals;
    std::default_random_engine RNG;
    float INF = 1e9;

public:
    AI(Player _color);
    float getEval(Board& b, Player& turn);
    void processMove(Board& b, Move move);
    void unprocessMove(Board& b, Move move);
    std::vector<Move> getPossibleMoves(Board& b, Player turn);
    Move miniMax(Board& b, Player turn, bool maxTurn);
    float processMiniMax(Board& b, int steps, Player turn, bool maxTurn);
    float pieceEvaluation(Board& b);
    float materialScore(Board& b);
    float materialScoreHelper(int x, int y, Board& b);
    float mobilityScore(Board& b);
    float safeKingScore(Board& b);
};
