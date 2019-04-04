#include "persset.h"
#include "generators.h"
#include "random.hpp"
#include "News.h"

#include <queue>
#include <iostream>
#include <utility>
#include <vector>

using Random = effolkronium::random_static;

void testINT() {
    RBTree<int> t([](int &a, int &b) {
        if (a == b)
            return 1;
        return (a < b) ? 0 : 2;
    });
    for (int i = 2; i < 22; i++)
        t.insert(Random::get(1, 2000));
}

void testNEWS() {
    generateNewsFile(10);
    auto news = getNewsFromFile("news.txt");
    RBTree<News> t([](News &a, News &b) {
        return News::cmpTITLE(a, b);
    });
    for (auto &n:news) {
        t.insert(n);
    }

    t.print();
}

void handTest() {
    RBTree<int> t([](int &a, int &b) {
        if (a == b)
            return 1;
        return (a < b) ? 0 : 2;
    });
    auto v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto &el:v) {
        t.insert(el);
        t.print();
    }

    if (0) {

        while (false) {
            std::cout << "Go to version: ";
            int version;
            std::cin >> version;
            t.resetTo(version);
            t.print();
        }
    }
}

int main() {
    handTest();
    //testINT();
    //testNEWS();

    return 0;
}