# pragma once

#include "Game.hpp"
#include <random>
using namespace std;

int MAX_LAYER = 10;
int INF = 1e9+5;
int NUM_STEPS = 5;

struct Move {
    pair<int,int> currPos, nxtPos;
    Move() {}
    Move(pair<int,int> a, pair<int,int> b) : currPos(a), nxtPos(b) {}

    void setPos(pair<int,int>& a, pair<int,int>& b) {
        currPos = a;
        nxtPos = b;
    }
};

class AI {
    Player color;
    vector<int> tree;
    unordered_map<string, int> storedEvals;
    default_random_engine RNG;

public:
    AI(Player _color) : color(_color) {}
    int getEval(Board& b) {
        if(storedEvals[b.serialize()] != 0) return storedEvals[b.serialize()];

        return 0;
    }

    void processMove(Board& b, Move move) {
        pair<int,int> currPos = move.currPos;
        pair<int,int> nxtPos = move.nxtPos;

        b.t[nxtPos.first][nxtPos.second] = b.t[currPos.first][currPos.second];       
        b.t[currPos.first][currPos.second] = nullptr;
    }

    void unprocessMove(Board& b, Move move) {
        pair<int,int> currPos = move.currPos;
        pair<int,int> nxtPos = move.nxtPos;

        b.t[currPos.first][currPos.second] = b.t[nxtPos.first][nxtPos.second];
        b.t[nxtPos.first][nxtPos.second] = nullptr;
    }

   Move miniMax(Board& b, Player turn, bool maxTurn) {
        vector<Move> nextMoves;
        int steps = NUM_STEPS;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(b.t[i][j] == nullptr or b.t[i][j]->whichColor() != turn) continue;
                for(auto& move : b.t[i][j]->genMoves(b.t)) {
                    if(!b.clearPath({i,j}, move)) continue;

                    auto [nextX, nextY] = move;
                    if(b.t[nextX][nextY] != nullptr and b.t[nextX][nextY]->whichColor() == turn) continue;
                    nextMoves.push_back(Move({i,j}, move));
                }
            }
        }

        shuffle(nextMoves.begin(), nextMoves.end(), RNG);
        int eval;
        Move move;

        if(maxTurn) {
            eval = -INF;
            
            for(int i = 0; i < min(MAX_LAYER, (int) nextMoves.size()); i++) {
                processMove(b, nextMoves[i]);
                int tmpEval = miniMax(b, steps - 1, !turn, false);
                unprocessMove(b, nextMoves[i]);
                if(eval < tmpEval) {
                    eval = tmpEval;
                    move = nextMoves[i];
                }
            }
        } else {
            eval = INF;

            for(int i = 0; i < min(MAX_LAYER, (int) nextMoves.size()); i++) {
               processMove(b, nextMoves[i]);
                int tmpEval = miniMax(b, steps - 1, !turn, true);
                unprocessMove(b, nextMoves[i]);
                if(eval > tmpEval) {
                    eval = tmpEval;
                    move = nextMoves[i];
                } 
            }
        }

        return move;
    }

    int miniMax(Board& b, int steps, Player turn, bool maxTurn) {
        vector<Move> nextMoves;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(b.t[i][j] == nullptr or b.t[i][j]->whichColor() != turn) continue;
                for(auto& move : b.t[i][j]->genMoves(b.t)) {
                    if(!b.clearPath({i,j}, move)) continue;

                    auto [nextX, nextY] = move;
                    if(b.t[nextX][nextY] != nullptr and b.t[nextX][nextY]->whichColor() == turn) continue;
                    nextMoves.push_back(Move({i,j}, move));
                }
            }
        }

        shuffle(nextMoves.begin(), nextMoves.end(), RNG);
        int eval;
        Move move;

        if(maxTurn) {
            eval = -INF;
            
            for(int i = 0; i < min(MAX_LAYER, (int) nextMoves.size()); i++) {
                processMove(b, nextMoves[i]);
                int tmpEval = miniMax(b, steps - 1, !turn, false);
                unprocessMove(b, nextMoves[i]);
                if(eval < tmpEval) {
                    eval = tmpEval;
                    move = nextMoves[i];
                }
            }
        } else {
            eval = INF;

            for(int i = 0; i < min(MAX_LAYER, (int) nextMoves.size()); i++) {
               processMove(b, nextMoves[i]);
                int tmpEval = miniMax(b, steps - 1, !turn, true);
                unprocessMove(b, nextMoves[i]);
                if(eval > tmpEval) {
                    eval = tmpEval;
                    move = nextMoves[i];
                } 
            }
        }

        return eval;
    }   
};