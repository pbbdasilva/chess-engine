#include"pieces.h"
using namespace std;

class Board {
    vector<vector<Piece*>> t;
    
    unordered_map<Player, pair<int,int>> kingPos;
    unordered_map<Player, bool> checkStatus;
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

        kingPos[WHITE] = {0, 4};
        kingPos[BLACK] = {7, 4};

        checkStatus[WHITE] = false;
        checkStatus[BLACK] = false;
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

    bool isCheck() {
        auto [kingX, kingY] = kingPos[turn];
        
    }

    bool isMate() {
        auto [whiteKingX, whiteKingY] = kingPos[WHITE];
        auto [blackKingX, blackKingY] = kingPos[BLACK];


    }
    
    bool checkPath(tuple<int,int> currCoord, tuple<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;

        int deltaX = (nextX - currX)/abs(nextX - currX);
        int deltaY =  (nextY - currY)/abs(nextY - currY);

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

        // check basic problems of movement
        if(t[currX][currY] == nullptr) throw runtime_error("coord does not have a piece");
        if(t[nextX][nextY] != nullptr && t[nextX][nextY]->whichColor() == turn) throw runtime_error("target coord is the same type as who is moving\n");
        if(checkStatus[turn] && t[currX][currY]->whichType() != KING) throw runtime_error("player is in check but did not move king\n");

        // decide moveIntention
        if(t[nextX][nextY] != nullptr) moveIntention = ATTACK;
        else moveIntention = MOVE;
        
        // check if movement is valid for this type of piece
        if(t[currX][currY]->validMove(nextX, nextY, moveIntention, turn) == false) throw std::invalid_argument("not valid move");
        
        // check if other piece is on the way
        if(checkPath(currCoord, nextCoord) == false) throw std::invalid_argument("piece is on the way\n");

        // update piece position
        t[currX][currY]->updateCoord(nextX, nextY);
        t[nextX][nextY] = t[currX][currY];
        t[currX][currY] = nullptr;

        if(t[nextX][nextY]->whichType() == KING) kingPos[turn] = {nextX, nextY};

        turn = switchTurn[turn];
    }
};

int main() {
    Board b;
    b.createGame();
    b.printCurrState();
    b.move({1, 5}, {3, 5});
    b.move({6,4}, {4,4});
    b.move({1, 0}, {2, 0});
    b.printCurrState();
    b.move({7, 3}, {3, 7});
    b.printCurrState();
}