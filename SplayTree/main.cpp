#include <iostream>

using namespace std;

template<typename KEY, class DAT>
class Node {
public:
    Node(const KEY &_key, const DAT &_data) : key(_key), data(_data) {}

    Node<KEY, DAT> *left = nullptr;
    Node<KEY, DAT> *right = nullptr;
    Node<KEY, DAT> *parent = nullptr;

    DAT data;
    KEY key;
};

template<typename KEY, class DAT>
class SplayTree {
public:
    SplayTree() = default;

    ~SplayTree() {
        del(Root);
    }

    void splay(Node<KEY, DAT> *x) {
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

    void insert(const KEY &key, const DAT &dat) {
        // binary insert
        auto x = new Node<DAT, KEY>(key, dat);

        Node<DAT, KEY> *prev = nullptr;
        auto curr = Root;
        while (curr != nullptr) {
            prev = curr;
            if (key <= curr->key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (prev == nullptr)
            Root = x;
        else {
            x->parent = prev;
            if (key <= prev->key)
                prev->left = x;
            else
                prev->right = x;
        }
        // splay
        splay(x);
    }

    bool exists(const KEY &key) {
        auto curr = Root;
        auto prev = Root;
        while (curr != nullptr) {
            prev = curr;
            if (key <= curr->key)
                curr = curr->left;

            else
                curr = curr->right;
        }
        if (prev->key == key)
            return true;
        else
            return false;

    }

private:
    Node<KEY, DAT> *Root = nullptr;

    void del(Node<DAT, KEY> *curr) {
        if (curr == nullptr)
            return;
        del(curr->left);
        del(curr->right);

        delete curr;
    }

    void rotateLeft(Node<DAT, KEY> *x) {
        Node<DAT, KEY> *y = x->right;
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

    void rotateRight(Node<DAT, KEY> *x) {
        Node<DAT, KEY> *y = x->left;
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
    auto t = SplayTree<int, int>();
    for (int i = 0; i < 10; i++)
        t.insert(i, i);
    std::cout << t.exists(9) << " " << t.exists(111);
    return 0;
}