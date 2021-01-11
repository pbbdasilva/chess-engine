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
        uint64_t clearRank(int which_one){
            return ~maskRank(which_one);
        }
        uint64_t maskRank(int which_one){
            uint64_t aux, result;
            result = 0;
            for (int i=0; i<64; i++){
                if (i/8 == which_one){
                    aux = 1;
                    aux = aux<<i;
                    result = result | aux;
                }
            }
            return result;
        }
        uint64_t maskFile(int which_one){
            uint64_t aux, result;
            result = 0;
            for (int i=0; i<64; i++){
                if ( i%8 == (which_one-1) ){
                    aux = 1;
                    aux = aux<<i;
                    result = result | aux;
                }
            }
            return result;
        }
        uint64_t clearFile(int which_one){
            return ~maskFile(which_one);
        }
        uint64_t whiteKingValid(uint64_t king_position){
            uint64_t pseudo_valid, north, south, east, west, northeast, northwest, southeast, southwest;
            // check if in an edge rank
            east = king_position<<1;
            west = king_position>>1;
            north = king_position<<8;
            south = king_position>>8;
            northeast = king_position<<9;
            northwest = king_position<<7;
            southeast = king_position>>7;
            southwest = king_position>>9;
            // check if in an edge file
            uint64_t a_file = maskFile(1);
            if (a_file & king_position != 0){
                pseudo_valid = south | north | northeast | southeast | east;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
            uint64_t h_file = maskFile(8);
            if (h_file & king_position != 0){
                pseudo_valid = south | north | west | northwest | southwest;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
            else{
                pseudo_valid = east | west | north | south | northeast | northwest | southeast | southwest;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
        }
        uint64_t blackKingValid(uint64_t king_position){
            uint64_t pseudo_valid, north, south, east, west, northeast, northwest, southeast, southwest;
            // check if in an edge rank
            east = king_position<<1;
            west = king_position>>1;
            north = king_position>>8;
            south = king_position<<8;
            northeast = king_position>>9;
            northwest = king_position>>7;
            southeast = king_position<<7;
            southwest = king_position<<9;
            // check if in an edge file
            uint64_t a_file = maskFile(1);
            if (a_file & king_position != 0){
                pseudo_valid = south | north | northeast | southeast | east;
                pseudo_valid = pseudo_valid & ~black_occupiedSquares();
                return pseudo_valid;
            }
            uint64_t h_file = maskFile(8);
            if (h_file & king_position != 0){
                pseudo_valid = south | north | west | northwest | southwest;
                pseudo_valid = pseudo_valid & ~black_occupiedSquares();
                return pseudo_valid;
            }
            else{
                pseudo_valid = east | west | north | south | northeast | northwest | southeast | southwest;
                pseudo_valid = pseudo_valid & ~black_occupiedSquares();
                return pseudo_valid;
            }
        }
        uint64_t whitePawnValid(uint64_t pawn_postion, bool enPassant){
            // we should implement enpassant later on
            uint64_t pseudo_valid, pseudo_attacks,forward, forward2, west_attack, east_attack;
            forward = pawn_postion<<8;
            forward2 = pawn_postion<<16;
            west_attack = pawn_postion<<7;
            east_attack = pawn_postion<<9;
            // pawn is in 2nd rank
            if (pawn_postion>>16 == 0){
                pseudo_valid = forward | forward2;
                pseudo_attacks = west_attack | east_attack;
                pseudo_valid = pseudo_valid & black_occupiedSquares();
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                pseudo_valid = pseudo_valid | pseudo_attacks;
                return pseudo_valid;
            }
            else{
                pseudo_valid = forward;
                pseudo_attacks = west_attack | east_attack;
                pseudo_valid = pseudo_valid & black_occupiedSquares();
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                pseudo_valid = pseudo_valid | pseudo_attacks;
                return pseudo_valid;
            }
        }
        uint64_t blackPawnValid(uint64_t pawn_postion, bool enPassant){
            // we should implement enpassant later on
            uint64_t pseudo_valid,pseudo_attacks, forward, forward2, west_attack, east_attack;
            forward = pawn_postion>>8;
            forward2 = pawn_postion>>16;
            // remember that the board is upside down to black
            west_attack = pawn_postion>>9;
            east_attack = pawn_postion>>7;
            // pawn is in 2nd rank
            if (pawn_postion<<16 == 0){
                pseudo_valid = forward | forward2;
                pseudo_attacks = west_attack | east_attack;
                pseudo_attacks = pseudo_attacks & white_occupiedSquares();
                pseudo_valid = pseudo_valid & ~black_occupiedSquares();
                pseudo_valid = pseudo_valid | pseudo_attacks;
                return pseudo_valid;
            }
            else{
                pseudo_valid = forward;
                pseudo_attacks = west_attack | east_attack;
                pseudo_attacks = pseudo_attacks & white_occupiedSquares();
                pseudo_valid = pseudo_valid & ~black_occupiedSquares();
                pseudo_valid = pseudo_valid | pseudo_attacks;
                return pseudo_valid;
            }
        }
        uint64_t whiteKnightValid(uint64_t knight_position){
            uint64_t pseudo_valid, upwest, upeast, midupwest, midupeast, midbotwest, midboteast, botwest, boteast;
            upwest = knight_position<<15;
            upeast = knight_position<<17;
            midupwest = knight_position<<6;
            midupeast = knight_position<<10;
            midbotwest = knight_position>>10;
            midboteast = knight_position>>6;
            botwest = knight_position>>17;
            boteast = knight_position>>15;
            if ( knight_position & maskFile(1) != 0){
                pseudo_valid = upeast | midupeast | midboteast | boteast;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
            if ( knight_position & maskFile(2) != 0){
                pseudo_valid = upeast | upwest | midupeast | midboteast | boteast | botwest;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
            if (knight_position & maskFile(8) != 0){
                pseudo_valid = upwest | midupwest | midbotwest | botwest;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
            if (knight_position & maskFile(7) != 0){
                pseudo_valid = upeast | upwest | midupwest | midbotwest | boteast | botwest;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares();
                return pseudo_valid;
            }
            else{
                pseudo_valid = upeast | upwest | midupeast | midupwest | midboteast | midbotwest | boteast | botwest;
                pseudo_valid = pseudo_valid & ~white_occupiedSquares(); 
                return pseudo_valid;
            }
        }
        uint64_t blackKnightValid(uint64_t knight_position){
            uint64_t pseudo_valid, upwest, upeast, midupwest, midupeast, midbotwest, midboteast, botwest, boteast;
            upwest = knight_position>>15;
            upeast = knight_position>>17;
            midupwest = knight_position>>6;
            midupeast = knight_position>>10;
            midbotwest = knight_position<<10;
            midboteast = knight_position>>6;
            botwest = knight_position<<17;
            boteast = knight_position<<15; 
            pseudo_valid = upeast | upwest | midupeast | midupwest | midboteast | midbotwest | boteast | botwest;
            pseudo_valid = pseudo_valid & ~black_occupiedSquares();
            return pseudo_valid;
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
};
int main(){
    Board tabuleiro;
    tabuleiro.pretty_print(tabuleiro.teste());
}