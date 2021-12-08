#include "Node.h"


shared_ptr<Node> Node::selection(shared_ptr<Node> node) {
    if ((!node->is_expanded()) || (node->game_state->is_terminal())) {
        return node;
    }
    auto max_child_pos = max_element(node->children.begin(), node->children.end(),
                                     [](shared_ptr<Node> &a, shared_ptr<Node> &b) { return a->ucb() < b->ucb(); });
    return selection(*max_child_pos);
}
void Node::expansion() {
    if (!game_state->is_terminal())
        for (const auto &pos: game_state->legal_position()) {
            unique_ptr<GameState> new_game_state{new GameState{*game_state}};
            new_game_state->board[pos] = GameState::Piece::Cross;
            children.emplace_back(make_unique<Node>(this, new_game_state));
        }
}
void Node::simulation() {}
void Node::backpropagation() {}

bool Node::is_expanded() {
    return !children.empty();
}

float Node::ucb() {
    return static_cast<float>(n_win) / static_cast<float>(n_visit) + sqrt(2 * log(parent->n_visit) / static_cast<float>(n_win));
}


Node::Node() : parent(nullptr), game_state(make_unique<GameState>()) {}
Node::Node(Node *parent, unique_ptr<GameState> &game_state) : parent(parent), game_state(move(game_state)){};
