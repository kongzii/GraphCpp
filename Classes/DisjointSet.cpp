//
// Created by peter on 13/01/19.
//

#include "DisjointSet.h"

DisjointSet::DisjointSet(Universe &universe) {
    this->makeSet(universe);
}

DisjointSet::DisjointSet(int a, int b) {
    this->makeSet(a, b);
}

int DisjointSet::Find(int k) {
    if (parent[k] != k)
        parent[k] = Find(parent[k]);

    return parent[k];
}

void DisjointSet::makeSet(const Universe & universe) {
    for (int i : universe) {
        parent[i] = i;
        rank[i] = 0;
    }
}

void DisjointSet::makeSet(int a, int b) {
    for (int i = a; i < b; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

void DisjointSet::Union(int a, int b) {
    int x = Find(a);
    int y = Find(b);

    if (x == y)
        return;

    if (rank[x] > rank[y])
        parent[y] = x;
    else if (rank[x] < rank[y])
        parent[x] = y;
    else {
        parent[x] = y;
        rank[y]++;
    }
}

bool DisjointSet::sameSet(int a, int b) {
    return this->Find(a) == this->Find(b);
}

void DisjointSet::print() const {
    // TO_DO
}