//
// Created by Sergey on 17.02.2019.
//

#include <iostream>
#include <vector>

enum Color {
    black = false, red = true
};

template<typename T>
class Node {
public:
    Node() = default;

    Node(Node<T> *other) : data(other->data), left(other->left), right(other->right), parent(other->parent),
                           color(other->color) {}

    ~Node() = default;

    template<typename DAT> friend
    class RBTree;

private:
    static Node<T> *createNIL() {
        auto tmp = new Node<T>();
        tmp->color = black;
        return tmp;
    }

    T data;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;
    Color color = red; // true - red, false - black
};


template<typename T>
class RBTree {
public:
    RBTree() = delete;

    ~RBTree() {
        recursiveDelete(Root);
        delete NIL;
    }

    template<typename F>
    explicit RBTree(F _cmp): cmp(_cmp) {}

    void insert(const T &val) {
        insertNode(val);
    }

    T find(T data) {
        auto tmp = findNode(data);
        if (tmp == NIL) {
            return 0;
        } else
            return tmp->data;
    }

    static int cmpINT(int &a, int &b) {
        if (a == b)
            return 1;
        return (a < b) ? 0 : 2;
    }

    unsigned int getSize() const { return size; }

    void print() {
        std::cout << "Current version: " << currentVersion;
        if (currentVersion == latestVersion)
            std::cout << " (latest)\n";
        else
            std::cout << "\n";
        displayNodeFancy(Root, 2);
    }

    void resetTo(int version) {
        if (version >= 0 && version <= latestVersion) {
            currentVersion = version;
            Root = versions[version];
        } else
            return;
    }

    void lastVersion() {
        currentVersion = latestVersion;
        Root = versions[latestVersion];
    }

private:
    Node<T> *NIL = Node<T>::createNIL();
    Node<T> *Root = NIL;

    int latestVersion = 0;
    int currentVersion = 0;

    std::vector<Node<T> *> versions = {NIL};

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
    }

    void insertFixup(Node<T> *x) {
        /* check red-black properties */
        while (x != Root && x->parent->color == red) {
            /* we have a violation */
            if (x->parent->parent == nullptr)
                break;

            if (x->parent == x->parent->parent->left) {
                // COPY

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
                // COPY
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
        if (Root == NIL) {
            auto x = new Node<T>();
            x->data = data;
            x->parent = nullptr;
            x->left = NIL;
            x->right = NIL;
            x->color = red;
            Root = x;

            latestVersion++;
            if (currentVersion != latestVersion)
                currentVersion = latestVersion;

            versions.push_back(Root);
            return x;
        }

        auto rootCopy = new Node<T>(Root);


        Node<T> *current, *parent, *x;

        current = rootCopy;
        parent = nullptr;
        while (current != NIL) {
            parent = current;
            int tmp = cmp(data, current->data);

            if (tmp == 0 || tmp == 1) {
                if (current->left == NIL) break;

                auto leftCopy = new Node<T>(current->left);
                current->left = leftCopy;
                leftCopy->parent = current;
                current = leftCopy;
            } else {
                if (current->right == NIL) break;

                auto rightCopy = new Node<T>(current->right);
                rightCopy->parent = current;
                current->right = rightCopy;
                current = rightCopy;
            }
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
        versions.push_back(rootCopy);

        latestVersion++;
        if (currentVersion != latestVersion)
            currentVersion = latestVersion;
        Root = rootCopy;

        // Copy LR two levels up
        if (x->parent != nullptr)
        {
            CopyLR(x->parent);
            if (x->parent->parent != nullptr)
                CopyLR(x->parent->parent);
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

    void recursiveDelete(Node<T> *x) {
        if (x == NIL)
            return;
        recursiveDelete(x->left);
        recursiveDelete(x->right);
        delete x;
    }

    void displayNodeFancy(Node<T> *node, int tabs) {
        if (node == nullptr)
            return;
        if (node->right != nullptr)
            displayNodeFancy(node->right, tabs + 4);
        else std::cout << std::endl;
        for (int i = 0; i < tabs; i++)
            std::cout << " ";
        if (node == NIL)
            std::cout << "NIL";
        else
            std::cout << node->data;
        if (node->left != nullptr)
            displayNodeFancy(node->left, tabs + 4);
        else std::cout << std::endl;

    }

    void CopyLR(Node<T> *x) {
        if (x->left != NIL) {
            auto left = new Node<T>(x->left);
            left->parent = x;
            x->left = left;
        }
        if (x->right != NIL) {
            auto right = new Node<T>(x->right);
            right->parent = x;
            x->right = right;
        }
    }
};