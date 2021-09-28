#include"pieces.h"
using namespace std;

class Board {
    vector<vector<Piece*>> t;
    vector<pair<int,int>> threatCoords[2];

    unordered_map<Player, pair<int,int>> kingPos;
    unordered_map<Player, bool> checkStatus;
    unordered_map<pieceType, char> pieceReprWhite;
    unordered_map<pieceType, char> pieceReprBlack;
    unordered_map<char, pieceType> charToPieceWhite;
    unordered_map<char, pieceType> charToPieceBlack;
    stack<pair<int,int>> lastMoves;
    
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
        
        for(auto itr : pieceReprWhite) charToPieceWhite[itr.second] = itr.first;
        for(auto itr : pieceReprBlack) charToPieceBlack[itr.second] = itr.first;
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

    void buildGame(string FEN) {

    }

    void printCurrState() {
        for(int i = t.size() - 1; i >= 0; i--) {
            for(int j = 0; j < t.size(); j++) {
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

    int isCheck(Player currTurn) {
        auto [kingX, kingY] = kingPos[currTurn];
        int nChecks = 0;
        Player opColor = !currTurn;
        threatCoords[currTurn].clear();

        for(int i = 0; i < t.size(); i++) for(int j = 0; j < t.size(); j++) {
            if(t[i][j] == nullptr or t[i][j]->whichColor() == currTurn) continue;
            if(t[i][j]->validMove(kingX, kingY, ATTACK, opColor)) {
                pair<int,int> currLocation = {i,j};
                bool tmp = clearPath(currLocation, kingPos[currTurn]);
                if(tmp) {
                    threatCoords[currTurn].push_back({i,j});
                    nChecks++;
                }
            }
        }

        checkStatus[currTurn] = (nChecks > 0);
        return nChecks;
    }

    bool isMate() {
        bool status = true;
        isCheck(turn);

        Player opColor = !turn;
        int nChecks = isCheck(opColor);
        // cout << endl << nChecks << endl;
        if(nChecks == 0) return false;

        if(nChecks > 2) {
            auto [kingX, kingY] = kingPos[opColor];
            for(auto& move : t[kingX][kingY]->genMoves(t)) {
                if(!clearPath(kingPos[opColor], move)) continue;
                
                movePiece(kingPos[opColor], move);
                if(isCheck(opColor) == 0) status = false;
                movePiece(move, kingPos[opColor]);

                if(!status) break;
            }
        } else {
            for(int i = 0; i < t.size() and status; i++) {
                for(int j = 0; j < t.size() and status; j++) {
                    if(t[i][j] != nullptr and t[i][j]->whichColor() == opColor) {
                        for(auto& move : t[i][j]->genMoves(t)) {
                            if(!clearPath({i,j}, move)) continue;
                            
                            movePiece({i,j}, move);
                            if(isCheck(opColor) == 0) status = false;
                            movePiece(move, {i,j});

                            if(!status) break;
                        }
                    }
                }
            }
        }

        return status;
    }
    
    bool clearPath(tuple<int,int> currCoord, tuple<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;
        
        if(t[currX][currY]->whichType() == KNIGHT) {
            if(t[nextX][nextY] == nullptr or t[currX][currY]->whichColor() != t[nextX][nextY]->whichColor()) return true; // modify to smaller statement
            else return false;
        }

        int deltaX = (nextX - currX)/abs(nextX - currX);
        int deltaY =  (nextY - currY)/abs(nextY - currY);
        int steps = max(abs(nextX - currX), abs(nextY - currY));

        for(int i = 1; i < steps; i++) {
            currX += deltaX;
            currY += deltaY;

            if(t[currX][currY] != nullptr) return false;
        }

        return true;
    }

    void movePiece(tuple<int,int> currCoord, tuple<int,int> nextCoord) {
        if(currCoord == nextCoord) return;
        
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;

        t[currX][currY]->updateCoord(nextX, nextY);
        t[nextX][nextY] = t[currX][currY];
        t[currX][currY] = nullptr;
    }

    void move(tuple<int,int> currCoord, tuple<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;
        moveType moveIntention;

        // check basic problems of movement
        if(t[currX][currY] == nullptr) throw runtime_error("coord does not have a piece");
        if(t[nextX][nextY] != nullptr and t[nextX][nextY]->whichColor() == turn) throw runtime_error("target coord is the same type as who is moving\n");
        if(checkStatus[turn] and t[currX][currY]->whichType() != KING) throw runtime_error("player is in check but did not move king\n");

        // decide moveIntention
        if(t[nextX][nextY] != nullptr) moveIntention = ATTACK;
        else moveIntention = MOVE;
        
        // check if movement is valid for this type of piece
        if(t[currX][currY]->validMove(nextX, nextY, moveIntention, turn) == false) throw std::invalid_argument("not valid move");
        
        // check if other piece is on the way
        if(clearPath(currCoord, nextCoord) == false) throw std::invalid_argument("piece is on the way\n");

        // update piece position
        movePiece(currCoord, nextCoord);

        if(t[nextX][nextY]->whichType() == KING) kingPos[turn] = {nextX, nextY};
        
        bool status = isMate();
        
        if(checkStatus[turn]) throw invalid_argument("last move resulted in check (suicide)");
        if(status) throw runtime_error("ENDGAME\n");

        turn = !turn;
    }

    void testGen(int x, int y) {
        for(auto [i, j] : t[x][y]->genMoves(t)) {
            cout << "(" << i << "," << j << ")" << endl;
        }
    }
};

int main() {
    Board b;
    b.createGame();
    b.printCurrState();
    b.move({1, 5}, {2, 5});
    b.move({6,4}, {4,4});
    b.move({1, 6}, {3, 6});
    b.printCurrState();
    b.move({7, 3}, {3, 7});
    b.printCurrState();
} // clearpath ta bugado