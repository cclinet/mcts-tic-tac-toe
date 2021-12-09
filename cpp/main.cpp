#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <iostream>


void mcts() {
    auto game_state = GameState();
    shared_ptr<Node> tree = make_shared<Node>();
    for (int i = 0; i != 20; i++) {
        auto node = tree->selection(tree);
        node->expansion();
        std::cout << *node->game_state;
        node->expansion();
        auto point = node->simulation();
        std::cout<<(int)point<<endl;
        node->backpropagation(point);
    }
    for_each((tree->children).begin(), (tree->children).end(), [](shared_ptr<Node> node){cout<<node->n_visit<<' ';});
}

int main() {
    mcts();
    return 0;
}