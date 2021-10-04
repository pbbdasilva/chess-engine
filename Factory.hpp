#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"

class Factory {
public:
    Piece* buildPiece(PieceType type, Player who, int i, int j);
};