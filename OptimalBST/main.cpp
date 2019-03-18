#include "OptimalBST.h"
#include "News.h"
#include "generators.h"
#include "random.hpp"

#include <limits.h>

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>


using Random = effolkronium::random_static;

/*
void testINT(int n) {
    std::vector<std::pair<int, int>> v(n);
    std::vector<double> freq(n);

    int total = 0;
    for (int i = 0; i < n; i++) {
        v[i] = std::make_pair(Random::get(1, 2000), Random::get(1, 2000));
        total += v[i].first;
    }
    for (int i = 0; i < n; i++)
        freq[i] = (double) (v[i].first) / (double) total;

    OptimalBST<int, int> t(v, freq);

    t.printTree(1);
}*/

void testNEWS(int n) {
    //generateNewsFile(n);
    auto news = getNewsFromFile("news.txt");

    sort(news.begin(), news.end(), [](const News &a, const News &b) { return a.getTitle() < b.getTitle(); });
    std::vector<double> freq(news.size());
    std::vector<std::pair<std::string, News>> v(news.size());
    int total = 0;
    for (auto &n:news) {
        total += n.getViews();
    }
    for (int i = 0; i < news.size(); i++) {
        freq[i] = (double) news[i].getViews() / (double) total;

        v[i] = std::make_pair(news[i].getTitle(), news[i]);
    }
    OptimalBST<std::string, News> t(v, freq);

    t.printTree(1);

}

int main() {
    /*
    std::vector<std::pair<int, int> > v = {std::make_pair(2, 1),
                                           std::make_pair(4, 2),
                                           std::make_pair(6, 7),
                                           std::make_pair(8, 40)};
    std::vector<double> freq = {0.1, 0.5, 0.1, 0.3};
    OptimalBST<int, int> t(v, freq);
    std::cout << "\n" << t.exists(2) << " " << t.exists(-1) << "\n";
    std::cout << "----------------------------------------------------------\n";
    t.printTree(4);*/

    std::vector<std::pair<int, int> > v = {std::make_pair(1, 1),
                                           std::make_pair(4, 2),
                                           std::make_pair(8, 7),
                                           std::make_pair(3, 40),
                                           std::make_pair(13, 40),
                                           std::make_pair(2, 40),
                                           std::make_pair(20, 40)};
    std::vector<double> freq(v.size());

    int total = 0;
    for (int i = 0; i < v.size(); i++) {
        total += v[i].first;
    }

    for (int i = 0; i < v.size(); i++) {
        freq[i] = (double) v[i].first / (double) total;
    }

    OptimalBST<int, int> t(v, freq);
    t.printTree(1);

    //testINT(10);

    std::cout << "******************************************\n";
    //testNEWS(15);
    return 0;
}
