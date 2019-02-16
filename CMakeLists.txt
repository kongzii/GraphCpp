cmake_minimum_required(VERSION 3.13)
project(z2018)

set(CMAKE_CXX_STANDARD 11)

add_executable(z2018 main.cpp Classes/Certificate.cpp Classes/JoinTable.cpp Classes/JoinTable.h  Classes/SpanningTree.cpp Classes/Graph.cpp Classes/Graph.h Classes/Node.cpp Classes/Node.h Classes/Rosetta/comb.h Classes/DisjointSet.cpp Classes/DisjointSet.h Classes/Edge.cpp Classes/Edge.h Classes/Cycles.cpp Classes/StronglyConnectedComponents.cpp Classes/Euler.cpp Classes/Hamiltonian.cpp Classes/print.h Classes/Disconnected.cpp Classes/LongestPaths.cpp)
