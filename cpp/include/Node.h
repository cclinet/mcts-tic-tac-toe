#ifndef MCTS_NODE_H
#define MCTS_NODE_H
#include "GameState.h"
#include <cmath>
#include <memory>
#include <vector>
using namespace std;

class Node {
private:
    vector<shared_ptr<Node>> children;
    shared_ptr<Node> parent;
    float n_visit{0};
    float n_win{0};

public:
    Node();
    Node(Node *parent, unique_ptr<GameState>& game_state);
    shared_ptr<Node> selection(shared_ptr<Node> node);
    void expansion();
    void simulation();
    void backpropagation();

    unique_ptr<GameState> game_state;

private:
    bool is_expanded();
    float ucb();
};


#endif//MCTS_NODE_H
