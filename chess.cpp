#include <iostream>
#include <bitset>
// COLOR: BLACK or WHITE
// 1 == TRUE AND 0 == FALSE

using namespace std;
// essa função é usada para montar o tabuleiro
void insert_piece(uint64_t &piece_positions, int index){
    uint64_t aux = 1;
    aux = aux<<index;
    piece_positions = piece_positions | aux;
}
class Move{
    public:
        int starting;
        int finishing;
        int move_type;
        string color;
        Move(int init_square, int finish_square, string who){
            // implement here board notation to integers later on
            // easily do it with enum
            starting = init_square;
            finishing = finish_square;
            color = who;
        }
        bool isLegal(){
            return true;
        }
};
class Board{
    // each square of the board can be represented by a bit and we
    // can have a 64 array of 1's and 0's
    // that is called bit-board representation
    // [1, 0, 0, ...., 0, , 0]
    // [a1, a2, ...., a8, b1, ..., h8]
    private:
        uint64_t white_pawns = 0;
        uint64_t white_rooks = 0;
        uint64_t white_bishops = 0;
        uint64_t white_queens = 0;
        uint64_t white_knights = 0;
        uint64_t white_king = 0;
        uint64_t black_pawns = 0;
        uint64_t black_rooks = 0;
        uint64_t black_bishops = 0;
        uint64_t black_queens = 0;
        uint64_t black_knights = 0;
        uint64_t black_king = 0;
    public:
        Board(){
            // default initialize game
            // white
            insert_piece(white_rooks, 0);
            insert_piece(white_rooks, 7);
            insert_piece(white_knights,1);
            insert_piece(white_knights,6);
            insert_piece(white_bishops, 2);
            insert_piece(white_bishops, 5);
            insert_piece(white_queens, 3);
            insert_piece(white_king, 4);
            for (int i=8; i<16; i++){
                insert_piece(white_pawns, i);
            }
            // black's turn
            insert_piece( black_rooks, 63);
            insert_piece( black_rooks, 56);
            insert_piece( black_knights,62);
            insert_piece( black_knights,57);
            insert_piece( black_bishops, 61);
            insert_piece( black_bishops, 58);
            insert_piece( black_queens, 59);
            insert_piece( black_king, 60);
            for (int i=48; i<56; i++){
                insert_piece( black_pawns, i);
            }
        }
        uint64_t white_occupiedSquares(){
            return white_bishops | white_king | white_knights | white_pawns | white_queens | white_rooks;
        }
        uint64_t black_occupiedSquares(){
            return black_bishops | black_king | black_knights | black_pawns | black_queens | black_rooks;
        }
        uint64_t occupiedSquares(){
            return white_occupiedSquares() | black_occupiedSquares();
        }
        uint64_t emptySquares(){
            return ~occupiedSquares();
        }
        int movePawn(Move move){
            // the sole purpose of this function is to move forward a pawn
            // there will be a separate one to deal with captures
            // starting is where our pawn is right now
            // finishing is where the user wants to land it
            // returns 1 if legal move and updates the Board
            // else it would not update and returns 0
            // important note: only conditions related to pawns only are here, general conditions such
            // check or passing through some certain piece is not intended to be here
            // we will use legalMove func after declaring this one
            if (move.color == "WHITE"){
                if (move.starting/8 == 1){
                    if (move.finishing - move.starting != 8 || move.finishing - move.starting != 16){
                        return 0;
                    } 
                }
                else{
                    if (move.finishing - move.starting != 8){
                        return 0;
                    }
                }
                uint64_t pawn_to_move = 1;
                uint64_t aux_board;
                // getting current location of pawn we want to move
                pawn_to_move = pawn_to_move<<move.starting;
                // taking the pawn off the board to move
                aux_board = white_pawns ^ pawn_to_move;
                // setting new location of pawn
                pawn_to_move = pawn_to_move<<(move.finishing-move.starting);
                // result of the movement
                white_pawns = pawn_to_move | aux_board;
                // note: implement promotion of pawns
                return 1;
            }
            else if (move.color == "BLACK"){
                if (move.starting/8 == 6){
                    if (move.finishing - move.starting != -8 || move.finishing - move.starting != -16){
                        return 0;
                    } 
                }
                else{
                    if (move.finishing - move.starting != -8){
                        return 0;
                    }
                }
                uint64_t pawn_to_move = 1;
                uint64_t aux_board;
                // getting current location of pawn we want to move
                pawn_to_move = pawn_to_move<<move.starting;
                // taking the pawn off the board to move
                aux_board = white_pawns ^ pawn_to_move;
                // setting new location of pawn
                pawn_to_move = pawn_to_move<<(move.starting-move.finishing);
                // result of the movement
                white_pawns = pawn_to_move | aux_board;
                // note: implement promotion of pawns
                return 1;
            }
        }
        void pretty_print(uint64_t piece_positions){
            // lembrar do method .to_string() do bitset
            // p implementar dps
            string helper = bitset<64>(piece_positions).to_string();
            string aux;
            for (int i=0; i<helper.length(); i= i + 8){
                aux = helper.substr(i, 8);
                cout << aux << endl;
            }
        }
        uint64_t teste(){
            return black_occupiedSquares();
        }
};
int main(){
    Board tabuleiro;
    tabuleiro.pretty_print(tabuleiro.teste());
}