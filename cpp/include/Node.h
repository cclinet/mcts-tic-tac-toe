#ifndef MCTS_NODE_H
#define MCTS_NODE_H
#include "GameState.h"
#include <cmath>
#include <memory>
#include <random>
#include <utility>
#include <vector>
using namespace std;

class Node : public enable_shared_from_this<Node> {
public:
    vector<shared_ptr<Node>> children;
    weak_ptr<Node> parent;
    int n_visit{0};
    int value{0};
    pos_type position{255};

public:
    Node();
    Node(weak_ptr<Node> parent, unique_ptr<GameState> game_state, pos_type position = 255);
    Node(weak_ptr<Node> parent, board_type board, pos_type position = 255);

public:
    shared_ptr<Node> selection(shared_ptr<Node> node);
    void expansion();
    int8_t simulation();
    void backpropagation(int beats);

    unique_ptr<GameState> game_state;

public:
    bool is_expanded() const;
    double ucb() const;
    static constexpr int seed = 22;
    //    random_device rd;
    mt19937 rng;
};


#endif//MCTS_NODE_H
