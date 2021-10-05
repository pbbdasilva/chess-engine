#pragma once

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
    
    Player turn = Player::WHITE;

public:
    Board();

    void buildBoard(string& pieceString);

    void defineTurn(string& turnString);

    void fenParser(string s);

    void printCurrState();

    int isCheck(Player currTurn);

    bool isMate();
    
    bool clearPath(pair<int,int> currCoord, pair<int,int> nextCoord);

    void movePiece(pair<int,int> currCoord, pair<int,int> nextCoord);

    void castle(pair<int,int> currCoord, pair<int,int> nextCoord);

    bool move(pair<int,int> currCoord, pair<int,int> nextCoord);

    void endRound();

    void testGen(int x, int y);

    bool stillThreat(Player currTurn);
};