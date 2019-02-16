//
// Created by peter on 11/01/19.
//

#ifndef Z2018_NODE_H
#define Z2018_NODE_H

#include <bits/stdc++.h>

class Node {
public:
    int n = -1;
    mutable int cost = -1;
    mutable int component = -1;
    bool dummy = false;

    Node();
    Node(int);
    Node(int, int);
    Node(int, int, bool);

    Node copy() const;

    const std::string toString() const;
    void print() const;
    const int hash() const { return this->n; };

    bool operator==(const Node& other) const {
        return this->n == other.n;
    }

    bool operator>(const Node& other) const {
        return this->cost > other.cost;
    }

    bool operator<(const Node& other) const {
        return this->cost < other.cost;
    }
};

typedef std::unordered_set<Node> Nodes;
typedef std::deque<Node> NodePath;
typedef std::deque<NodePath> NodePaths;

namespace std {
    template<>
    struct hash<Node> {
        size_t
        operator()(const Node& obj) const {
            return hash<int>()(obj.hash());
        }
    };
}


#endif //Z2018_NODE_H
