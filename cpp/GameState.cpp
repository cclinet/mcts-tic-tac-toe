#include "GameState.h"
GameState::GameState() {
    fill(board.begin(), board.end(), Null);
}
GameState::GameState(array<Piece, 9> board) : board(board) {}
GameState::~GameState() = default;

bool GameState::is_terminal() {
    return all_of(board.begin(), board.end(), [](Piece i) { return i != Null; });
}
