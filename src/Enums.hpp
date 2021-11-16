#pragma once

enum Player { WHITE, BLACK };
Player operator!(Player p);

enum MoveType { MOVE, ATTACK };
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };