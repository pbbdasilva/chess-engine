#include"pieces.hpp"
using namespace std;

class Board {
    vector<vector<Piece*>> t;
    vector<pair<int,int>> threatCoords[2];

    unordered_map<player, pair<int,int>> kingPos;
    unordered_map<player, bool> checkStatus;
    unordered_map<pieceType, char> pieceReprWhite;
    unordered_map<pieceType, char> pieceReprBlack;
    unordered_map<char, pair<pieceType, player>> charToPiece;
    stack<pair<int,int>> lastMoves;
    
    player turn = WHITE;

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
        
        for(auto itr : pieceReprWhite) charToPiece[itr.second] = {itr.first, WHITE};
        for(auto itr : pieceReprBlack) charToPiece[itr.second] = {itr.first, BLACK};
    }

    void buildBoard(string& pieceString) {
        Factory factory;
        int idx = 0;

        for(int row = 7; row >= 0; row--) {
            for(int col = 0; col < 8; col++) {
                char ch = pieceString[idx++];
                if(ch == '/') ch = pieceString[idx++];

                if(ch >= 49 and ch <= 57) col += (ch - '1');
                else {
                    auto [type, color] = charToPiece[ch];
                    t[row][col] = factory.buildPiece(type, color, row, col);
                    
                    if(ch == 'k') kingPos[BLACK] = {row, col};
                    else if(ch == 'K') kingPos[WHITE] = {row, col};
                }
            }
        }
    }

    void defineTurn(string& turnString) {
        if(turnString == "w") turn = WHITE;
        else turn = BLACK;
    }

    void fenParser(string FEN) {
        int piecesIdx = FEN.find(' ');

        string pieceString = FEN.substr(0, piecesIdx);
        string turnString = FEN.substr(piecesIdx + 1, 1);

        buildBoard(pieceString);
        defineTurn(turnString);

        isMate();
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

    int isCheck(player currTurn) {
        auto [kingX, kingY] = kingPos[currTurn];
        int nChecks = 0;
        player opColor = !currTurn;
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
        int ownChecks = isCheck(turn);

        player opColor = !turn;
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
        
        if((nextX - currX) == 0 and (nextY - currY) == 0) return false;

        if(t[currX][currY]->whichType() == KNIGHT) {
            if(t[nextX][nextY] == nullptr or t[currX][currY]->whichColor() != t[nextX][nextY]->whichColor()) return true; // modify to smaller statement
            else return false;
        }

        int deltaX = 0, deltaY = 0;
        if((nextX - currX) != 0) deltaX = (nextX - currX)/abs(nextX - currX);
        if((nextY - currY) != 0) deltaY =  (nextY - currY)/abs(nextY - currY);
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
    // b.createGame();
    b.fenParser("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b");
    b.printCurrState();
    // b.move({1, 5}, {2, 5});
    // b.move({6,4}, {4,4});
    // b.move({1, 6}, {3, 6});
    // b.printCurrState();
    // b.move({7, 3}, {3, 7});
    // b.printCurrState();
} // clearpath ta bugado