#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <iostream>


void mcts() {
    auto game_state = GameState();
    shared_ptr<Node> tree = make_shared<Node>();
    for (int i = 0; i != 20; i++) {
        auto node = tree->selection(tree);
        std::cout << *node->game_state<< endl;
        node->expansion();
    }
}

int main() {
    mcts();
    return 0;
}