#include "Factory.hpp"
using namespace std;

Piece* Factory::buildPiece(PieceType type, Player who, int i, int j) {
    Piece* product = nullptr;

    switch (type) {
    case PAWN:
        product = new Pawn(who, i, j);
        break;

    case KNIGHT:
        product = new Knight(who, i, j);
        break;

    case ROOK:
        product = new Rook(who, i, j);
        break;

    case BISHOP:
        product = new Bishop(who, i, j);
        break;

    case QUEEN:
        product = new Queen(who, i, j);
        break;

    case KING:
        product = new King(who, i, j);
        break;

    default:
        throw invalid_argument("wrong piece type\n");
        break;
    }

    return product;
}