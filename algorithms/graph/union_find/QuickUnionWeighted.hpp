#pragma once

#include <vector>

#include "UnionFindInterface.hpp"

/*

Keep track of size of each tree
Balance by linking root of smaller tree to root of the larger

init       -> N
union      -> log(N) (+ finding the roots)
connected  -> log(N)

*/

class QuickUnionWeighted : public QuickFindItf {
private:
    std::vector<int> parent;
    std::vector<int> size; // size[i] = the number of objects in the tree rooted at size[i]
    int setsCount;
public:
    QuickUnionWeighted(int n);
    bool Connected(int p, int q) override;
    bool Union(int p, int q) override;
    int GetSetsCount() override;
    int Find(int p) override;
};

QuickUnionWeighted::QuickUnionWeighted(int n) : parent(n), size(n), setsCount(n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i; // each element is its own root
        size[i] = 1;
    }
}

int QuickUnionWeighted::GetSetsCount() {
    return setsCount;
}

int QuickUnionWeighted::Find(int p) {
    while (p != parent[p]) {
        parent[p] = parent[parent[p]]; // make every other node point to its grandpa (halving path lengths)
        p = parent[p];
    }
    return p;
}

bool QuickUnionWeighted::Connected(int p, int q) {
    return Find(p) == Find(q);
}

bool QuickUnionWeighted::Union(int p, int q) {
    int rootP = Find(p);
    int rootQ = Find(q);
    if (rootP == rootQ) {
        return false; // if failed to merge there is a cycle
    }
    if (size[rootP] < size[rootQ]) {
        parent[rootP] = rootQ;
        size[rootQ] += size[rootP];
    } else {
        parent[rootQ] = rootP;
        size[rootP] += size[rootQ];
    }
    parent[rootP] = rootQ;
    --setsCount;
    return true;
}
