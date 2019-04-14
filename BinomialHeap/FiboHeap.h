//
// Created by isara on 14-Apr-19.
//

#ifndef BINOMIALHEAP_FIBOHEAP_H
#define BINOMIALHEAP_FIBOHEAP_H

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iostream>

template<typename T>
class Node {
public:
    T value;
    Node<T> *parent;
    Node<T> *child;
    Node<T> *left;
    Node<T> *right;
    int degree;
    bool mark;

    static Node<T> *createNode(T _value) {
        auto n = new Node<T>;
        n->value = _value;
        n->left = n->right = n;
        n->degree = 0;
        n->mark = false;
        n->child = nullptr;
        n->parent = nullptr;
        return n;
    }

private:
};

template<typename T>
class FibonacciHeap {
private:
    Node<T> *heap;
public:
    FibonacciHeap() {
        heap = _empty();
    }

    ~FibonacciHeap() {
        if (heap)
            _deleteAll(heap);
    }

    Node<T> *push(T value) {
        Node<T> *ret = Node<T>::createNode(value);
        heap = _merge(heap, ret);
        return ret;
    }

    void merge(FibonacciHeap &other) {
        heap = _merge(heap, other.heap);
        other.heap = _empty();
    }

    bool empty() {
        return heap == nullptr;
    }

    T top() {
        return heap->value;
    }

    T pop() {
        Node<T> *old = heap;
        heap = _pop(heap);
        T ret = old->value;
        delete old;
        return ret;
    }

    void decreaseKey(Node<T> *n, T value) {
        heap = _decreaseKey(heap, n, value);
    }

    Node<T> *find(T value) {
        return _find(heap, value);
    }

    void print() {
        if (heap) {
            print(heap, heap->left);
        }
    }

private:
    void print(Node<T> *node, Node<T> *begin) {
        std::cout << node->value << ' ';

        if (node->child) {
            print(node->child, node->child->left);
        }

        if (node != begin) {
            print(node->right, begin);
        }


    }

    Node<T> *_empty() {
        return nullptr;
    }

    void _deleteAll(Node<T> *n) {
        if (n != nullptr) {
            Node<T> *c = n;
            do {
                Node<T> *d = c;
                c = c->right;
                _deleteAll(d->child);
                delete d;
            } while (c != n);
        }
    }

    void _addChild(Node<T> *parent, Node<T> *child) {
        child->left = child->right = child;
        child->parent = parent;
        parent->degree++;
        parent->child = _merge(parent->child, child);
    }

    void _removeConnections(Node<T> *n) {
        if (n == nullptr)
            return;
        Node<T> *c = n;
        do {
            c->mark = false;
            c->parent = nullptr;
            c = c->right;
        } while (c != n);
    }

    Node<T> *_pop(Node<T> *n) {
        _removeConnections(n->child);
        if (n->right == n) {
            n = n->child;
        } else {
            n->right->left = n->left;
            n->left->right = n->right;
            n = _merge(n->right, n->child);
        }
        if (n == nullptr)
            return n;
        Node<T> *trees[64] = {nullptr};

        while (true) {
            if (trees[n->degree] != nullptr) {
                Node<T> *t = trees[n->degree];
                if (t == n)break;
                trees[n->degree] = nullptr;
                if (n->value < t->value) {
                    t->left->right = t->right;
                    t->right->left = t->left;
                    _addChild(n, t);
                } else {
                    t->left->right = t->right;
                    t->right->left = t->left;
                    if (n->right == n) {
                        t->right = t->left = t;
                        _addChild(t, n);
                        n = t;
                    } else {
                        n->left->right = t;
                        n->right->left = t;
                        t->right = n->right;
                        t->left = n->left;
                        _addChild(t, n);
                        n = t;
                    }
                }
                continue;
            } else {
                trees[n->degree] = n;
            }
            n = n->right;
        }
        Node<T> *min = n;
        Node<T> *start = n;
        do {
            if (n->value < min->value)min = n;
            n = n->right;
        } while (n != start);
        return min;
    }

    Node<T> *_cut(Node<T> *_heap, Node<T> *n) {
        if (n->right == n) {
            n->parent->child = nullptr;
        } else {
            n->right->left = n->left;
            n->left->right = n->right;
            n->parent->child = n->right;
        }
        n->right = n->left = n;
        n->mark = false;
        return _merge(_heap, n);
    }

    Node<T> *_decreaseKey(Node<T> *_heap, Node<T> *n, T value) {
        if (n->value < value)
            return _heap;
        n->value = value;
        if (n->parent) {
            if (n->value < n->parent->value) {
                _heap = _cut(_heap, n);
                Node<T> *parent = n->parent;
                n->parent = nullptr;
                while (parent != nullptr && parent->mark) {
                    _heap = _cut(_heap, parent);
                    n = parent;
                    parent = n->parent;
                    n->parent = nullptr;
                }
                if (parent != nullptr && parent->parent != nullptr)
                    parent->mark = true;
            }
        } else {
            if (n->value < _heap->value) {
                _heap = n;
            }
        }
        return _heap;
    }

    Node<T> *_find(Node<T> *_heap, T value) {
        Node<T> *n = _heap;
        if (n == nullptr)
            return nullptr;
        do {
            if (n->value == value)
                return n;
            Node<T> *ret = _find(n->child, value);
            if (ret)
                return ret;
            n = n->right;
        } while (n != _heap);
        return nullptr;
    }
};

template<typename T>
Node<T> *_merge(Node<T> *a, Node<T> *b) {
    if (a == nullptr)return b;
    if (b == nullptr)return a;
    if (a->value > b->value) {
        Node<T> *temp = a;
        a = b;
        b = temp;
    }
    Node<T> *an = a->right;
    Node<T> *bp = b->left;
    a->right = b;
    b->left = a;
    an->left = bp;
    bp->right = an;
    return a;
}

#endif //BINOMIALHEAP_FIBOHEAP_H
