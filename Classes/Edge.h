//
// Created by peter on 19/01/19.
//

#ifndef Z2018_EDGE_H
#define Z2018_EDGE_H

#include "Node.h"

class Edge {
public:
    Node from;
    Node to;
    int cost;

    Edge();
    Edge(Node, Node);
    Edge(Node, Node, int);

    Edge copy() const;
    Edge getReversed() const;

    const std::string toString() const;
    void print() const;
    const int hash() const;

    bool operator==(const Edge& other) const {
        return (
                ((this->from == other.from && this->to == other.to) ||
                 (this->from == other.to && this->to == other.from))

                && this->cost == other.cost
        );
    }

    bool operator>(const Edge& other) const {
        // For priority queue
        return this->cost > other.cost;
    }

    bool operator<(const Edge& other) const {
        // For vector sorting
        return this->cost < other.cost;
    }
};

typedef std::unordered_set<Edge> Edges;
typedef std::deque<Edge> EdgePath;
typedef std::deque<EdgePath> EdgePaths;

namespace std {
    template<>
    struct hash<Edge> {
        size_t
        operator()(const Edge& obj) const {
            return hash<int>()(obj.hash());
        }
    };
}

#endif //Z2018_EDGE_H
