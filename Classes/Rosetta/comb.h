//
// Created by peter on 12/01/19.
//

#ifndef Z2018_COMB_H
#define Z2018_COMB_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace rosetta {

    typedef std::vector<int> Combination;
    typedef std::vector<Combination> Combinations;

    Combinations combinations(int N, int K) {
        Combinations combinations;

        std::string bitmask(K, 1); // K leading 1's
        bitmask.resize(N, 0); // N-K trailing 0's

        // Get integers and permute bitmask
        do {
            Combination c;

            for (int i = 0; i < N; ++i) {
                // [0..N-1] integers

                if (bitmask[i]) {
                    c.emplace_back(i);
                }
            }

            combinations.emplace_back(c);
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

        return combinations;
    }

}

#endif //Z2018_COMB_H
