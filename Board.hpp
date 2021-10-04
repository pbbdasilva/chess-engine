#include "Factory.hpp"
using namespace std;

class Board {
    int round = 0;
    bool castling = false;
    vector<vector<Piece*>> t;
    vector<pair<int,int>> threatCoords[2];
    queue<tuple<int,int,int>> enPassantPieces;

    unordered_map<Player, pair<int,int>> kingPos;
    unordered_map<Player, bool> checkStatus;
    unordered_map<PieceType, char> pieceReprWhite;
    unordered_map<PieceType, char> pieceReprBlack;
    unordered_map<char, pair<PieceType, Player>> charToPiece;
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
        string line = "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
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

        cout << line;
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
        int ownChecks = isCheck(turn);

        Player opColor = !turn;
        int nChecks = isCheck(opColor);

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
    
    bool clearPath(pair<int,int> currCoord, pair<int,int> nextCoord) {
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

    void movePiece(pair<int,int> currCoord, pair<int,int> nextCoord) {
        if(currCoord == nextCoord) return;
        
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;

        // set enpassant
        if(t[currX][currY]->whichType() == PAWN) {
            t[currX][currY]->setEnPassantStatus(false);

            if(abs(currX - nextX) == 2) {
                Player currTurn = t[currX][currY]->whichColor();
                vector<int> dy = {-1, 1};
                vector<int> dx = { 0, 0};

                for(int i = 0; i < dx.size(); i++) {
                    int candX = nextX + dx[i];
                    int candY = nextY + dy[i];

                    if(candX < 0 or candX >= 8) continue;
                    if(candY < 0 or candY >= 8) continue;
                    if(t[candX][candY] == nullptr) continue;

                    if(t[candX][candY]->whichColor() == (!currTurn) and t[candX][candY]->whichType() == PAWN) {
                        t[candX][candY]->setEnPassantStatus(true);
                        enPassantPieces.push({candX, candY, round});
                        
                        if(currTurn == WHITE) t[candX][candY]->setCoordEnPassant({nextX - 1, nextY});
                        else t[candX][candY]->setCoordEnPassant({nextX + 1, nextY});

                        t[candX][candY]->setCoordEnPassantCapture({nextX, nextY});
                    }
                }
            }
        }

        t[currX][currY]->setMoveStatus(false);
        t[currX][currY]->updateCoord(nextX, nextY);
        t[nextX][nextY] = t[currX][currY];
        t[currX][currY] = nullptr;
    }

    void castle(pair<int,int> currCoord, pair<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;

        if(nextY == 2) {
            t[currX][3] = t[currX][0];
            t[currX][0] = nullptr;
            t[currX][3]->setMoveStatus(false);
        } else if(nextY == 6) {
            t[currX][5] = t[currX][7];
            t[currX][7] = nullptr;
            t[currX][5]->setMoveStatus(false);
        }


    }

    void move(pair<int,int> currCoord, pair<int,int> nextCoord) {
        auto [currX, currY] = currCoord;
        auto [nextX, nextY] = nextCoord;
        MoveType moveIntention;

        // check basic problems of movement
        if(t[currX][currY] == nullptr) throw runtime_error("coord does not have a piece");
        if(t[nextX][nextY] != nullptr and t[nextX][nextY]->whichColor() == turn) throw runtime_error("cannot overplace pieces\n");
        if(checkStatus[turn] and t[currX][currY]->whichType() != KING) throw runtime_error("Player is in check but did not move king\n");

        // decide moveIntention
        if(t[nextX][nextY] != nullptr) moveIntention = ATTACK;
        else moveIntention = MOVE;
        
        // check if movement is valid for this type of piece
        if(t[currX][currY]->validMove(nextX, nextY, moveIntention, turn) == false) throw std::invalid_argument("not valid move");
        
        // check if other piece is on the way
        if(clearPath(currCoord, nextCoord) == false) throw std::invalid_argument("piece is on the way\n");

        // if enPassant, capture because movePiece will only move to new position
        if(t[currX][currY]->whichType() == PAWN and t[currX][currY]->getEnPassantStatus()) {
            if(nextCoord == t[currX][currY]->getCoordEnPassant()) {
                auto [captureX, captureY] = t[currX][currY]->getEnPassantCapture();
                t[captureX][captureY] = nullptr;
            }
        }
        
        //castling
        if(t[currX][currY]->whichType() == KING and t[currX][currY]->getMoveStatus()) {
            if(nextY == 2) {
                if(t[currX][0] != nullptr and t[currX][0]->whichType() == ROOK and t[currX][0]->getMoveStatus()) castling = true;
                else throw runtime_error("castle attempt but did not fulfill all requirements\n");
            } else if(nextY == 6) {
                if(t[currX][7] != nullptr and t[currX][7]->whichType() == ROOK and t[currX][7]->getMoveStatus()) castling = true;
                else throw runtime_error("castle attempt but did not fulfill all requirements\n");
            }
        }

        // perform rook movement before king
        if(castling) castle(currCoord, nextCoord);
        
        // update piece position
        movePiece(currCoord, nextCoord);
        if(t[nextX][nextY]->whichType() == KING) kingPos[turn] = {nextX, nextY};
        

        bool status = isMate();
        
        if(checkStatus[turn]) throw invalid_argument("last move resulted in check (suicide)");
        if(status) throw runtime_error("ENDGAME\n");

        endRound();
    }

    void endRound() {
        auto [x, y, pastRound] = enPassantPieces.front();

        while(!enPassantPieces.empty() and pastRound != round) {
            if(t[x][y] != nullptr) t[x][y]->setEnPassantStatus(false);
            enPassantPieces.pop();
            auto [x, y, z] = enPassantPieces.front();
            pastRound = z;
        }

        round++;
        castling = false;
        turn = !turn;
    }

    void testGen(int x, int y) {
        for(auto [i, j] : t[x][y]->genMoves(t)) {
            cout << "(" << i << "," << j << ")" << endl;
        }
    }
};

// int main() {
//     Board b;
//     b.fenParser("rn1qkbnr/ppp1pppp/8/5b2/2p1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 4");
//     b.printCurrState();
//     b.move({0,4}, {0,6});
//     b.printCurrState();
//     b.move({6,4}, {4,4});
//     b.printCurrState();
//     b.move({1,3}, {3,3});
//     b.printCurrState();
//     b.move({3,2}, {2,3});
//     b.printCurrState();
//     b.move({0,3}, {2,3});
//     b.printCurrState();
// }