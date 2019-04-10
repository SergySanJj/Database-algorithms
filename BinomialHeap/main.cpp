#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits.h>

using namespace std;

template<typename KEY, typename DAT>
class Node {
public:
    Node(KEY _key, DAT _data) {
        key = _key;
        data = _data;
        degree = 0;
        child = parent = sibling = nullptr;
    }

    KEY key;
    DAT data;

    Node<KEY, DAT> *child;
    Node<KEY, DAT> *sibling;
    Node<KEY, DAT> *parent;

    int degree;
private:
};

template<typename KEY, typename DAT>
class BinomialHeap {
public:
    void insert(KEY key, DAT data) {
        _heap = Insertion(_heap, key, data);
    }

    void print() {
        ShowHeap(_heap);
    }

    pair<KEY, DAT> getMin() {
        auto res = getMin(_heap);
        return make_pair(res->key, res->data);
    }

    void extractMin() {
        _heap = extractMin(_heap);
    }

    pair<KEY, DAT> find(KEY key) {
        auto t = findNode(key);
        if (t != nullptr)
            return make_pair(t->key, t->data);
        else
            return make_pair(KEY(), DAT());
    }

    void decrease(KEY key, KEY newKey) {
        auto t = findNode(key);
        if (t != nullptr)
            decreaseKey(_heap, t, newKey);
        else
            return;
    }

    template<typename K, typename D>
    friend BinomialHeap<K, D> operator+(BinomialHeap<K, D> const &lhs, BinomialHeap<K, D> const &rhs);

private:
    list<Node<KEY, DAT> *> _heap;

    Node<KEY, DAT> *Merge(Node<KEY, DAT> *tree1, Node<KEY, DAT> *tree2) {
        if (tree1->key > tree2->key) {
            swap(tree1->key, tree2->key);
            swap(tree1->data, tree2->data);
        }
        tree2->parent = tree1;
        tree2->sibling = tree1->child;
        tree1->child = tree2;
        tree1->degree++;
        return tree1;
    }

    static list<Node<KEY, DAT> *> Union(list<Node<KEY, DAT> *> heap1, list<Node<KEY, DAT> *> heap2) {
        list<Node<KEY, DAT> *> newHeap;
        auto i = heap1.begin();
        auto j = heap2.begin();
        while (i != heap1.end() && j != heap2.end()) {
            if ((*i)->degree <= (*j)->degree) {
                newHeap.push_back(*i);
                i++;
            } else {
                newHeap.push_back(*j);
                j++;
            }
        }
        while (i != heap1.end()) {
            newHeap.push_back(*i);
            i++;
        }
        while (j != heap2.end()) {
            newHeap.push_back(*j);
            j++;
        }
        return newHeap;
    }

    // reorder degrees
    list<Node<KEY, DAT> *> Order(list<Node<KEY, DAT> *> MyHeap) {
        if (MyHeap.size() <= 1)
            return MyHeap;
        list<Node<KEY, DAT> *> newHeap;
        auto i = MyHeap.begin();
        auto j = MyHeap.begin();
        auto k = MyHeap.begin();

        if (MyHeap.size() == 2) {
            j = i;
            j++;
            k = MyHeap.end();
        } else {
            j++;
            k = j;
            k++;
        }
        while (i != MyHeap.end()) {
            if (j == MyHeap.end())
                i++;
            else if ((*i)->degree < (*j)->degree) {
                i++;
                j++;
                if (k != MyHeap.end())
                    k++;
            } else if (k != MyHeap.end() && (*i)->degree == (*j)->degree && (*i)->degree == (*k)->degree) {
                i++;
                j++;
                k++;
            } else if ((*i)->degree == (*j)->degree) {
                Node<KEY, DAT> *temp;
                *i = Merge(*i, *j);
                j = MyHeap.erase(j);
                if (k != MyHeap.end())
                    k++;
            }
        }
        return MyHeap;
    }

    list<Node<KEY, DAT> *> InsertTree(list<Node<KEY, DAT> *> _heap, Node<KEY, DAT> *tree) {
        list<Node<KEY, DAT> *> temp;
        temp.push_back(tree);
        temp = Union(_heap, temp);
        return Order(temp);
    }

    list<Node<KEY, DAT> *> DeleteMin(Node<KEY, DAT> *tree) {
        list<Node<KEY, DAT> *> heap;
        auto *temp = tree->child;
        Node<KEY, DAT> *minimum;
        while (temp) {
            minimum = temp;
            temp = temp->sibling;
            minimum->sibling = nullptr;
            heap.push_front(minimum);
        }
        return heap;
    }

    list<Node<KEY, DAT> *> Insertion(list<Node<KEY, DAT> *> _head, KEY key, DAT data) {
        auto *temp = new Node<KEY, DAT>(key, data);
        return InsertTree(_head, temp);
    }

    Node<KEY, DAT> *getMin(list<Node<KEY, DAT> *> _heap) {
        auto i = _heap.begin();
        auto *temp = *i;
        while (i != _heap.end()) {
            if ((*i)->key < temp->key)
                temp = *i;
            i++;
        }
        return temp;
    }

    list<Node<KEY, DAT> *> extractMin(list<Node<KEY, DAT> *> _heap) {
        list<Node<KEY, DAT> *> newHeap, lo;
        Node<KEY, DAT> *temp;
        temp = getMin(_heap);

        for (auto &it:_heap) {
            if (it != temp) {
                newHeap.push_back(it);
            }
        }

        lo = DeleteMin(temp);
        newHeap = Union(newHeap, lo);
        newHeap = Order(newHeap);
        return newHeap;
    }

    void ShowTree(Node<KEY, DAT> *root) {
        while (root) {
            cout << "(" << root->key << ", " << root->data << ") ";
            ShowTree(root->child);
            root = root->sibling;
        }
    }


    void ShowHeap(list<Node<KEY, DAT> *> heap) {
        for (auto &el: heap)
            ShowTree(el);
    }

    void decreaseKey(list<Node<KEY, DAT> *> heap, Node<KEY, DAT> *x, KEY k) {
        if (k > x->key) {
            return;
        }
        x->key = k;
        auto z = x->parent;
        while (z != nullptr) {
            if (z->key < x->key) {
                swap(z->key, x->key);
                swap(z->data, x->data);
                z = x->parent;
            } else break;
        }
    }

    Node<KEY, DAT> *findNode(KEY key) {
        for (auto el:_heap) {
            auto t = treeFind(key, el);
            if (t != nullptr)
                return t;
        }
        return nullptr;
    }

    Node<KEY, DAT> *treeFind(KEY key, Node<KEY, DAT> *root) {
        if (root == nullptr)
            return nullptr;

        if (root->key == key)
            return root;
        if (root->key < key) {
            auto t = treeFind(key, root->child);
            if (t != nullptr)
                return t;
            t = treeFind(key, root->sibling);
        }
        return nullptr;
    }
};

template<typename KEY, typename DAT>
BinomialHeap<KEY, DAT> operator+(BinomialHeap<KEY, DAT> const &lhs, BinomialHeap<KEY, DAT> const &rhs) {
    auto tmp = lhs;
    tmp._heap = BinomialHeap<KEY, DAT>::Union(tmp._heap, rhs._heap);
    return tmp;
}


int main() {
    BinomialHeap<int, int> bh;
    bh.insert(1, 1);
    bh.insert(3, 2);
    bh.insert(-1, 3);
    bh.insert(11, 4);

    bh.print();

    std::cout << "\nmin: " << bh.getMin().first << endl;

    bh.extractMin();
    bh.print();

    BinomialHeap<int, int> bh2;
    bh2.insert(-20, 5);
    bh2.insert(-30, 6);

    bh = bh + bh2;
    cout << "\n";

    bh.print();

    bh.decrease(-20, -40);
    bh.decrease(3, -2);
    cout << "\n";

    bh.print();

    return 0;
}