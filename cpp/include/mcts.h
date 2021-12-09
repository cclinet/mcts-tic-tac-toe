#ifndef MCTS_MCTS_H
#define MCTS_MCTS_H

#include "GameState.h"
#include "Node.h"

#include <algorithm>
#include <iostream>
pos_type run_mcts(array<piece_type, 9> board);

#endif//MCTS_MCTS_H
