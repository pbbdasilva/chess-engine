#include "AI.hpp"
using namespace std;

AI::AI(Player _color) : color(_color) {}
int AI::getEval(Board& b) {
    string boardSerial = b.serialize();
    if(storedEvals.find(boardSerial) != storedEvals.end()) return storedEvals[boardSerial];
    return 0;
}

void AI::processMove(Board& b, Move move) {
    auto [currX, currY] = move.currPos;
    auto [nxtX, nxtY] = move.nxtPos;

    b.t[nxtX][nxtY] = b.t[currX][currY];       
    b.t[currX][currY] = nullptr;
}

void AI::unprocessMove(Board& b, Move move) {
    auto [currX, currY] = move.currPos;
    auto [nxtX, nxtY] = move.nxtPos;

    b.t[currX][currY] = b.t[nxtX][nxtY];       
    b.t[nxtX][nxtY] = nullptr; 
}

vector<Move> AI::getPossibleMoves(Board& b, Player turn) {
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

    return nextMoves;
}

Move AI::miniMax(Board& b, Player turn, bool maxTurn) {
    int steps = NUM_STEPS;
    vector<Move> nextMoves = getPossibleMoves(b, turn);

    shuffle(nextMoves.begin(), nextMoves.end(), RNG);
    int eval;
    Move move;

    if(maxTurn) {
        eval = -INF;
        
        for(int i = 0; i < min(MAX_LAYER, (int) nextMoves.size()); i++) {
            processMove(b, nextMoves[i]);
            int tmpEval = processMiniMax(b, steps - 1, !turn, false);
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
            int tmpEval = processMiniMax(b, steps - 1, !turn, true);
            unprocessMove(b, nextMoves[i]);
            if(eval > tmpEval) {
                eval = tmpEval;
                move = nextMoves[i];
            } 
        }
    }

    return move;
}

int AI::processMiniMax(Board& b, int steps, Player turn, bool maxTurn) {
    vector<Move> nextMoves = getPossibleMoves(b, turn);

    shuffle(nextMoves.begin(), nextMoves.end(), RNG);
    int eval;
    Move move;

    if(maxTurn) {
        eval = -INF;
        
        for(int i = 0; i < min(MAX_LAYER, (int) nextMoves.size()); i++) {
            processMove(b, nextMoves[i]);
            int tmpEval = processMiniMax(b, steps - 1, !turn, false);
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
            int tmpEval = processMiniMax(b, steps - 1, !turn, true);
            unprocessMove(b, nextMoves[i]);
            if(eval > tmpEval) {
                eval = tmpEval;
                move = nextMoves[i];
            } 
        }
    }

    return eval;
}