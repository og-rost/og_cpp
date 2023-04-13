#pragma once

#include <vector>

#include "UnionFindInterface.hpp"

/*

defect: Connected is too expensive, could be N (tree can get too tall)

init       -> N
union      -> N (2 calls to find)
connected  -> N (2 calls to find)
find       -> N

*/

class QuickUnion : public QuickFindItf {
private:
    std::vector<int> parent;
    int setsCount;
public:
    QuickUnion(int n);
    bool Connected(int p, int q) override;
    bool Union(int p, int q) override;
    int GetSetsCount() override;
    int Find(int p) override;
};

QuickUnion::QuickUnion(int n) : parent(n), setsCount(n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i; // each element is its own root
    }
}

int QuickUnion::GetSetsCount() {
    return setsCount;
}

int QuickUnion::Find(int p) {
    while (p != parent[p]) {
        p = parent[p];
    }
    return p;
}

/*

Recursive

int QuickUnion::Find(int p) {
    if (p == root[p]) {
        return p;
    }
    return root[p] = Find(root[p]);
}
*/

bool QuickUnion::Connected(int p, int q) {
    return Find(p) == Find(q);
}

bool QuickUnion::Union(int p, int q) {
    int rootP = Find(p);
    int rootQ = Find(q);
    if (parent[rootP] == rootQ) {
        return false;
    }
    parent[rootP] = rootQ;
    --setsCount;
    return true;
}

