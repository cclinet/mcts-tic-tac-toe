#ifndef MCTS_GAMESTATE_H
#define MCTS_GAMESTATE_H
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

class GameState {

    friend ostream &operator<<(ostream &out, const GameState &game_state);

public:
    enum Piece { Null = 0,
                 Cross = 1,
                 Circle = 2 };

    array<Piece, 9> board{};

public:
    GameState();
    explicit GameState(const array<uint8_t, 9> &board);
    GameState(const GameState &obj);
    ~GameState();
    bool is_terminal();
    uint8_t judge();
    vector<size_t> legal_position();
    Piece next_piece();
};


#endif//MCTS_GAMESTATE_H
