#include<bits/stdc++.h>
using namespace std;

enum Player {
    WHITE, BLACK
};

enum moveType {
    MOVE, ATTACK
};

class Piece {
private:
    Player owner;

public:
    Piece(Player who) { owner = who; }
    virtual bool validMove() { return false; }
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
            if(j != currY) return false;
            if(abs(i - currX) == 1) return true;
            if(abs(i - currX) == 2 && firstMove) {
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
};




class Board {
    vector<vector<Piece*>> t;

public:
    Board() {
        t.assign(8, vector<Piece*>(8, nullptr));
    }
};