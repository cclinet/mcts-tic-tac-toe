#ifndef MCTS_GAMESTATE_H
#define MCTS_GAMESTATE_H
#include <array>
using namespace std;

class GameState {
public:
    enum Piece { Null = 0,
                 Cross = 1,
                 Circle = 2 };


    array<Piece, 9> board{};

public:
    GameState();
    explicit GameState(array<Piece, 9> board);
    ~GameState();
    bool is_terminal();
};


#endif//MCTS_GAMESTATE_H
