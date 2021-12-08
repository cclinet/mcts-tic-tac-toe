#include "GameState.h"
#include "Node.h"
#include <algorithm>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;



PYBIND11_MODULE(mcts, m) {
    m.doc() = "MCTS C++ bind using pybind11";
    py::class_<GameState> game_state(m, "GameState");
    game_state.def(py::init<>())
            .def_readwrite("board", &GameState::board)
            .def(py::init<const array<uint8_t, 9> &>())
            .def("is_terminal", &GameState::is_terminal)
            .def("judge", &GameState::judge)
            .def("legal_position", &GameState::legal_position);

    py::enum_<GameState::Piece>(game_state, "Piece")
            .value("Null", GameState::Piece::Null)
            .value("Cross", GameState::Piece::Cross)
            .value("Circle", GameState::Piece::Circle);
}