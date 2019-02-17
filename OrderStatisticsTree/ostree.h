//
// Created by Sergey on 17.02.2019.
//

#ifndef ORDERSTATISTICSTREE_OSTREE_H
#define ORDERSTATISTICSTREE_OSTREE_H

enum Color {
    black = false, red = true
};

template<typename T>
class Node {
public:
    Node() = default;

    ~Node() = default;

    template<typename DAT> friend
    class OrderStatisticsTree;

private:
    static Node<T> *createNIL() {
        auto tmp = new Node<T>();
        tmp->color = black;
        tmp->size = 0;
        return tmp;
    }

    T data;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;
    Color color = red; // true - red, false - black
    unsigned int size;
};


template<typename T>
class OrderStatisticsTree {
public:
    OrderStatisticsTree() = delete;

    ~OrderStatisticsTree() {
        recursiveDelete(Root);
        delete NIL;
    }

    template<typename F>
    explicit OrderStatisticsTree(F _cmp): cmp(_cmp) {}

    void insert(const T &val) {
        insertNode(val);
        size++;
    }

    T find(T data) {
        auto tmp = findNode(data);
        if (tmp == NIL) {
            return 0;
        } else
            return tmp->data;
    }

    T orderStatistic(unsigned int i) {
        if (i > size)
            return T();
        else {
            auto p = orderStatisticNode(Root, i);
            if (p == NIL)
                return T();
            return orderStatisticNode(Root, i)->data;
        }
    }

    static int cmpINT(int &a, int &b) {
        if (a == b)
            return 1;
        return (a < b) ? 0 : 2;
    }

    unsigned int getSize() const { return size; }

private:
    Node<T> *NIL = Node<T>::createNIL();

    Node<T> *Root = NIL;

    // Function that compares 2 typename T elements with <= order
    int (*cmp)(T &, T &);

    unsigned int size = 0;


    void rotateLeft(Node<T> *x) {
        Node<T> *y = x->right;

        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;

        if (y != NIL) y->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        } else {
            Root = y;
        }

        y->left = x;
        if (x != NIL) x->parent = y;

        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
    }

    void rotateRight(Node<T> *x) {
        Node<T> *y = x->left;

        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;

        if (y != NIL) y->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
        } else {
            Root = y;
        }

        y->right = x;
        if (x != NIL) x->parent = y;

        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
    }

    void insertFixup(Node<T> *x) {
        /* check red-black properties */
        while (x != Root && x->parent->color == red) {
            /* we have a violation */
            if (x->parent == x->parent->parent->left) {
                Node<T> *y = x->parent->parent->right;
                if (y->color == red) {

                    /* uncle is red */
                    x->parent->color = black;
                    y->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
                } else {

                    /* uncle is black */
                    if (x == x->parent->right) {
                        /* make x a left child */
                        x = x->parent;
                        rotateLeft(x);
                    }

                    /* recolor and rotate */
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    rotateRight(x->parent->parent);
                }
            } else {

                /* mirror image of above code */
                Node<T> *y = x->parent->parent->left;
                if (y->color == red) {

                    /* uncle is red */
                    x->parent->color = black;
                    y->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
                } else {

                    /* uncle is black */
                    if (x == x->parent->left) {
                        x = x->parent;
                        rotateRight(x);
                    }
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    rotateLeft(x->parent->parent);
                }
            }
        }
        Root->color = black;
    }

    Node<T> *insertNode(T data) {
        Node<T> *current, *parent, *x;

        current = Root;
        parent = nullptr;
        while (current != NIL) {
            current->size++;
            parent = current;
            int tmp = cmp(data, current->data);
            current = (tmp == 0 || tmp == 1) ?
                      current->left : current->right;
        }

        x = new Node<T>();
        x->data = data;
        x->parent = parent;
        x->left = NIL;
        x->right = NIL;
        x->color = red;

        if (parent) {
            int tmp = cmp(data, parent->data);
            if (tmp == 0 || tmp == 1)
                parent->left = x;
            else
                parent->right = x;
        } else {
            Root = x;
        }
        insertFixup(x);

        return (x);
    }

    Node<T> *findNode(T data) {
        Node<T> *curr = Root;
        Node<T> *prev = Root;
        while (curr != NIL) {
            if (cmp(data, curr->data) == 0) {
                prev = curr;
                curr = curr->left;
            } else {
                prev = curr;
                curr = curr->right;
            }
        }
        if (cmp(prev->data, data) == 1)
            return prev;
        return NIL;
    }

    Node<T> *orderStatisticNode(Node<T> *x, unsigned int i) {
        if (x == NIL)
            return NIL;
        int r = x->left->size + 1;
        if (i == r)
            return x;
        else if (i < r)
            return orderStatisticNode(x->left, i);
        else
            return orderStatisticNode(x->right, i - r);
    }

    void recursiveDelete(Node<T> *x) {
        if (x == NIL)
            return;
        recursiveDelete(x->left);
        recursiveDelete(x->right);
        delete x;
    }
};

#endif //ORDERSTATISTICSTREE_OSTREE_H
