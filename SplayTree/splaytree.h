//
// Created by Sergey on 03.03.2019.
//

#pragma once

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
        while (x->parent != nullptr) {
            // Zig
            if (x->parent->parent == nullptr) {
                if (x->parent->left == x)
                    rotateRight(x->parent);
                else
                    rotateLeft(x->parent);
            }
                // Zig-Zig
            else if (x->parent->left == x && x->parent->parent->left == x->parent) {
                rotateRight(x->parent->parent);
                rotateRight(x->parent);
            } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
                rotateLeft(x->parent->parent);
                rotateLeft(x->parent);
            }
                // Zig-Zag
            else if (x->parent->left == x && x->parent->parent->right == x->parent) {
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
        auto x = new Node<KEY, DAT>(key, dat);

        Node<KEY, DAT> *prev = nullptr;
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

    bool exists(const KEY &key) const {
        auto curr = Root;
        while (curr != nullptr) {
            if (curr->key == key)
                break;

            if (key < curr->key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (curr == nullptr)
            return false;
        return (curr->key == key);
    }

    DAT find(const KEY &key) const {
        auto curr = Root;
        while (curr != nullptr) {
            if (curr->key == key)
                break;

            if (key < curr->key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (curr == nullptr)
            return DAT();
        if (curr->key == key)
            return curr->data;
        else
            return DAT();
    }

    int height() const {
        return findHeight(Root);
    }

    double avgHeight() const {
        int lc = 0;
        int sum = 0;
        findAvgHeight(Root, sum, lc, 0);

        return (sum / (double) lc);
    }

private:
    Node<KEY, DAT> *Root = nullptr;

    void del(Node<KEY, DAT> *curr) {
        if (curr == nullptr)
            return;
        del(curr->left);
        del(curr->right);

        delete curr;
    }

    void rotateLeft(Node<KEY, DAT> *x) {
        Node<KEY, DAT> *y = x->right;
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

    void rotateRight(Node<KEY, DAT> *x) {
        Node<KEY, DAT> *y = x->left;
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

    int findHeight(Node<KEY, DAT> *curr) const {
        if (curr == nullptr) {
            return -1;
        }

        int left = findHeight(curr->left);
        int right = findHeight(curr->right);

        if (left > right) {
            return left + 1;
        } else {
            return right + 1;
        }
    }

    void findAvgHeight(Node<KEY, DAT> *curr, int &sum, int &leafs, int height) const {
        if (curr->left == nullptr && curr->right == nullptr) {
            sum += height;
            leafs++;
            return;
        }
        if (curr->left != nullptr)
            findAvgHeight(curr->left, sum, leafs, height + 1);
        if (curr->right != nullptr)
            findAvgHeight(curr->right, sum, leafs, height + 1);

    }
};
