#pragma once

class QuickFindItf {
public:
    virtual bool Connected(int p, int q) = 0;
    virtual bool Union(int p, int q) = 0;
    virtual int GetSetsCount() = 0;
    virtual int Find(int p) = 0;
};
