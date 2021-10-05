#include "Game.hpp"
using namespace std;

Game::Game() { b.fenParser("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); }

Game::Game(string FEN) { b.fenParser(FEN); }


void Game::run() {
    initialRender();

    while(running) {
        processInput();
        play();
        render();
    }
}

void Game::processInput() {
    int currX, currY, nextX, nextY;
    cout << "Curr Position: ";
    cin >> currX >> currY;
    cout << "New Position: ";
    cin >> nextX >> nextY;
    cout << endl;

    currCoord = {currX - 1, currY - 1};
    nextCoord = {nextX - 1, nextY - 1};
}

void Game::play() { validMove = b.move(currCoord, nextCoord); }


void Game::render() {
    if(validMove) b.printCurrState();
    else cout << "=-=-=-=-=-=-=- INVALID MOVE -=-=-=-=-=-=-=\n";
}

void Game::initialRender() {
    cout << "Welcome to Mediocre-Chess, a pbpj product!\n";
    cout << "How to play: Choose coordinates using integer (1 to 8) separated by space.\n";

    render();
}