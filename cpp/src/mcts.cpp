#include "mcts.h"

pos_type run_mcts(array<piece_type, 9> board) {
    shared_ptr<Node> tree = make_shared<Node>(make_shared<Node>(), board, 255);
    for (int i = 0; i != 10000; i++) {
        auto node = tree->selection(tree);
        node->expansion();
        auto point = node->simulation();
        node->backpropagation(point);
        cout<<i<<' ';
    }
    shared_ptr<Node> max_visit_child = *max_element(tree->children.begin(), tree->children.end(),
                                                    [](const shared_ptr<Node> &a, const shared_ptr<Node> &b) { return a->n_visit < b->n_visit; });

        for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node> &node) { cout << *node->game_state << '\n'; });
        for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node> &node) { cout << node->n_visit << ' '; });
//        cout << endl;
//        for_each((tree->children).begin(), (tree->children).end(), [](const shared_ptr<Node> &node) { cout << node->ucb() << ' '; });
    return max_visit_child->position;
}


int main() {
    array<piece_type, 9> b = {0,0,0,
                              0,0,0,
                              0,0,0};
    cout<<(int)run_mcts(b)<<endl;
    return 0;
}