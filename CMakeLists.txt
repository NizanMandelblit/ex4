cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp Server.cpp Server.h Solver.h  ClientHandler.h CasheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h MyParallelServer.cpp MyParallelServer.h StringReverser.cpp StringReverser.h Searchable.h Searcher.h OA.h State.h BstFS.h Point.cpp Point.h Problem.cpp Problem.h BFS.h DFS.h AStar.h Cashe.h)
