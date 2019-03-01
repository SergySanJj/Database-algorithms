#include <iostream>

using namespace std;


template<typename T>
class SplayTree {
public:
    SplayTree() = delete;

    template <typename F>
    explicit SplayTree(F _cmp) : cmp(_cmp) {}

    ~SplayTree() = default;


private:

    int (*cmp)(const T &, const T &);

    template<typename DAT>
    class Node {
    public:
        Node<DAT> *left, *right, *parent = nullptr;
        DAT data;
    };

    Node<T> *Root = nullptr;

};

int main() {
    auto r = SplayTree<int>([](const int &a, const int &b) { return ((a < b) ? -1 : ((a > b) ? 1 : 0)); });
    return 0;
}