#include "GameState.h"

bool GameState::is_terminal() {
    return all_of(board.begin(), board.end(), [](Piece i) { return i != Null; }) || judge() == 1 || judge() == 2;
}

player_type GameState::judge() {
    auto select_winner = [](Piece &piece) -> player_type {
        if (piece == Piece::Cross) {
            return 1;
        }
        return 2;
    };

    for (int i = 0; i != 3; ++i) {
        if ((board[3 * i] != 0) && (board[3 * i] == board[3 * i + 1]) && (board[3 * i] == board[3 * i + 2])) {
            return select_winner(board[3 * i]);
        }
        if ((board[i] != 0) && (board[i] == board[i + 3]) && (board[i] == board[i + 6])) {
            return select_winner(board[i]);
        }
    }
    if ((board[0] != 0) && (board[0] == board[4]) && (board[0] == board[8])) {
        return select_winner(board[0]);
    }
    if ((board[2] != 0) && (board[2] == board[4]) && (board[2] == board[6])) {
        return select_winner(board[2]);
    }
    return 0;
}

vector<pos_type> GameState::legal_position() {
    vector<pos_type> result{};
    for (auto i = 0; i != 9; ++i) {
        if (board[i] == Piece::Null) {
            result.emplace_back(i);
        }
    }
    return result;
}

ostream &operator<<(ostream &out, const GameState &game_state) {
    for (int i = 0; i != 9; ++i) {
        out << game_state.board[i];
        if (i % 3 == 2) {
            out << '\n';
        }
    }
    return out;
}

GameState::Piece GameState::next_piece() {
    auto n_pieces = count_if(board.begin(), board.end(), [](Piece p) { return p == Piece::Null; });
    if (n_pieces % 2 == 0) {
        return GameState::Circle;
    }
    return GameState::Cross;
}

GameState::GameState() {
    fill(board.begin(), board.end(), Null);
}

GameState::GameState(const board_type &board) {
    for (int i = 0; i != 9; ++i) {
        this->board[i] = Piece(board[i]);
    }
}

GameState::GameState(const GameState &obj) = default;

GameState::~GameState() = default;