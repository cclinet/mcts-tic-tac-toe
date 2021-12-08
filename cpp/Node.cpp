#include "Node.h"


Node *Node::selection(Node *node) {
    if ((!node->is_expanded()) || (node->game_state->is_terminal())) {
        return node;
    }
    auto max_child_pos = max_element(node->children.begin(), node->children.end(),
                                     [](Node *a, Node *b) { return a->ucb() < b->ucb(); });
    return selection(*max_child_pos);
}
void Node::expansion() {}
void Node::simulation() {}
void Node::backpropagation() {}

bool Node::is_expanded() {
    return !children.empty();
}

float Node::ucb() {
    return static_cast<float>(n_win) / static_cast<float>(n_visit) + sqrt(2 * log(parent->n_visit) / static_cast<float>(n_win));
}
