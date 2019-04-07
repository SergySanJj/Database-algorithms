#include "BPlusTree.h"
#include "News.h"
#include "generators.h"

#include "random.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using Random =effolkronium::random_static;

void TestINT(int n, int t) {
    std::vector<int> v(n);
    BPlusTree<int, int> tree(t);
    for (int i = 0; i < n; i++) {
        v[i] = Random::get(0, n);
        tree.insert(v[i], v[i]);
    }

    for (auto el:v)
        std::cout << el << " ";
    std::cout << std::endl;
    tree.print();
}

void TestNEWS(int n, int t) {
    //generateNewsFile(n);
    auto news = getNewsFromFile("news.txt");
    BPlusTree<int, News> tree(t);
    for (auto &nw:news) {
        tree.insert(nw.getViews(), nw);
    }

    tree.print();
}


int main() {
//    TestINT(6, 2);
    TestNEWS(10, 2);
    return 0;
}