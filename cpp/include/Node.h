#ifndef MCTS_NODE_H
#define MCTS_NODE_H
#include "GameState.h"
#include <cmath>
#include <memory>
#include <vector>
#include <random>
using namespace std;

class Node : public enable_shared_from_this<Node> {
private:
    vector<shared_ptr<Node>> children;
    weak_ptr<Node> parent;
    float n_visit{0};
    float n_win{0};

public:
    Node();
    Node(weak_ptr<Node> parent, unique_ptr<GameState> &game_state);
    shared_ptr<Node> selection(shared_ptr<Node> node);
    void expansion();
    int8_t simulation();
    void backpropagation();

    unique_ptr<GameState> game_state;

private:
    bool is_expanded();
    float ucb();
    random_device rd;
    mt19937 rng;
};


#endif//MCTS_NODE_H
