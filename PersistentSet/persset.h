//
// Created by Sergey on 17.02.2019.
//

enum Color {
    black = false, red = true
};

template<typename T>
class Node {
public:
    Node() = default;

    ~Node() = default;

    Node(const Node<Key, Data> *node) : key(node->key), data(node->data), color(node->color),
                                            left(node->left), right(node->right),
                                            parent(node->parent) {}

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

    void recursiveDelete(Node<T> *x) {
        if (x == NIL)
            return;
        recursiveDelete(x->left);
        recursiveDelete(x->right);
        delete x;
    }
};