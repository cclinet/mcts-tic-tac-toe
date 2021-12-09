#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <iostream>


void mcts() {
    auto game_state = make_unique<GameState>(array<piece_type, 9>{0, 0, 1, 1, 2, 2, 2, 1, 1});
    shared_ptr<Node> tree = make_shared<Node>(make_shared<Node>(), move(game_state));
    for (int i = 0; i != 10000; i++) {
        auto node = tree->selection(tree);
        node->expansion();
        auto point = node->simulation();
        node->backpropagation(point);
    }
    for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node> &node) { cout << *node->game_state << '\n'; });
    for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node> &node) { cout << node->n_visit << ' '; });
    cout << endl;
    for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node> &node) { cout << node->ucb() << ' '; });
}


int main() {
    mcts();
    return 0;
}