#pragma once

#include"Board.hpp"

class Game {
    bool running = true, validMove = true;
    Board b;
    std::pair<int,int> currCoord, nextCoord;
public:
    Game();
    Game(std::string FEN);

    void testFeature();

    void run();
    void processInput();
    void play();

    void render();
    void initialRender();
};