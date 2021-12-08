#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;


void mcts() {
}

PYBIND11_MODULE(mcts, m) {
    m.doc() = "MCTS C++ bind using pybind11";
    py::class_<GameState> game_state(m, "GameState");
    game_state.def(py::init<>());
    game_state.def_readwrite("board", &GameState::board);

    py::enum_<GameState::Piece>(game_state, "Piece")
            .value("Null", GameState::Piece::Null)
            .value("Cross", GameState::Piece::Cross)
            .value("Circle", GameState::Piece::Circle);
    m.def("mcts", &mcts, "run mcts");
}