#include <iostream>
#include <vector>

template<typename KEY, typename DAT>
class Node {
public:
    std::vector<KEY> keys;
    std::vector<DAT*> data;
    std::vector<Node<KEY, DAT> *> sons;

    int size() { return keys.size(); }

private:
};

template<typename KEY, typename DAT>
class BPlusTree {
public:
    BPlusTree() = delete;

    explicit BPlusTree(std::size_t _t) : t(_t) {}

    ~BPlusTree() = default;

    void insert(KEY key, DAT data) {
        if
    }

    void find(const KEY &key) const {}

private:
    std::size_t t = 2;
    Node<KEY, DAT> *Root = nullptr;
};


int main() {

    return 0;
}