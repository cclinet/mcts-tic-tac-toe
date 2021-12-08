#ifndef MCTS_NODE_H
#define MCTS_NODE_H
#include "GameState.h"
#include <cmath>
#include <vector>
using namespace std;

class Node {
private:
    vector<Node *> children;
    Node *parent;
    float n_visit{0};
    float n_win{0};
    GameState *game_state;

public:
    Node *selection(Node *node);
    void expansion();
    void simulation();
    void backpropagation();

private:
    bool is_expanded();
    float ucb();
};


#endif//MCTS_NODE_H
