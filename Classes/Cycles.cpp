//
// Created by peter on 20/01/19.
//

#include "Graph.h"

void Graph::printCycles() const {
    for (const auto &x : this->cycles) {
        for (auto y : x) {
            std::cout<<y.n<<" ";
        } std::cout<<std::endl;
    }
}

void Graph::findCycles() {
    int cycleId = this->nOfVertices + 1;

    for (const auto &n : this->adjList) {
        if (this->isCycleNode(n.first)) {
            continue;
        }

        Path path;
        path.push_back(n.first);

        std::queue<Path> paths;
        paths.push(path);

        Node prevNode;
        Node lastNode;

        while (!paths.empty()) {
            path = paths.front();
            paths.pop();

            lastNode = path.back();

            if (path.size() > 1) {
                prevNode = path[path.size() - 2];
            }

            for (const auto &node : this->adjList[lastNode]) {
                if (prevNode == node) {
                    continue;
                }

                Path path_copy = path;

                auto f = find(path_copy.begin(), path_copy.end(), node);

                if ( f != path_copy.end() ) {
                    Path cycle_path(f, path_copy.end());

                    for (const auto &x : cycle_path) {
                        this->cycleNodes.insert(x);
                        this->nodeToCycle[x] = cycleId;
                    }

                    this->cycles.push_back(cycle_path);
                    cycleId++;
                    goto break2;
                }

                if (this->isCycleNode(node)) {
                    continue;
                }

                path_copy.push_back(node);
                paths.push(path_copy);
            }
        }

        break2:;
    }
}
