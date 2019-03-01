#include <iostream>

using namespace std;

template<typename DAT>
class Node {
public:
    Node(const DAT &_data) : data(_data) {}

    Node<DAT> *left, *right, *parent = nullptr;
    DAT data;
};

template<typename T>
class SplayTree {
public:
    SplayTree() = delete;

    template<typename F>
    explicit SplayTree(F _cmp) : cmp(_cmp) {}

    ~SplayTree() = default;

    void splay(Node<T> *x) {
        while (x->parent) {
            if (!x->parent->parent) {
                if (x->parent->left == x)
                    rotateRight(x->parent);
                else
                    rotateLeft(x->parent);
            } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
                rotateRight(x->parent->parent);
                rotateRight(x->parent);
            } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
                rotateLeft(x->parent->parent);
                rotateLeft(x->parent);
            } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
                rotateRight(x->parent);
                rotateLeft(x->parent);
            } else {
                rotateLeft(x->parent);
                rotateRight(x->parent);
            }
        }
    }

    void insert(const T &val) {
        // binary insert
        auto x = new Node<T>(val);

        Node<T> *prev = nullptr;
        auto curr = Root;
        while (curr != nullptr) {
            prev = curr;
            int compare = cmp(curr->data, val);
            if (compare == -1 || compare == 0)
                curr = curr->left;

            else
                curr = curr->right;
        }
        if (prev == nullptr)
            Root = x;
        else {
            x->parent = prev;
            int compare = cmp(prev->data, val);
            if (compare == -1 || compare == 0)
                prev->left = x;
            else
                prev->right = x;
        }
        // splay
        splay(x);
    }

    bool exists(const T &val) {
        auto curr = Root;
        auto prev = Root;
        while (curr != nullptr) {
            prev = curr;
            int compare = cmp(curr->data, val);
            if (compare == -1 || compare == 0)
                curr = curr->left;

            else
                curr = curr->right;
        }
        if (cmp(prev->data, val) == 0)
            return true;
        else
            return false;

    }

private:

    int (*cmp)(const T &, const T &);

    Node<T> *Root = nullptr;

    void rotateLeft(Node<T> *x) {
        Node<T> *y = x->right;
        if (y) {
            x->right = y->left;
            if (y->left) y->left->parent = x;
            y->parent = x->parent;
        }

        if (!x->parent) Root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->left = x;
        x->parent = y;
    }

    void rotateRight(Node<T> *x) {
        Node<T> *y = x->left;
        if (y) {
            x->left = y->right;
            if (y->right) y->right->parent = x;
            y->parent = x->parent;
        }
        if (!x->parent) Root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->right = x;
        x->parent = y;
    }


};

int main() {
    auto t = SplayTree<int>([](const int &a, const int &b) { return ((a < b) ? -1 : ((a > b) ? 1 : 0)); });
    for (int i = 0; i < 10; i++)
        t.insert(i);
    std::cout << t.exists(9) << " " << t.exists(111);
    return 0;
}