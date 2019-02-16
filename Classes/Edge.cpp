//
// Created by peter on 19/01/19.
//

#include "Edge.h"

Edge::Edge() {
    this->from = Node();
    this->to = Node();
    this->cost = 0;
}

Edge::Edge(Node from, Node to) {
    this->from = from;
    this->to = to;
}

Edge::Edge(Node from, Node to, int cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
}

Edge Edge::copy() const {
    return Edge(this->from.copy(), this->to.copy(), this->cost);
}

Edge Edge::getReversed() const {
    return Edge(this->to.copy(), this->from.copy(), this->cost);
}

const int Edge::hash() const {
    // Cantor pairing function
    int a = std::min(this->from.hash(), this->to.hash());
    int b = std::max(this->from.hash(), this->to.hash());

    return ((a + b) * (a + b + 1) / 2) + b;
}

const std::string Edge::toString() const {
    std::ostringstream stringStream;
    stringStream << this->from.toString() << " -> " << this->to.toString() << " (" << this->cost << ", "
                 << ")";

    return stringStream.str();
}

void Edge::print() const {
    std::cout << this->toString();
}