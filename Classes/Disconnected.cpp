//
// Created by peter on 03/02/19.
//

#include "Graph.h"

Graph::Graphs Graph::getDisconnected() const {
    /*
     * Return vector of graphs, created from separated ones in main graph.
     */


    JoinTable joined(0, this->nOfVertices + 1);

    for (const auto &node : this->nodes) {
        for (const auto &connectedNode : this->adjList.at(node)) {
            joined.join(node, connectedNode);
        }
    }

    std::unordered_map<int, Nodes> nodesInSet;

    for (auto node : this->nodes) {
        nodesInSet[joined.getSet(node)].insert(node);
    }

    Graphs graphs;

    for (const auto &set : nodesInSet) {
        Graph graph(this->direction, set.second.size());

        for (const auto &node : set.second) {
            for (const auto &connectedNode : this->adjList.at(node)) {
                graph.addEdge(node, connectedNode);
            }
        }

        graphs.push_back(graph);
    }

    return graphs;
}