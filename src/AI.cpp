#include "AI.hpp"
using namespace std;

AI::AI(Player _color) : color(_color) {}

float AI::materialScoreHelper(int x, int y, Board& b, Player turn) {
    switch (b.t[x][y]->whichType())
    {
    case PieceType::PAWN:
        return 1;
    case PieceType::KNIGHT:
        return 2.7;
    case PieceType::BISHOP:
        return 2.9;
    case PieceType::ROOK:
        return 4.3;
    case PieceType::QUEEN:
        return 8.9;
    case PieceType::KING:
        return AI::INF;
    default:
        return 0;
    }
}

float AI::positionalScore(int x, int y, Board& b, Player turn) {
    switch (b.t[x][y]->whichType())
    {
    case PieceType::PAWN:
        if(b.t[x][y]->whichColor() == Player::WHITE) return AI::pawn_score[x * 8 + y];
        return AI::pawn_score[mirror_score[x * 8 + y]];
    case PieceType::KNIGHT:
        if(b.t[x][y]->whichColor() == Player::WHITE) return AI::knight_score[x * 8 + y];
        return AI::knight_score[mirror_score[x * 8 + y]];
    case PieceType::BISHOP:
        if(b.t[x][y]->whichColor() == Player::WHITE) return AI::bishop_score[x * 8 + y];
        return AI::bishop_score[mirror_score[x * 8 + y]];
    case PieceType::ROOK:
        if(b.t[x][y]->whichColor() == Player::WHITE) return AI::rook_score[x * 8 + y];
        return AI::rook_score[mirror_score[x * 8 + y]];
    case PieceType::KING:
        if(b.t[x][y]->whichColor() == Player::WHITE) return AI::king_score[x * 8 + y];
        return AI::pawn_score[mirror_score[x * 8 + y]];
    default:
        return 0;
    }
}

float AI::materialScore(Board& b, Player turn) {
    float sum = 0;
    for(int i = 0; i < b.t.size(); i++) {
        for(int j = 0; j < b.t[0].size(); j++) {
            float val = 0;
            auto valMaterial = materialScoreHelper(i, j, b);
            auto valPosition = positionalScore(i, j, b, turn);
            if(b.t[i][j]->whichColor() == Player::BLACK) val = -val;
            sum += val;
        }
    }
    
    return sum;
}

float AI::pieceEvaluation(Board& b, Player turn) {
    
}

float AI::getEval(Board& b, Player& turn) {
    string boardSerial = b.serialize();
    if(storedEvals.find(boardSerial) != storedEvals.end()) {
        int val = storedEvals[boardSerial];
        if(turn == WHITE) return val;
        return -val;
    }
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