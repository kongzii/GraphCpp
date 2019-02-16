//
// Created by peter on 13/01/19.
//

#ifndef Z2018_DISJOINTSET_H
#define Z2018_DISJOINTSET_H

#include <iostream>
#include <vector>
#include <unordered_map>

typedef std::vector<int> Universe;

class DisjointSet {
    std::unordered_map<int, int> parent;

    // stores the depth of trees
    std::unordered_map<int, int> rank;

public:
    explicit DisjointSet(Universe &);
    explicit DisjointSet(int, int);

    void makeSet(const Universe &);

    void makeSet(int, int);

    int Find(int);

    void Union(int, int);

    bool sameSet(int, int);

    void print() const;
};

#endif //Z2018_DISJOINTSET_H
