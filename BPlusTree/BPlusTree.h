//
// Created by Sergey on 08.04.2019.
//
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template<typename KEY, typename DAT>
class Node {
public:
    bool leaf;
    Node<KEY, DAT> *parent = nullptr;
    // brothers:
    Node<KEY, DAT> *right = nullptr;
    Node<KEY, DAT> *left = nullptr;

    std::vector<KEY> keys;
    std::vector<DAT> data;
    std::vector<Node<KEY, DAT> *> children;

    int keyNumber;

    explicit Node(int t) {
        leaf = false;
        keyNumber = 0;
        keys.resize(2 * t);
        data.resize(2 * t);
        children.resize(2 * t + 2);
    }

    int size() { return keys.size(); }

    bool hasKey(KEY key, int &pos) {
        for (auto &k:keys) {
            if (key == k)
                return true;
        }
        return false;
    }

    KEY minKey() {
        return keys[0];
    }

private:
};

template<typename KEY, typename DAT>
class BPlusTree {
public:
    BPlusTree() = delete;

    explicit BPlusTree(std::size_t _t) : t(_t) {}

    ~BPlusTree() = default;

    DAT find(KEY key) {
        auto leaf = getLeaf(key);
        auto it = std::find(leaf->keys.begin(), leaf->keys.end(), key);
        if (it != leaf->keys.end()) {
            return leaf->data[std::distance(leaf->keys.begin(), it)];
        } else
            return DAT();
    }

    void insert(KEY key, DAT data) {
        if (!Root) {
            Root = new Node<KEY, DAT>(t);
            Root->leaf = true;
        }

        auto leaf = getLeaf(key);

        int pos = 0;

        while (pos < leaf->keyNumber && leaf->keys[pos] < key) {
            pos++;
        }

        for (int i = leaf->keyNumber; i > pos; --i) {
            leaf->keys[i] = leaf->keys[i - 1];
            leaf->data[i] = leaf->data[i - 1];
        }

        leaf->keys[pos] = key;
        leaf->data[pos] = data;

        leaf->keyNumber++;

        if (leaf->keyNumber == 2 * t) {
            split(leaf);
        }
    }

    void print() {
        print(0, Root);
    }

    void sorted() {
        auto curr = Root;
        while (!curr->leaf) {
            curr = curr->children[0];
        }
        do {
            for (auto &el:curr->keys) {
                std::cout << el << " ";
            }
            std::cout << " | ";
            curr = curr->right;
        } while (curr->right);
    }

private:
    std::size_t t = 2;
    Node<KEY, DAT> *Root = nullptr;


    Node<KEY, DAT> *getLeaf(KEY key) {
        auto node = Root;

        while (!node->leaf)
            for (int i = 0; i <= node->keyNumber; ++i)
                if (i == node->keyNumber || key < node->keys[i]) {
                    node = node->children[i];
                    break;
                }

        return node;
    }

    void split(Node<KEY, DAT> *node) {
        auto newNode = new Node<KEY, DAT>(t);

        if (node->right) {
            newNode->right = node->right;
            node->right->left = newNode;
        }

        node->right = newNode;
        newNode->left = node;

        int middle = node->keys[t];
        newNode->keyNumber = t - 1;
        node->keyNumber = t;

        for (int i = 0; i <= newNode->keyNumber - 1; i++) {
            newNode->keys[i] = node->keys[i + t + 1];
            newNode->data[i] = node->data[i + t + 1];
            newNode->children[i] = node->children[i + t + 1];
            if (newNode->children[i])
                newNode->children[i]->parent = newNode;
        }

        newNode->children[newNode->keyNumber] = node->children[2 * t];
        if (newNode->children[newNode->keyNumber])
            newNode->children[newNode->keyNumber]->parent = newNode;

        if (node->leaf) {
            newNode->keyNumber++;
            newNode->leaf = true;

            for (int i = newNode->keyNumber - 1; i > 0; --i) {
                newNode->keys[i] = newNode->keys[i - 1];
                newNode->data[i] = newNode->data[i - 1];
            }
            newNode->keys[0] = node->keys[t];
            newNode->data[0] = node->data[t];
        }

        if (node == Root) {
            Root = new Node<KEY, DAT>(t);
            Root->keys[0] = middle;
            Root->children[0] = node;
            Root->children[1] = newNode;
            Root->keyNumber = 1;
            node->parent = Root;
            newNode->parent = Root;
        } else {
            newNode->parent = node->parent;
            auto parent = node->parent;

            int pos = 0;

            while (pos < parent->keyNumber && parent->keys[pos] < middle)
                pos++;

            for (int i = parent->keyNumber; i > pos; i--)
                parent->keys[i] = parent->keys[i - 1];
            for (int i = parent->keyNumber + 1; i > pos + 1; i--)
                parent->children[i] = parent->children[i - 1];

            parent->keys[pos] = middle;
            parent->children[pos + 1] = newNode;

            parent->keyNumber++;

            if (parent->keyNumber == 2 * t)
                split(parent);
        }
    }

    void print(int deep, Node<KEY, DAT> *node) {
        for (int i = 0; i < deep * node->keys.size(); ++i) {
            std::cout << '\t';
        }

        if (node->leaf)
            std::cout << " leaf ";
        std::cout << "  ";
        for (int i = 0; i < node->keyNumber; ++i) {
            std::cout << node->keys[i] << ' ';
        }
        std::cout << "\n";

        bool needMargin = false;
        for (int i = node->keyNumber; i >= 0; i--) {
            if (node->children[i]) {
                print(deep + 1, node->children[i]);
                needMargin = true;
            }
        }
        if (needMargin) {
            std::cout << '\n';
        }
    }
};