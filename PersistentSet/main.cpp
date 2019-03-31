#include "persset.h"

#include <queue>
#include <iostream>
#include <utility>
#include <vector>


int main() {
    RBTree<int> t([](int &a, int &b) {
        if (a == b)
            return 1;
        return (a < b) ? 0 : 2;
    });
    t.print();
    t.insert(8);
    t.print();
    t.insert(1);
    t.print();
    t.insert(2);
    t.print();
    t.insert(4);
    t.print();

//    t.print();
//
//    t.resetTo(2);
//    t.print();
//
//    t.resetTo(0);
//    t.print();

    return 0;
}