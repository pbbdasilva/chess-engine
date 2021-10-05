#pragma once

#include"Board.hpp"

class Game {
    bool running = true, validMove = true;
    Board b;
    pair<int,int> currCoord, nextCoord;
public:
    Game();
    
    Game(string FEN);

    void run();
    
    void processInput();
    
    void play();
    
    void render();

    void initialRender();
};