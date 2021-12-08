#include "GameState.h"

GameState::GameState() {
    fill(board.begin(), board.end(), Null);
}
GameState::GameState(const array<uint8_t, 9> &board) {
    for (int i = 0; i != 9; ++i) {
        this->board[i] = Piece(board[i]);
    }
}
GameState::~GameState() = default;

bool GameState::is_terminal() {
    return all_of(board.begin(), board.end(), [](Piece i) { return i != Null; }) || judge() == 1 || judge() == 2;
}


uint8_t GameState::judge() {
    auto win_func = [](Piece &piece) -> uint8_t {
        if (piece == Piece::Cross) {
            return 1;
        } else if (piece == Piece::Circle) {
            return 2;
        }
        return 0;
    };

    for (int i = 0; i != 3; ++i) {
        if ((board[3 * i] == board[3 * i + 1]) && (board[3 * i] == board[3 * i + 2])) {
            uint8_t winner = win_func(board[3 * i]);
            if (winner != 0) {
                return winner;
            }
        }
        if ((board[i] == board[i + 3]) && (board[i] == board[i + 6])) {
            uint8_t winner = win_func(board[i]);
            if (winner != 0) {
                return winner;
            }
        }
    }
    if ((board[0] == board[4]) && (board[0] == board[7])) {
        uint8_t winner = win_func(board[0]);
        if (winner != 0) {
            return winner;
        }
    }
    if ((board[2] == board[4]) && (board[2] == board[6])) {
        uint8_t winner = win_func(board[2]);
        if (winner != 0) {
            return winner;
        }
    }
    return 0;
}
vector<size_t> GameState::legal_position() {
    vector<size_t> result{};
    for (auto i = 0; i != 9; ++i) {
        if (board[i] == Piece::Null) {
            result.emplace_back(i);
        }
    }
    return result;
}
GameState::GameState(const GameState &obj) = default;
