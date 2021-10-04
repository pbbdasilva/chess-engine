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

    bool verifyOwnership(Player playerColor);

    virtual vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t) = 0;

    virtual void setEnPassantStatus(bool updatedStatus) = 0;
    
    virtual void setCoordEnPassant(pair<int,int> coords) = 0;

    virtual void setCoordEnPassantCapture(pair<int,int> coords) = 0;

    void setMoveStatus(bool status);

    bool getEnPassantStatus();

    bool getMoveStatus();

    pair<int,int> getCoordEnPassant();

    pair<int,int> getEnPassantCapture();
};
