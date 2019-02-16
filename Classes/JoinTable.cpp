//
// Created by peter on 12/01/19.
//

#include "JoinTable.h"

JoinTable::JoinTable(int start, int end) : ds(start, end) {
    /* Empty */
}

void JoinTable::join(Node n1, Node n2) {
    this->ds.Union(n1.n, n2.n);
}

void JoinTable::join(Edge e) {
    this->join(e.from, e.to);
}

const bool JoinTable::isJoined(Edge e) {
    return this->isJoined(e.from, e.to);
}

const bool JoinTable::isJoined(Node n1, Node n2) {
    return this->ds.sameSet(n1.n, n2.n);
}

void JoinTable::print() const {
    this->ds.print();
}

int JoinTable::getSet(Node &n) {
    return this->ds.Find(n.n);
}