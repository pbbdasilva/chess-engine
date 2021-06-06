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
protected:
    int currX, currY;
public:
    Piece(Player who, int i, int j) { 
        currX = i;
        currY = j;
        color = who; 
    }
    virtual bool validMove(int i, int j, moveType type, Player turn) { 
        cout << "DEU RUIM\n";
        return false; 
    }
    virtual pieceType whichType() { return NONE; }
    Player whichColor() { return color; }
    void updateCoord(int i, int j) {
        currX = i;
        currY = j;
    }
};

class Pawn : public Piece { 
    bool firstMove = true;
    moveType type;

public:    
    Pawn(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        cout << "sla\n";
        cout << i << endl;
        cout << j << endl;
        if(type == MOVE) {
            if(j != currY) {
                cout << "wtf0\n";
                return false;
            }
            if(i > currX && turn == BLACK) {
                cout << "wtf1\n";
                return false;
            }
            if(i < currX && turn == WHITE) {
                cout << "wtf2\n";
                return false;
            }

            if(abs(i - currX) == 1) {
                cout << "wtf3\n";
                return true;
            }
            if(abs(i - currX) == 2 && firstMove) {
                cout << "wtf4\n";
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
public:
    Knight(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
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
public:
    King(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
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

    pieceType whichType() { return KING; }
};

class Rook : public Piece {
public:
    Rook(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(i != currX && j != currY) return false;
        else return true;
    }

    pieceType whichType() { return ROOK; }
};

class Bishop : public Piece {
public:
    Bishop(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) { // (0,2) -> (1,1)
        if(i + j != currX + currY && i - currX != j - currY) return false;
        else return true;
    }

    pieceType whichType() { return BISHOP; }
};

class Queen : public Piece {
public:
    Queen(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) { // 7, 3
        if((i + j != currX + currY && i - currX != j - currY) && (i != currX && j != currY)) return false;
        else return true;
    }

    pieceType whichType() { return QUEEN; }
};