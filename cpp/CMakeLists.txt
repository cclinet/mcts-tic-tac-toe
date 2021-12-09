cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(mcts)

find_package(pybind11 CONFIG)

pybind11_add_module(mcts src/main.cpp src/GameState.cpp src/Node.cpp src/mcts.cpp)
target_include_directories(mcts PUBLIC include)

add_executable(mcts_cpp src/mcts.cpp src/GameState.cpp src/Node.cpp)
target_include_directories(mcts_cpp PUBLIC include)
