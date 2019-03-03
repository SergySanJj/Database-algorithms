#include "News.h"
#include "generators.h"
#include "random.hpp"
#include "splaytree.h"

#include <iostream>
#include <map>

using namespace std;
using Random = effolkronium::random_static;


void testNEWS() {
    generateNewsFile(1000);
    auto news = getNewsFromFile("news.txt");
    SplayTree<std::string, News> t;
    for (auto &n:news) {
        t.insert(n.getTitle(), n);
    }
    auto testNews = news[0];

    t.find(testNews.getTitle()).print();
    std::cout << "Max Height: " << t.height() << std::endl;
    std::cout << "Avg Height: " << t.avgHeight() << std::endl;
}

void testINT(int cnt = 1000, int mean = 0, int deviation = 1, bool displayVals = true) {
    vector<int> v(1000);
    for (int i = 0; i < 1000; i++) {
        // mean | standard deviation
        v[i] = (int) Random::get<std::normal_distribution<>>((double) mean, (double) deviation);
    }

    SplayTree<int, int> t;
    std::map<int, int> m;
    for (auto &val:v) {
        t.insert(val, val);
        m[val]++;
    }
    if (displayVals) {
        for (auto &val:m) {
            std::cout << "(" << val.first << ", " << val.second << ") ";
        }
    }
    std::cout << "cnt | mean | deviation : " << cnt << " | " << mean << " | " << deviation << std::endl;
    std::cout << "Max Height: " << t.height() << std::endl;
    std::cout << "Avg Height: " << t.avgHeight() << std::endl;
}

void statINT(int cnt) {
    for (int i = 0; i < cnt; i++) {
        testINT(cnt, 0, i, false);
    }
}

int main() {
    //testNEWS();
    //testINT(1000, 0, 1);
    //statINT(1000);
    return 0;
}