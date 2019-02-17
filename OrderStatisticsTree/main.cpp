#include <iostream>
#include <random>
#include <ctime>
#include <cstdio>
#include <fstream>

#include "words.h"
#include "random.hpp"
#include "News.h"
#include "ostree.h"
#include "generators.h"

using Random = effolkronium::random_static;

void testINT() {
    OrderStatisticsTree<int> t([](int &a, int &b) {
        if (a == b)
            return 1;
        return (a < b) ? 0 : 2;
    });
    for (int i = 2; i < 22; i++)
        t.insert(Random::get(1, 2000));
    std::cout << t.orderStatistic(1);
}

void testNEWS() {
    //generateNewsFile(100);
    auto news = getNewsFromFile("news.txt");
    OrderStatisticsTree<News> t([](News &a, News &b) {
        return News::cmpVIEWS(a, b);
    });
    for (auto &n:news) {
        t.insert(n);
    }
    /*
    for (int i = 1; i <= t.getSize(); i++) {
        t.orderStatistic(i).print();
        std::cout << std::endl;
    }
     */
    t.orderStatistic(10).print();
}

int main() {
    //testINT();
    testNEWS();

    return 0;
}