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
constexpr piece_type unoccupied = 0;
constexpr piece_type crosses = 1;
constexpr piece_type noughts = 2;

class GameState {
    friend ostream &operator<<(ostream &out, const GameState &game_state);

public:
    board_type board{};

public:
    GameState();
    explicit GameState(const board_type &board);
    GameState(const GameState &obj);
    ~GameState();

public:
    bool is_terminal();
    player_type judge();
    vector<pos_type> legal_position();
    piece_type next_piece();
};


#endif//MCTS_GAMESTATE_H
