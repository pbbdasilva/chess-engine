#include<bits/stdc++.h>
using namespace std;

enum Player {
    WHITE, BLACK
};

enum moveType {
    MOVE, ATTACK
};

enum pieceType {
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE
};

class Piece {
private:
    Player color;

public:
    Piece(Player who) { color = who; }
    virtual bool validMove() { return false; }
    virtual pieceType whichType() { return NONE; }
    Player whichColor() {return color; }
};

class Pawn : public Piece { 
    bool firstMove = true;
    int currX, currY;

public:    
    Pawn(Player who, int i, int j) : Piece(who) {
        currX = i;
        currY = j;
    }

    bool validMove(int i, int j, moveType type) {
        if(type == MOVE) {
            if(i != currY) return false;
            if(j > currY && BLACK) return false;
            if(j < currY && WHITE) return false;

            if(abs(j - currX) == 1) return true;
            if(abs(j - currX) == 2 && firstMove) {
                firstMove = false;
                return true;
            }

            return false;
        } else if(type == ATTACK) {
            if(abs(i - currX) == 1 && abs(j - currY) == 1) return true;
            
            return false;
        } else {
            cout << "Invalid parameter\n";
            return false;
        }
    }

    pieceType whichType() { return PAWN; }
};

class Knight : public Piece {
    int currX, currY;
public:
    Knight(Player who, int i, int j) : Piece(who) {
        currX = i;
        currY = j;
    }

    bool validMove(int i, int j) {
        vector<int> dx = {2,  2, 1, -1,  1, -1, -2, -2};
        vector<int> dy = {1, -1, 2,  2, -2, -2,  1, -1};

        for(int idx = 0; idx < dx.size(); idx++) {
            int nextX = currX + dx[idx];
            int nextY = currY + dy[idx];

            if(nextX < 0 || nextX >= 8) return false;
            if(nextY < 0 || nextY >= 8) return false;
            if(nextX == i && nextY == j) return true;
        }

        return false;
    }

    pieceType whichType() { return KNIGHT; }
};

class King : public Piece {
    int currX, currY;
public:
    King(Player who, int i, int j) : Piece(who) {
        currX = i;
        currY = j;
    }

    bool validMove(int i, int j) {
        vector<int> dx = {0,  0,  1, 1,  1, -1, -1, -1};
        vector<int> dy = {1, -1,  0, 1, -1,  0,  1, -1};

        for(int idx = 0; idx < dx.size(); idx++) {
            int nextX = currX + dx[idx];
            int nextY = currY + dy[idx];

            if(nextX < 0 || nextX >= 8) return false;
            if(nextY < 0 || nextY >= 8) return false;
            if(nextX == i && nextY == j) return true;
        }

        return false;
    }

    pieceType whichType() { return KNIGHT; }
};

class Board {
    vector<vector<Piece*>> t;
    unordered_map<pieceType, char> pieceReprWhite;
    unordered_map<pieceType, char> pieceReprBlack;

public:
    Board() {
        t.assign(8, vector<Piece*>(8, nullptr));
        pieceReprWhite[PAWN] = 'P';
        pieceReprWhite[KNIGHT] = 'N';
        pieceReprWhite[BISHOP] = 'B';
        pieceReprWhite[ROOK] = 'R';
        pieceReprWhite[QUEEN] = 'Q';
        pieceReprWhite[KING] = 'K';
        pieceReprBlack[PAWN] = 'p';
        pieceReprBlack[KNIGHT] = 'n';
        pieceReprBlack[BISHOP] = 'b';
        pieceReprBlack[ROOK] = 'r';
        pieceReprBlack[QUEEN] = 'q';
        pieceReprBlack[KING] = 'k';
    }

    // initial version w/o string entry
    void createGame() {
        for(int col = 0; col < 8; col++) t[1][col] = new Pawn(WHITE, 1, col);
        for(int col = 0; col < 8; col++) t[6][col] = new Pawn(BLACK, 6, col);
    }

    void printCurrState() {
        for(int i = 7; i >= 0; i--) {
            for(int j = 0; j < 8; j--) {
                if(t[i][j] == nullptr) {
                    cout << "- "; 
                    continue;
                }

                if(t[i][j]->whichColor() == WHITE) cout << pieceReprWhite[t[i][j]->whichType()] << " ";
                if(t[i][j]->whichColor() == BLACK) cout << pieceReprBlack[t[i][j]->whichType()] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Board b;
    b.createGame();
    b.printCurrState();
}