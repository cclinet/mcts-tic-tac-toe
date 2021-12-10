#include "Node.h"


shared_ptr<Node> Node::selection(shared_ptr<Node> node) {
    if ((!node->is_expanded()) || (node->game_state->is_terminal())) {
        return node;
    }
    auto max_ucb_child = max_element(node->children.begin(), node->children.end(),
                                     [](shared_ptr<Node> &a, shared_ptr<Node> &b) { return a->ucb() < b->ucb(); });
    return selection(*max_ucb_child);
}


void Node::expansion() {
    if ((!game_state->is_terminal()) && (!is_expanded()))
        for (const auto &pos: game_state->legal_position()) {
            board_type board = game_state->board;
            board[pos] = game_state->next_piece();
            children.emplace_back(make_shared<Node>(weak_from_this(), board, pos));
        }
}


int8_t Node::simulation() {
    unique_ptr<GameState> simulator_game_state(new GameState(*game_state));
    while (!simulator_game_state->is_terminal()) {
        auto legal_pos = simulator_game_state->legal_position();
        uniform_int_distribution<pos_type> dis(0, (legal_pos.size() - 1));
        size_t pos = legal_pos[dis(rng)];
        simulator_game_state->board[pos] = simulator_game_state->next_piece();
    }
    auto beats = simulator_game_state->judge();
    if (beats == 0) {
        return 0;
    }
    if (beats != static_cast<player_type>(game_state->next_piece())) {
        return 1;
    }
    return -1;
}


void Node::backpropagation(int beats) {
    auto this_node = weak_from_this();
    while (auto ptr = this_node.lock()) {
        ptr->n_visit += 1;
        ptr->value += beats;
        this_node = ptr->parent;
        beats = -beats;
    }
}


bool Node::is_expanded() const {
    return !children.empty();
}


double Node::ucb() const {
    if (n_visit == 0) { return numeric_limits<double>::max(); }

    return (static_cast<double>(value) / static_cast<double>(n_visit)) + (sqrt(2 * log(parent.lock()->n_visit) / static_cast<double>(n_visit)));
}


Node::Node() : parent(weak_ptr<Node>()), game_state(make_unique<GameState>()) {}
Node::Node(weak_ptr<Node> parent, unique_ptr<GameState> game_state, pos_type position) : parent(std::move(parent)), game_state(move(game_state)), position(position) {}
Node::Node(weak_ptr<Node> parent, board_type board, pos_type position) : parent(std::move(parent)), game_state(make_unique<GameState>(board)), position(position) {
}
