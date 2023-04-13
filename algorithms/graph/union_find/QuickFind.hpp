#pragma once

#include <vector>

#include "UnionFindInterface.hpp"

/*
p and q are connected if they have the same id
id is the top of the connected component
8 > 3 > 4 > 9, 8 is the id

defect: Union is too expensive, to connect n elements it requires N^2 time

init       -> N
union      -> N
connected  -> 1
find       -> 1

*/

class QuickFind : public QuickFindItf {
private:
    std::vector<int> ids;
    int setsCount;
public:
    QuickFind(int n);
    bool Connected(int p, int q) override;
    bool Union(int p, int q) override;
    int GetSetsCount() override;
    int Find(int p) override;
};

QuickFind::QuickFind(int n) : ids(n), setsCount(n) {
    for (int i = 0; i < n; ++i) {
        ids[i] = i;
    }
}

int QuickFind::GetSetsCount() {
    return setsCount;
}

int QuickFind::Find(int p) {
    return ids[p];
}

bool QuickFind::Connected(int p, int q) {
    return Find(p) == Find(q);
}

bool QuickFind::Union(int p, int q) {
    int rootP = Find(p);
    int rootQ = Find(q);
    if (rootP == rootQ) {
        return false;
    }
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] == rootP) {
            ids[i] = rootQ;
        }
    }
    --setsCount;
    return true;
}
