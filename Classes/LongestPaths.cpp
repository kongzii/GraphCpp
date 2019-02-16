//
// Created by peter on 04/02/19.
//

#include "Graph.h"

void Graph::findLongestPathsFrom(const Node &from) const {
    /*
     * Most propably need edit to solve some specific task
     */

    // Must be stack
    std::stack<Path> paths;

    Path path, p;
    path.emplace_back(from);

    paths.push(path);

    Node lastV;
    int maximumCost = 0, maximumLength = 0;
    bool pathProlonged = false;

    while (!paths.empty()) {
        pathProlonged = false;

        path = paths.top();
        paths.pop();

        lastV = path.back();

        for (const auto &node : this->adjList.at(lastV)) {
            /*
            if (node.cost < lastV.cost) {
               continue;
            }
            */

            if (std::find(path.begin(), path.end(), node) != path.end()) {
                continue;
            }

            p = path;
            p.emplace_back(node);

            int newLength = p.size() - 1;
            int newCost = 0;

            for (const auto &n : p) {
                newCost += n.cost;
            }

            if ((newCost > maximumCost) || (newCost == maximumCost && newLength > maximumLength)) {
                maximumCost = newCost;
                maximumLength = newLength;
            }

            paths.push(p);
            pathProlonged = true;
        }
    }
}