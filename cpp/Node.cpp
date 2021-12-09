#include "Node.h"

#include <utility>


shared_ptr<Node> Node::selection(shared_ptr<Node> node) {
    if ((!node->is_expanded()) || (node->game_state->is_terminal())) {
        return node;
    }
    auto max_child_pos = max_element(node->children.begin(), node->children.end(),
                                     [](shared_ptr<Node> &a, shared_ptr<Node> &b) { return a->ucb() < b->ucb(); });
    return selection(*max_child_pos);
}
void Node::expansion() {
    if ((!game_state->is_terminal()) && (!is_expanded()))
        for (const auto &pos: game_state->legal_position()) {
            unique_ptr<GameState> new_game_state{new GameState{*game_state}};
            new_game_state->board[pos] = game_state->next_piece();
            shared_ptr<Node> new_node = make_shared<Node>(weak_from_this(), new_game_state);
            children.emplace_back(new_node);
        }
}
int8_t Node::simulation() {
    shared_ptr<GameState> new_game_state(new GameState(*game_state));
    while (!new_game_state->is_terminal()) {
        auto legal_pos = new_game_state->legal_position();
        uniform_int_distribution<> dist(0, static_cast<u_int8_t>(legal_pos.size() - 1));
//        u_int8_t pos = legal_pos[dist(rng)];
        u_int8_t pos = legal_pos[0];
        new_game_state->board[pos] = new_game_state->next_piece();
    }
    auto winner = new_game_state->judge();
//    std::cout<<"board:\n"<<*new_game_state<<"winner: "<<(int)winner<<"    next player: "<<game_state->next_piece()<<endl;
    if (winner == 0) {
        return 0;
    }
    if (winner != static_cast<u_int8_t>(game_state->next_piece())) {
        return 1;
    }
    return -1;
}
void Node::backpropagation() {}

bool Node::is_expanded() {
    return !children.empty();
}

float Node::ucb() {
    return static_cast<float>(n_win) / static_cast<float>(n_visit) + sqrt(2 * log(parent.lock()->n_visit) / static_cast<float>(n_win));
}


Node::Node() : parent(weak_ptr<Node>()), game_state(make_unique<GameState>()), rng(rd()) {}
Node::Node(weak_ptr<Node> parent, unique_ptr<GameState> &game_state) : parent(std::move(parent)), game_state(move(game_state)), rng(rd()) {}
