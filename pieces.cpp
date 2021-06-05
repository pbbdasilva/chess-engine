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

    bool validMove(int i, int j, moveType type, Player turn) {
        if(i + j != currX + currY) return false;
        else return true;
    }

    pieceType whichType() { return BISHOP; }
};

class Queen : public Piece {
public:
    Queen(Player who, int i, int j) : Piece(who, i, j) {}

    bool validMove(int i, int j, moveType type, Player turn) {
        if(i + j != currX + currY || (i != currX && j != currY)) return false;
        else return true;
    }

    pieceType whichType() { return QUEEN; }
};

class Board {
    vector<vector<Piece*>> t;
    unordered_map<pieceType, char> pieceReprWhite;
    unordered_map<pieceType, char> pieceReprBlack;
    unordered_map<Player, Player> switchTurn;
    Player turn = WHITE;

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

        switchTurn[WHITE] = BLACK;
        switchTurn[BLACK] = WHITE;
    }

    // initial version w/o string entry
    void createGame() {
        t[0][0] = new Rook(WHITE, 0, 0);
        t[0][7] = new Rook(WHITE, 0, 7);
        t[0][2] = new Bishop(WHITE, 0, 2);
        t[0][5] = new Bishop(WHITE, 0, 5);
        t[0][1] = new Knight(WHITE, 0, 1);
        t[0][6] = new Knight(WHITE, 0, 6);
        t[0][3] = new Queen(WHITE, 0, 3);
        t[0][4] = new King(WHITE, 0, 4);
        for(int col = 0; col < 8; col++) t[1][col] = new Pawn(WHITE, 1, col);

        t[7][0] = new Rook(BLACK, 7, 0);
        t[7][7] = new Rook(BLACK, 7, 7);
        t[7][2] = new Bishop(BLACK, 7, 2);
        t[7][5] = new Bishop(BLACK, 7, 5);
        t[7][1] = new Knight(BLACK, 7, 1);
        t[7][6] = new Knight(BLACK, 7, 6);
        t[7][3] = new Queen(BLACK, 7, 3);
        t[7][4] = new King(BLACK, 7, 4);
        for(int col = 0; col < 8; col++) t[6][col] = new Pawn(BLACK, 6, col);
    }

    void printCurrState() {
        for(int i = 7; i >= 0; i--) {
            for(int j = 0; j < 8; j++) {
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

    bool checkWin() {
        return false;
    }

    bool checkPath(tuple<int,int> currCoord, tuple<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;

        int deltaX = nextX - currX > 0 ? 1 : 0;
        int deltaY =  nextY - currY > 0 ? 1 : 0;

        while(currX != nextX && currY != nextY) {
            currX += deltaX;
            currY += deltaY;

            if(t[currX][currY] != nullptr) return false;
        }

        return true;        
    }

    void move(tuple<int,int> currCoord, tuple<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;
        moveType moveIntention;

        if(t[currX][currY] == nullptr) throw runtime_error("coord does not have a piece");
        if(t[nextX][nextY]->whichType() == turn) throw runtime_error("target coord is the same type as who is moving\n");

        if(t[nextX][nextY] != nullptr) moveIntention = ATTACK;
        else moveIntention = MOVE;
        
        if(t[currX][currY]->validMove(nextX, nextY, moveIntention, turn) == false) throw std::invalid_argument("not valid move");
        if(checkPath(currCoord, nextCoord) == false) throw std::invalid_argument("piece is on the way\n");

        t[currX][currY]->updateCoord(nextX, nextY);
        t[nextX][nextY] = t[currX][currY];
        t[currX][currY] = nullptr;

        if(checkWin()) {
            cout << "Player " << turn << " WON!\n";
            exit(0);
        } else turn = switchTurn[turn];
    }
};

int main() {
    Board b;
    b.createGame();

    b.move({1, 1}, {3, 1});
    b.move({6,1}, {5,1});

    b.printCurrState();
    
    b.move({3, 1}, {4, 1});
    
    b.printCurrState();
}