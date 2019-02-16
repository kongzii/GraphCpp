//
// Created by peter on 12/01/19.
//

#ifndef Z2018_JOINTABLE_H
#define Z2018_JOINTABLE_H

#include "Node.h"
#include "Edge.h"
#include "DisjointSet.h"

class JoinTable {
public:
    explicit JoinTable(int, int);

    int getSet(Node &n);

    void join(Node n1, Node n2);
    void join(Edge e);

    const bool isJoined(Edge e);
    const bool isJoined(Node n1, Node n2);
    void print() const;
private:
    DisjointSet ds;
};


#endif //Z2018_JOINTABLE_H
