//
// Created by peter on 03/02/19.
//

#ifndef Z2018_PRINT_H
#define Z2018_PRINT_H

#include <iostream>

#include "Node.h"
#include "Edge.h"

namespace print {

    std::ostream &operator<<(std::ostream &os, const Node &m) {
        return os << m.n;
    }

    std::ostream &operator<<(std::ostream &os, const Edge &m) {
        return os << "[ " << m.from << " -> " << m.to << " (" << m.cost << ") ]";
    }

    template<typename T>
    void print(T p) {
        std::cout << p << std::endl;
    }

    template<typename T>
    void iter(T iter) {
        for (const auto &x : iter) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    template<typename T>
    void nestedIter(T nestedIter) {
        for (const auto &x : nestedIter) {
            iter(x);
        }
    }

}


#endif //Z2018_PRINT_H
