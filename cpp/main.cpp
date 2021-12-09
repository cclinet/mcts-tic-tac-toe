#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <iostream>


void mcts() {
    shared_ptr root = make_shared<Node>();
    auto game_state = make_unique<GameState>(array<piece_type, 9>{0,0,0,0,0,0,0,0,0});
    shared_ptr<Node> tree = make_shared<Node>(root, move(game_state));
    for (int i = 0; i != 100000; i++) {
        auto node = tree->selection(tree);
        node->expansion();
        auto point = node->simulation();
        node->backpropagation(point);
    }
    for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node>& node){cout<<*node->game_state<<'\n';});
    for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node>& node){cout<<node->n_visit<<' ';});
    cout<<endl;
    for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node>& node){cout<<node->ucb()<<' ';});
}

int main() {
    mcts();
    return 0;
}