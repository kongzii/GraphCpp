//
// Created by peter on 30/01/19.
//

#include "Graph.h"

int Graph::countOddNodes() const {
    int odd = 0;

    for (const auto &node : this->adjList) {
        if (node.second.size() % 2 != 0) {
            ++odd;
        }
    }

    return odd;
}

bool Graph::checkEulerTheorem() const {
    /* Theorem:
       A graph G has an Euler trail if and only if it is
       connected and has 0 or 2 vertices of odd degree. */

    auto odd = this->countOddNodes();

    return odd == 0 || odd == 2;
}

Path Graph::getEulerPath() const {
    // TODO: Implement https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/

    if (!this->checkEulerTheorem()) {
        std::__throw_invalid_argument("EulerTheorem failed.");
    }

    // Creates copy for safe deletion of edges
    auto graph = this->copy();

    auto odd = this->countOddNodes();
    Node start;

    if (odd == 0) {
        /* Arbitary node */
        start = Node(0);

    } else if (odd == 2) {
        /* Odd node needed */
        for (const auto &node : graph.adjList) {
            if (node.second.size() % 2 != 0) {
                start = node.first;
                break;
            }
        }

    } else {
        /* Exception would be throwen in check */
    }

    std::stack<Node> stack;
    stack.push(start);

    Node n;
    Path path;
    while (!stack.empty()) {
        n = stack.top();
        stack.pop();

        path.push_back(n);

        for (const auto &node : graph.adjList.at(n)) {
            graph.adjList.at(n).erase(node);

            if (graph.direction == UnDirected) {
                graph.adjList.at(node).erase(n);
            }

            stack.push(node);
            break;
        }
    }

    return path;
}