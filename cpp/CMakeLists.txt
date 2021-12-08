cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(mcts)
set(Python_ROOT_DIR "/Users/cclin/opt/miniconda3/envs/tic-tac-toe/")
set(PYTHON_LIBRARY "/Users/cclin/opt/miniconda3/envs/tic-tac-toe/lib")
set(pybind11_DIR "/Users/cclin/opt/miniconda3/envs/tic-tac-toe/lib/python3.9/site-packages/pybind11/share/cmake/pybind11")

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

pybind11_add_module(mcts mcts.cpp GameState.cpp Node.cpp)
target_include_directories(mcts PUBLIC include)