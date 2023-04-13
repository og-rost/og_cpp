#include "QuickFind.hpp"
#include "QuickUnion.hpp"
#include "QuickUnionByRank.hpp"
#include "QuickUnionWeighted.hpp"

#include "UnionFindInterface.hpp"

#include <iostream>

void test(QuickFindItf& quickFind) {
    std::cout << "========================== starting test" << std::endl << std::endl;
    // for displaying booleans as literal strings, instead of 0 and 1
    std::cout << std::boolalpha;
    // 1-2-5-6-7 3-8-9 4
    quickFind.Union(1, 2);
    //quickFind.Display();
    quickFind.Union(2, 5);
    //quickFind.Display();
    quickFind.Union(5, 6);
    std::cout << quickFind.GetSetsCount() << std::endl;
    //quickFind.Display();
    quickFind.Union(6, 7);
    //quickFind.Display();
    quickFind.Union(3, 8);
    //quickFind.Display();
    quickFind.Union(8, 9);
    std::cout << quickFind.GetSetsCount() << std::endl;
    //quickFind.Display();
    std::cout << quickFind.Connected(1, 5) << std::endl;  // true
    std::cout << quickFind.Connected(5, 7) << std::endl;  // true
    std::cout << quickFind.Connected(4, 9) << std::endl;  // false
    // 1-2-5-6-7 3-8-9-4
    quickFind.Union(9, 4);
    std::cout << quickFind.Connected(4, 9) << std::endl;  // true
    std::cout << quickFind.GetSetsCount() << std::endl;

    std::cout << std::endl << "========================== test done" << std::endl << std::endl;
}

int main() {
    QuickFind qf(10);
    QuickUnion qu(10);
    QuickUnionByRank qubr(10);
    QuickUnionWeighted quw(10);

    test(qf);
    test(qu);
    test(qubr);
    test(quw);

    return 0;
}
