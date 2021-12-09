#include "GameState.h"

GameState::GameState() {
    fill(board.begin(), board.end(), Null);
}
GameState::GameState(const array<piece_type, 9> &board) {
    for (int i = 0; i != 9; ++i) {
        this->board[i] = Piece(board[i]);
    }
}
GameState::~GameState() = default;

bool GameState::is_terminal() {
    return all_of(board.begin(), board.end(), [](Piece i) { return i != Null; }) || judge() == 1 || judge() == 2;
}


player_type GameState::judge() {
    auto win_func = [](Piece &piece) -> player_type {
        if (piece == Piece::Cross) {
            return 1;
        } else if (piece == Piece::Circle) {
            return 2;
        }
        return 0;
    };

    for (int i = 0; i != 3; ++i) {
        if ((board[3 * i] == board[3 * i + 1]) && (board[3 * i] == board[3 * i + 2])) {
            player_type winner = win_func(board[3 * i]);
            if (winner != 0) {
                return winner;
            }
        }
        if ((board[i] == board[i + 3]) && (board[i] == board[i + 6])) {
            player_type winner = win_func(board[i]);
            if (winner != 0) {
                return winner;
            }
        }
    }
    if ((board[0] == board[4]) && (board[0] == board[7])) {
        player_type winner = win_func(board[0]);
        if (winner != 0) {
            return winner;
        }
    }
    if ((board[2] == board[4]) && (board[2] == board[6])) {
        player_type winner = win_func(board[2]);
        if (winner != 0) {
            return winner;
        }
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
    for (int i=0;i!=9;++i) {
        out<<game_state.board[i];
        if (i%3==2){
            out<<'\n';
        }
    }
    return out;
}
GameState::Piece GameState::next_piece() {
    auto n_pieces = count_if(board.begin(), board.end(), [](Piece p){return p == Piece::Null;});
    if (n_pieces % 2 == 0) {
        return GameState::Circle;
    }
    return GameState::Cross;
}
GameState::GameState(const GameState &obj) = default;
