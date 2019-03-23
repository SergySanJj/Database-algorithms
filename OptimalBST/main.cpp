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

int main() {
    int n = 5;
    auto vNews = getNewsFromFile("news.txt");

    std::sort(vNews.begin(), vNews.end(), [](const News &a, const News &b) { return a.getTitle() < b.getTitle(); });

//    vector<News> news = {News("a", "a", 1, 1, 1),
//                         News("b", "a", 1, 1, 4),
//                         News("c", "a", 1, 1, 8),
//                         News("d", "a", 1, 1, 3),
//                         News("e", "a", 1, 1, 13),
//                         News("f", "a", 1, 1, 2),
//                         News("g", "a", 1, 1, 20)};
//    vector<pair<string, News>> v(news.size());
//    vector<int> freq(news.size());
//    for (int i = 0; i < news.size(); i++) {
//        v[i].first = news[i].getTitle();
//        v[i].second = news[i];
//        freq[i] = news[i].getViews();
//    }

    vector<pair<string, News>> v(vNews.size());
    vector<int> freq(vNews.size());
    for (int i = 0; i < vNews.size(); i++) {
        v[i].first = vNews[i].getTitle();
        v[i].second = vNews[i];
        freq[i] = vNews[i].getViews();
    }

//    OptimalBST<string, News> t(v, freq);
    OptimalBST<string, News> t(v, freq);

    t.printTree(4);
    return 0;
}
