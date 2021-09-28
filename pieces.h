#include<bits/stdc++.h>
using namespace std;

enum Player { WHITE, BLACK };
Player operator! (Player p) { return (p == WHITE) ? BLACK : WHITE; }

enum moveType { MOVE, ATTACK };
enum pieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

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

    virtual vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) { return {{}}; }

    bool verifyOwnership(Player playerColor) { return (playerColor == whichColor()); }
};

class Pawn : public Piece { 
    bool firstMove = true;
    moveType type;

public:    
    Pawn(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
        if(type == MOVE) {
            if(j != currY) {
                // cout << "wtf0\n";
                return false;
            }
            if(i > currX and turn == BLACK) {
                // cout << "wtf1\n";
                return false;
            }
            if(i < currX and turn == WHITE) {
                // cout << "wtf2\n";
                return false;
            }

            if(abs(i - currX) == 1) {
                // cout << "wtf3\n";
                return true;
            }
            if(abs(i - currX) == 2 and firstMove) {
                // cout << "wtf4\n";
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

    pieceType whichType() { return PAWN; }

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) {
        vector<pair<int,int>> moves;

        if(this->whichColor() == WHITE) {
            if(firstMove and t[currX+1][currY] == nullptr) moves.push_back({currX+2, currY});
            if(currX + 1 < 8) moves.push_back({currX+1, currY});
            if(currY + 1 < 8 and t[currX+1][currY+1] != nullptr and t[currX+1][currY+1]->whichColor() == BLACK) moves.push_back({currX+1, currY+1});
            if(currY - 1 >= 0 and t[currX+1][currY-1] != nullptr and t[currX+1][currY-1]->whichColor() == BLACK) moves.push_back({currX+1, currY-1});
        } else {
            if(firstMove and t[currX-1][currY] == nullptr) moves.push_back({currX-2, currY});
            if(currX - 1 < 8) moves.push_back({currX-1, currY});
            if(currY + 1 < 8 and t[currX-1][currY+1] != nullptr and t[currX-1][currY+1]->whichColor() == BLACK) moves.push_back({currX-1, currY+1});
            if(currY - 1 >= 0 and t[currX-1][currY-1] != nullptr and t[currX-1][currY-1]->whichColor() == BLACK) moves.push_back({currX-1, currY-1});
        }

        return moves;
    }
};

class Knight : public Piece {
public:
    Knight(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
        vector<int> dx = {2,  2, 1, -1,  1, -1, -2, -2};
        vector<int> dy = {1, -1, 2,  2, -2, -2,  1, -1};

        for(int idx = 0; idx < dx.size(); idx++) {
            int nextX = currX + dx[idx];
            int nextY = currY + dy[idx];

            if(nextX < 0 || nextX >= 8) return false;
            if(nextY < 0 || nextY >= 8) return false;
            if(nextX == i and nextY == j) return true;
        }

        return false;
    }

    pieceType whichType() { return KNIGHT; }

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) {
        vector<int> dx = {2,  2, 1, -1,  1, -1, -2, -2};
        vector<int> dy = {1, -1, 2,  2, -2, -2,  1, -1};
        vector<pair<int,int>> moves;

        for(int idx = 0; idx < dx.size(); idx++) {
            int nextX = currX + dx[idx];
            int nextY = currY + dy[idx];

            if(nextX < 0 || nextX >= 8) continue;
            if(nextY < 0 || nextY >= 8) continue;
            
            moves.push_back({nextX, nextY});
        }

        return moves;
    }
};

class King : public Piece {
public:
    King(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
        vector<int> dx = {0,  0,  1, 1,  1, -1, -1, -1};
        vector<int> dy = {1, -1,  0, 1, -1,  0,  1, -1};

        for(int idx = 0; idx < dx.size(); idx++) {
            int nextX = currX + dx[idx];
            int nextY = currY + dy[idx];

            if(nextX < 0 || nextX >= 8) return false;
            if(nextY < 0 || nextY >= 8) return false;
            if(nextX == i and nextY == j) return true;
        }

        return false;
    }

    pieceType whichType() { return KING; }

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) {
        vector<int> dx = {0,  0,  1, 1,  1, -1, -1, -1};
        vector<int> dy = {1, -1,  0, 1, -1,  0,  1, -1};
        vector<pair<int,int>> moves;

        for(int idx = 0; idx < dx.size(); idx++) {
            int nextX = currX + dx[idx];
            int nextY = currY + dy[idx];

            if(nextX < 0 || nextX >= 8) continue;
            if(nextY < 0 || nextY >= 8) continue;
            
            moves.push_back({nextX, nextY});
        }

        return moves;
    }
};

class Rook : public Piece {
public:
    Rook(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
        if(i != currX and j != currY) return false;
        else return true;
    }

    pieceType whichType() { return ROOK; }

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) {
        vector<pair<int,int>> moves;

        for(int k = 0; k < 8; k++) {
            moves.push_back({currX, k});
            moves.push_back({k, currY});
        }

        return moves;
    }
};

class Bishop : public Piece {
public:
    Bishop(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
        if(i + j != currX + currY and i - currX != j - currY) return false;
        else return true;
    }

    pieceType whichType() { return BISHOP; }

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) {
        vector<pair<int,int>> moves;

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(i + j == currX + currY and i - currX == j - currY) moves.push_back({i, j});
            }
        }

        return moves;
    }
};

class Queen : public Piece {
public:
    Queen(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) { // 7, 3
        if(verifyOwnership(turn) == false) throw runtime_error("this piece does not belong to this player\n");
        if((i + j != currX + currY and i - currX != j - currY) and (i != currX and j != currY)) return false;
        else return true;
    }

    pieceType whichType() { return QUEEN; }

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) {
        vector<pair<int,int>> moves;

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(i + j == currX + currY and i - currX == j - currY) moves.push_back({i, j});
            }
        }

        for(int k = 0; k < 8; k++) {
            moves.push_back({currX, k});
            moves.push_back({k, currY});
        }

        return moves;
    }
};