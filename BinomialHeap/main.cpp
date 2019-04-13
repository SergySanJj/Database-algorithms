#include "BinomialHeap.h"
#include "News.h"

#include <iostream>

void TEST_BH_INT() {
    BinomialHeap<int> bh;

    std::vector<int> v = {5, 8, 4, 2, 6, 7, -1, 1, 10, 11};
    for (auto a:v)
        bh.push(a);
    std::cout << "All pushed: ";
    bh.print();

    std::cout << "\nMin: " << bh.top() << "\n";
    std::cout << "After pop: ";
    bh.pop();
    bh.print();

}

void TEST_BH_NEWS() {
    BinomialHeap<News> bh;

    std::vector<News> v = {{100, "Gene-silencing",           "Doctors have used a new type of medicine"},
                           {300, "Police open fire",         "Police said the uninjured man was taken to a central London hospital as a precaution"},
                           {60,  "Queerbaiting",             "Ariana Grande stands accused of manipulating "},
                           {500, "The pressure",             "Habiba wants to draw attention to how much of themselves Bangladeshi women have to compromise to make others happy"},
                           {900, "The mystery of Star Wars", "It stood once for the ambition and poise of a young nation emerging from colonial rule, stretching its wings"}};

    for (const auto &a:v)
        bh.push(a);
    std::cout << "Begin: ";
    bh.print();
    std::cout << "\nMin: \n";
    bh.top().print();

    bh.pop();
    std::cout << "\nAfter extract min: ";
    bh.print();
}


int main() {
    //TEST_BH_INT();
    TEST_BH_NEWS();
}
