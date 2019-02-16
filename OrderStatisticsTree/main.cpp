#include <iostream>

enum Color {
    black = false, red = true
};

class News {
public:
    News() {
        title = "";
        text = "";
        categoryId = -1;
    }

    News(std::string _title, std::string _text, int _Id, int _views) :
            title(std::move(_title)), text(std::move(_text)), categoryId(_Id), views(_views) {}

    std::string getTitle() const { return title; }

    int getViews() const { return views; }

    void print() {
        std::cout << "Title: " << title << "\n" << "Text: " << text << '\n' << "Views: " << views << std::endl;
    }

private:
    std::string title;
    std::string text;
    int categoryId;
    int agencyId;
    int views;
};

template<typename T>
class Node {
public:
    Node() = default;

    Node(T _data) : data(_data) {}

    ~Node() = default;

    template<typename DAT> friend
    class OrderStatisticsTree;

private:
    static Node<T> *createNIL() {
        Node<T> *tmp = new Node<T>();
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
class OrderStatisticsTree {
public:
    OrderStatisticsTree() = delete;

    template<typename F>
    explicit OrderStatisticsTree(F _cmp): cmp(_cmp) {}

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

private:
    Node<T> *NIL = Node<T>::createNIL();

    Node<T> *Root = NIL;

    // Function that compares 2 typename T elements with <= order
    bool (*cmp)(T &, T &);


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
            if (cmp(data, current->data)) return (current);
            parent = current;
            current = cmp(data, current->data) ?
                      current->left : current->right;
        }

        x = new Node<T>();
        x->data = data;
        x->parent = parent;
        x->left = NIL;
        x->right = NIL;
        x->color = red;

        if (parent) {
            if (cmp(data, parent->data))
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
            if (cmp(data, curr->data)) {
                prev = curr;
                curr = curr->left;
            } else {
                prev = curr;
                curr = curr->right;
            }
        }
        return prev;
    }

};

int main() {
    OrderStatisticsTree<int> t([](int &a, int &b) {
        return a < b;
    });

    for (int i = 1; i < 1000; i++)
        t.insert(i);

    std::cout << t.find(0) << " " << t.find(1) << std::endl;

    return 0;
}