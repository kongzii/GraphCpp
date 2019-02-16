//
// Created by peter on 11/01/19.
//

#include "Graph.h"

Graph Graph::createSpanningTree(const Node fromNode) {
    EdgePath path;

    const auto to = Node(fromNode.n, 0);

    path.emplace_back(-1, to, 0);
    path.front().from.dummy = true;

    return this->createSpanningTree(path);
}

Graph Graph::createSpanningTree(const EdgePath path) {
    EdgePaths paths;

    paths.push_back(path);

    return this->createSpanningTree(paths);
}

Graph Graph::createSpanningTree(const EdgePaths paths) {
    std::unordered_map<Node, int> parentCost;

    std::unordered_map<Node, int> key;
    for (const auto n : this->nodes) {
        key[n] = INF;
    }

    std::unordered_map<Node, bool> inMST;
    for (const auto n : this->nodes) {
        inMST[n] = false;
    }

    EdgePriorityQueue pq;
    Graph mstGraph(this->direction, 0);

    JoinTable joined(0, this->nOfVertices + 1);

    for (auto path : paths) {
        if (!path.front().from.dummy) {
            // Do prvního bodu se dostávame z neexistujúciho "dummyNodu" -> nutné kvúli výpočtum
            path.emplace_front(Node(-1), path.front().from, 0);
            path.front().from.dummy = true;
        }

        for (const auto &edge : path) {
            inMST[edge.to] = true;

            if (edge.to.cost != edge.cost) {
                // I prvni node v path musí mit cost = 0
                throw std::invalid_argument("Cost are not equal");
            }

            parentCost[edge.to] = edge.cost;
            key[edge.to] = edge.cost;

            if (!edge.from.dummy) {
                mstGraph.addEdge(edge);
                joined.join(edge);
            }

            pq.emplace(edge);
        }
    }

    Edge u;
    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        if ( !inMST[u.to] ) {
            mstGraph.addEdge(u);
            joined.join(u);
        }

        inMST[u.to] = true;

        for (const auto &p : this->adjList.at(u.to)) {
            // Pro všechny body spojený s u

            if ( !inMST[p] && key[p] > p.cost) {
                key[p] = p.cost;
                parentCost[p] = p.cost;

                pq.emplace(Edge(u.to, p, p.cost));
            }
        }
    }

    while (true) {
        EdgePriorityQueue pq2;

        for (const auto &edge : this->edges) {
            if (!joined.isJoined(edge)) {
                pq2.push(edge);
            }
        }

        if (pq2.empty()) {
            break;
        }

        mstGraph.addEdge(pq2.top());
        joined.join(pq2.top());
    }

    // mstGraph.print();
    return mstGraph;
}
