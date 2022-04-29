#pragma once

#include"Board.hpp"
#include"AI.hpp"

enum PlayerType { HUMANPLAYER, AIPLAYER };

class Game {
    bool running = true, validMove = true;
    Board b;
    AI ai;
    std::pair<int,int> currCoord, nextCoord;
    std::vector<PlayerType> turn;
    int turnIdx = 0;
public:
    Game() : ai(Player::BLACK) {
        turn.assign(2, PlayerType::HUMANPLAYER);
        turn[1] = PlayerType::AIPLAYER;
    }
    
    Game(std::string FEN);

    void testFeature();

    void run();
    void processInput();
    void play();

    void render();
    void initialRender();
};