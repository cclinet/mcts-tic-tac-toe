#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "mcts.h"

using namespace std;
namespace py = pybind11;


PYBIND11_MODULE(mcts, m) {
    m.doc() = "MCTS C++ bind using pybind11";
    py::class_<GameState> game_state(m, "GameState");
    game_state.def(py::init<>())
            .def_readwrite("board", &GameState::board)
            .def(py::init<const array<piece_type, 9> &>())
            .def("is_terminal", &GameState::is_terminal)
            .def("judge", &GameState::judge)
            .def("legal_position", &GameState::legal_position);


    m.def("run_mcts", &run_mcts);
}