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

int main() {
    int n = 5;
    vector<News> news = {News("a", "a", 1, 1, 1),
                         News("b", "a", 1, 1, 4),
                         News("c", "a", 1, 1, 8),
                         News("d", "a", 1, 1, 3),
                         News("e", "a", 1, 1, 13),
                         News("f", "a", 1, 1, 2),
                         News("g", "a", 1, 1, 20)};
    vector<pair<string, News>> v(news.size());
    vector<int> freq(news.size());
    for (int i=0;i<news.size();i++){
        v[i].first = news[i].getTitle();
        v[i].second = news[i];
        freq[i] = news[i].getViews();
    }

    OptimalBST<string, News> t(v,freq);

    t.printTree(4);
    return 0;
}
