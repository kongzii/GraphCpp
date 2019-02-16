//
// Created by peter on 11/01/19.
//

#include "Graph.h"

Graph::Graph(GraphDirection direction, int nOfVertices) {
    this->direction = direction;
    this->nOfVertices = nOfVertices;
}

Graph::Graph(GraphDirection direction, std::string certificate, int verticesCountFrom) {
    this->direction = direction;
    this->nOfVertices = std::count(certificate.begin(), certificate.end(), '0');

    this->checkCertificate(certificate);
    this->createFromCertificate(certificate, verticesCountFrom);
}

Graph Graph::copy() const {
    Graph newGraph(this->direction, this->nOfVertices);

    for (const auto &edge : this->edges) {
        if (this->adjList.at(edge.from).count(edge.to)) {
            newGraph.addEdge(edge.copy());
        }
    }

    return newGraph;
}

void Graph::addEdge(Edge e) {
    this->addEdge(e.from, e.to);
}

void Graph::addEdge(Node from, Node to) {
    this->size += 1;
    this->totalCost += to.cost;

    this->adjList[Node(from.n, from.cost)].insert(to);
    this->adjList[Node(to.n, to.cost)];

    this->nodes.insert(from);
    this->nodes.insert(to);

    this->edges.emplace(from, to, to.cost);

    if (this->direction == UnDirected) {
        this->adjList[Node(to.n, to.cost)].insert(Node(from.n, from.cost));
        this->edges.emplace(to, from, to.cost);
    }
}

void Graph::print() const {
    for (const auto& n : this->adjList) {
        std::cout << n.first.n << "(" << n.first.cost << "): ";

        for (const auto& node : n.second) {
            node.print();
            std::cout << " ";
        }

        std::cout << std::endl;
    }
}

void Graph::printMatrix() const {
    for (int i = 0; i < this->nOfVertices + 1; i++) {
        Node ni = Node(i);

        for (int j = 0; j < this->nOfVertices + 1; j++) {
            Node nj = Node(j);

            if (this->adjList.count(ni) && this->adjList.at(ni).count(nj)) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }

            if (j != this->nOfVertices) {
                std::cout << ",";
            }
        }

        std::cout << std::endl;
    }
}

void printNodes(const Nodes &nodes) {
    for (const auto &x : nodes) {
        std::cout << x.n << " ";
    }
    std::cout<<std::endl;
}

int Graph::getDistance(const Node from, const Node to) const {
    if (from == to) {
        return 0;
    }

    int *distances = new int[this->nOfVertices + 1] {};
    bool *visited = new bool[this->nOfVertices + 1] {};

    std::queue<Node> Queue; // FIFO

    Queue.push(from);
    visited[from.n] = true;

    Node v;
    int distance = 0;
    while (!Queue.empty()) {
        v = Queue.front();
        Queue.pop();

        if (this->adjList.count(v)) {
            for(const auto &it : this->adjList.at(v)) {
                if (visited[it.n] || it == from) {
                    continue;
                }

                distances[it.n] = distances[v.n] + 1;

                if (it == to) {
                    delete[] distances;
                    delete[] visited;

                    return distances[to.n];
                }

                Queue.push(it);

                visited[it.n] = true;
            }
        }
    }

    std::string err_message = "Path from " + std::to_string(from.n) +" to " + std::to_string(to.n) + " not found";
    std::__throw_invalid_argument(err_message.c_str());
}

Path Graph::findPath(const Node from, const Node to) {
    auto *visited = new bool[this->nOfVertices + 1] {};

    std::queue<Path> Queue; // FIFO

    Path p;
    p.push_back(from);

    Queue.push(p);
    visited[from.n] = true;

    Node lastV;
    while (!Queue.empty()) {
        p = Queue.front();
        Queue.pop();

        lastV = p.back();

        if (this->adjList.count(lastV)) {
            for (const auto it : this->adjList.at(lastV)) {
                Path p2 = p;

                if (visited[it.n] || it == from) {
                    continue;
                }

                p2.push_back(it);

                if (it == to) {
                    delete[] visited;

                    return p2;
                }

                Queue.push( p2 );

                visited[it.n] = true;
            }
        }
    }

    delete[] visited;

    std::string err = "Path from " + std::to_string(from.n) + " to " + std::to_string(to.n) + " not found";
    std::__throw_invalid_argument(err.c_str());
}