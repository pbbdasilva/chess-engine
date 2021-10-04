#include<bits/stdc++.h>
using namespace std;

enum Player { WHITE, BLACK };
enum MoveType { MOVE, ATTACK };
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

class Piece {
private:
    Player color;
protected:
    int currX, currY;
    bool enPassant = false;
    bool unMoved = true;
    pair<int,int> enPassantMove;
    pair<int,int> enPassantCapture;
public:
    Piece(Player who, int i, int j);
    
    virtual bool validMove(int i, int j, MoveType type, Player turn);
    
    virtual PieceType whichType();
    
    Player whichColor();
    
    void updateCoord(int i, int j);

    virtual vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);

    bool verifyOwnership(Player playerColor);

    virtual void setEnPassantStatus(bool updatedStatus);
    
    virtual void setCoordEnPassant(pair<int,int> coords);

    virtual void setCoordEnPassantCapture(pair<int,int> coords);

    void setMoveStatus(bool status);

    bool getEnPassantStatus();

    bool getMoveStatus();

    pair<int,int> getCoordEnPassant();

    pair<int,int> getEnPassantCapture();
};
