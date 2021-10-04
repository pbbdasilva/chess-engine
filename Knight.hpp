#include "Piece.hpp"

class Knight : public Piece {
public:
    Knight(Player who, int i, int j);

    bool validMove(int i, int j, MoveType type, Player turn);

    PieceType whichType();

    vector<pair<int,int>> genMoves(vector<vector<Piece*>>& t);
};