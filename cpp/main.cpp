#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <iostream>


void mcts() {
    shared_ptr<Node> tree = make_shared<Node>();
    for (int i = 0; i != 1000; i++) {
        auto node = tree->selection(tree);
        std::cout << node->game_state<< endl;
    }
}

int main() {
    mcts();
    return 0;
}