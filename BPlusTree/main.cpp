#include "BPlusTree.h"
#include "News.h"
#include "generators.h"

#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    BPlusTree<int, int> t(4);
    t.insert(1, 1);
    t.insert(2, 1);
    t.insert(3, 1);
    t.insert(4, 1);

    std::cout << t.find(1) << " " << t.find(5);

    return 0;
}