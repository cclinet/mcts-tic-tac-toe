#ifndef MCTS_GAMESTATE_H
#define MCTS_GAMESTATE_H
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using pos_type = uint8_t;
using player_type = uint8_t;
using piece_type = uint8_t;
using board_type = array<piece_type, 9>;

class GameState {
    friend ostream &operator<<(ostream &out, const GameState &game_state);

public:
    enum Piece { Null = 0,
                 Cross = 1,
                 Circle = 2 };

    array<Piece, 9> board{};

public:
    GameState();
    explicit GameState(const board_type &board);
    GameState(const GameState &obj);
    ~GameState();

public:
    bool is_terminal();
    player_type judge();
    vector<pos_type> legal_position();
    Piece next_piece();
};


#endif//MCTS_GAMESTATE_H
