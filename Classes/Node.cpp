//
// Created by peter on 11/01/19.
//

#include "Node.h"

Node::Node() {}

Node::Node(int n) {
    this->n = n;
}

Node::Node(int n, int cost) {
    this->n = n;
    this->cost = cost;
}

Node::Node(int n, int cost, bool dummy) {
    this->n = n;
    this->cost = cost;
    this->dummy = dummy;
}

Node Node::copy() const {
    return Node(this->n, this->cost, this->dummy);
}

const std::string Node::toString() const {
    std::ostringstream stringStream;
    stringStream << this->n << "(" << this->cost << ")";

    return stringStream.str();
}

void Node::print() const {
    std::cout << this->toString();
}