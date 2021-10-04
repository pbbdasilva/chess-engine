#include "Board.hpp"

int main() {
    Board b;
    b.fenParser("rn1qkbnr/ppp1pppp/8/5b2/2p1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 4");
    b.printCurrState();
    b.move({0,4}, {0,6});
    b.printCurrState();
    b.move({6,4}, {4,4});
    b.printCurrState();
    b.move({1,3}, {3,3});
    b.printCurrState();
    b.move({3,2}, {2,3});
    b.printCurrState();
    b.move({0,3}, {2,3});
    b.printCurrState();
}