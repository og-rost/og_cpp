#pragma once

#include <vector>

#include "UnionFindInterface.hpp"

/*
Constructor	Find	Union	Connected
O(N)	    O(α(N))	O(α(N))	O(α(N))

O(α(N)) means O(1) on average
*/

class QuickUnionByRank : public QuickFindItf {
public:
    QuickUnionByRank(int sz);
    bool Union(int x, int y) override;
    bool Connected(int x, int y) override;
    int GetSetsCount() override;
    int Find(int x) override;
private:
    std::vector<int> root;
    std::vector<int> rank;
    int setsCount;
};

QuickUnionByRank::QuickUnionByRank(int sz) : root(sz), rank(sz), setsCount(sz) {
    for (int i = 0; i < sz; ++i) {
        root[i] = i;
        rank[i] = 1;
    }
}

int QuickUnionByRank::GetSetsCount() {
    return setsCount;
}

int QuickUnionByRank::Find(int x) {
    while (x != root[x]) {
        x = root[x];
    }
    return x;
}

bool QuickUnionByRank::Union(int x, int y) {
    int rootX = Find(x);
    int rootY = Find(y);
    if (rootX == rootY) {
        return false;
    }
    if (rank[rootX] > rank[rootY]) {
        root[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        root[rootX] = rootY;
    } else {
        root[rootY] = rootX;
        rank[rootX] += 1;
    }
    --setsCount;
    return true;
}

bool QuickUnionByRank::Connected(int x, int y) {
    return Find(x) == Find(y);
}
