#pragma once

#include "Factory.hpp"

class Board {
    int round = 0;
    bool castling = false;
    std::vector<std::vector<Piece*>> t;
    std::vector<std::pair<int,int>> threatCoords[2];
    std::queue<std::tuple<int,int,int>> enPassantPieces;

    std::unordered_map<Player, std::pair<int,int>> kingPos;
    std::unordered_map<Player, bool> checkStatus;
    std::unordered_map<PieceType, char> pieceReprWhite;
    std::unordered_map<PieceType, char> pieceReprBlack;
    std::unordered_map<char, std::pair<PieceType, Player>> charToPiece;
    std::stack<std::pair<int,int>> lastMoves;

    Player turn = Player::WHITE;

public:
    std::string initFEN;
    Board();

    void fenParser(const std::string s);
    void buildBoard(const std::string& pieceString);
    void defineTurn(const std::string& turnString);

    void printCurrState();

    int isCheck(Player currTurn);
    bool isMate();
    bool stillThreat(Player currTurn);

    bool move(std::pair<int,int> currCoord, std::pair<int,int> nextCoord);
    bool clearPath(std::pair<int,int> currCoord, std::pair<int,int> nextCoord);
    void movePiece(std::pair<int,int> currCoord, std::pair<int,int> nextCoord);
    void castle(std::pair<int,int> currCoord, std::pair<int,int> nextCoord);
    std::string serialize();

    void endRound();

    void testGen(int x, int y);
};