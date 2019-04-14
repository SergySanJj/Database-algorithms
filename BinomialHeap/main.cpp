#include "BinomialHeap.h"
#include "FiboHeap.h"
#include "News.h"

#include <iostream>

void TEST_BH_INT() {
    BinomialHeap<int> bh;

    std::vector<int> v = {5, 8, 4, 2, 6, 7, -1, 1, 10, 11};
    for (auto a:v)
        bh.push(a);
    std::cout << "All pushedto bh: ";
    bh.print();

    std::cout << "\nMin: " << bh.top() << "\n";
    std::cout << "After pop: ";
    bh.pop();
    bh.print();

    BinomialHeap<int> bh2;
    std::vector<int> v2 = {100, 200, 50, 300, 250};
    for (auto a:v2)
        bh2.push(a);
    std::cout << "\nAll pushed to bh2: ";
    bh2.print();

    bh.merge(bh2);

    std::cout << "\nAfter merge: ";
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

void TEST_FH_INT() {
    FibonacciHeap<int> fh;

    std::vector<int> v = {5, 8, 4, 2, 6, 7, -1, 1, 10, 11};
    for (auto a:v)
        fh.push(a);
    std::cout << "All pushedto bh: \n";
    fh.print();

    std::cout << "\nMin: " << fh.top() << "\n";
    std::cout << "After pop: \n";
    fh.pop();
    fh.print();

    FibonacciHeap<int> fh2;
    std::vector<int> v2 = {100, 50, -20, 20};
    for (auto a:v2)
        fh2.push(a);
    std::cout << "\nAll pushed to fh2: \n";
    fh2.print();

    fh.merge(fh2);

    std::cout << "\nAfter merge: \n";
    fh.print();

    fh.decreaseKey(fh.find(100),-100);
    std::cout << "\nDecrease 100 key to -100:\n";
    fh.print();

}

void TEST_FH_NEWS() {
    FibonacciHeap<News> bh;

    std::vector<News> v = {{100, "Gene-silencing",           "Doctors have used a new type of medicine"},
                           {300, "Police open fire",         "Police said the uninjured man was taken to a central London hospital as a precaution"},
                           {60,  "Queerbaiting",             "Ariana Grande stands accused of manipulating "},
                           {500, "The pressure",             "Habiba wants to draw attention to how much of themselves Bangladeshi women have to compromise to make others happy"},
                           {900, "The mystery of Star Wars", "It stood once for the ambition and poise of a young nation emerging from colonial rule, stretching its wings"}};

    for (const auto &a:v)
        bh.push(a);
    std::cout << "Begin: \n";
    bh.print();
    std::cout << "\nMin: \n";
    bh.top().print();

    bh.pop();
    std::cout << "\nAfter extract min: \n";
    bh.print();


}


int main() {
    //TEST_BH_INT();
    //TEST_BH_NEWS();

    TEST_FH_INT();
    //TEST_FH_NEWS();
}
