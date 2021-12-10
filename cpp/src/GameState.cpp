#include "GameState.h"

bool GameState::is_terminal() {
    return all_of(board.begin(), board.end(), [](piece_type i) { return i != 0; }) || judge() == 1 || judge() == 2;
}

player_type GameState::judge() {
    auto is_win = [](array<piece_type, 3> pieces) {
        return (pieces[0] != unoccupied) && (pieces[0] == pieces[1]) && (pieces[0] == pieces[2]);
    };
    auto select_winner = [](piece_type &piece) -> player_type {
        if (piece == crosses) {
            return 1;
        }
        return 2;
    };

    for (int i = 0; i != 3; ++i) {
        if (is_win({board[3 * i], board[3 * i + 1], board[3 * i +2]})) {
            return select_winner(board[3 * i]);
        }
        if (is_win({board[i], board[i + 3], board[i + 6]})) {
            return select_winner(board[i]);
        }
    }
    if (is_win({board[0], board[4], board[8]})) {
        return select_winner(board[0]);
    }
    if (is_win({board[2], board[4], board[6]})) {
        return select_winner(board[2]);
    }
    return 0;
}

vector<pos_type> GameState::legal_position() {
    vector<pos_type> result{};
    for (auto i = 0; i != 9; ++i) {
        if (board[i] == unoccupied) {
            result.emplace_back(i);
        }
    }
    return result;
}

ostream &operator<<(ostream &out, const GameState &game_state) {
    for (int i = 0; i != 9; ++i) {
        out << (int) game_state.board[i];
        if (i % 3 == 2) {
            out << '\n';
        }
    }
    return out;
}

piece_type GameState::next_piece() {
    auto n_pieces = count_if(board.begin(), board.end(), [](piece_type p) { return p == unoccupied; });
    if (n_pieces % 2 == 0) {
        return 2;
    }
    return 1;
}

GameState::GameState() {
    fill(board.begin(), board.end(), 0);
}

GameState::GameState(const board_type &board) : board(board) {
}

GameState::GameState(const GameState &obj) = default;

GameState::~GameState() = default;