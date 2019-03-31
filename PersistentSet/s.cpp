#include <iostream>


#include <queue>
#include <iostream>
#include <utility>
#include <vector>

enum Color {
    red, black
};

template<class Key, class Dat>
struct Node {
    Node() : color(red), left(nullptr), right(nullptr), parent(nullptr) {}

    Node(const Node<Key, Dat> *node) : key(node->key), data(node->data), color(node->color),
                                       left(node->left), right(node->right),
                                       parent(node->parent) {}

    Key key;
    Dat data;
    unsigned color;
    Node<Key, Dat> *left;
    Node<Key, Dat> *right;
    Node<Key, Dat> *parent;
};


template<class Key, class Dat>
class RBTree {
public:
    ~RBTree();

    //functions to print the tree
    void printLevels(Node<Key, Dat> *root) const;     //uses the queue to print tree level by level


    Dat search(const Key &key) const;

    void inserKey(const Key &key, const Dat &data);

    //Persistent set methods
    void saveTree(Node<Key, Dat> *root, Node<Key, Dat> *node);

    void print();

private:
    Node<Key, Dat> *_root = nullptr;
    std::vector<Node<Key, Dat> *> versions;

    Node<Key, Dat> *searchKey(const Key &key, Node<Key, Dat> *node) const;

    void printPostTree(const Node<Key, Dat> *node) const;

    void printPreTree(const Node<Key, Dat> *node) const;

    void printInTree(const Node<Key, Dat> *node) const;

    void deleteTree(Node<Key, Dat> *node);

    int getColor(Node<Key, Dat> *node);

    void setColor(Node<Key, Dat> *node, int color);

    Node<Key, Dat> *insertRBTree(Node<Key, Dat> *node, Node<Key, Dat> *ptr);

    void rotateLeft(Node<Key, Dat> *node);

    void rotateRight(Node<Key, Dat> *node);

    Node<Key, Dat> *minKeyNode(Node<Key, Dat> *node);

    Node<Key, Dat> *maxKeyNode(Node<Key, Dat> *node);

    void insertCase1(Node<Key, Dat> *node);

    void insertCase2(Node<Key, Dat> *node);

    void insertCase3(Node<Key, Dat> *node);

    void insertCase4(Node<Key, Dat> *node);

    void insertCase5(Node<Key, Dat> *node);

    void print(int i);
};


template<class Key, class Dat>
RBTree<Key, Dat>::~RBTree() {
    deleteTree(this->_root);
}

template<class Key, class Dat>
struct Level {
    int level = 0;
    Node<Key, Dat> *node = nullptr;
};


template<class Key, class Dat>
inline Dat RBTree<Key, Dat>::search(const Key &key) const {
    Node<Key, Dat> *node = searchKey(key, this->_root);
    return node->data;
}

template<class Key, class Dat>
inline Node<Key, Dat> *RBTree<Key, Dat>::searchKey(const Key &key, Node<Key, Dat> *node) const {
    if (node == nullptr)
        return nullptr;
    if (node->key == key)
        return node;
    if (node->key > key)
        return searchKey(key, node->left);
    if (node->key < key)
        return searchKey(key, node->right);
}

template<class Key, class Dat>
void RBTree<Key, Dat>::deleteTree(Node<Key, Dat> *node) {
    if (node->left != nullptr)
        deleteTree(node->left);
    if (node->right != nullptr)
        deleteTree(node->right);
    delete node;
}

template<class Key, class Dat>
int RBTree<Key, Dat>::getColor(Node<Key, Dat> *node) {
    if (node == nullptr)
        return black;
    return node->color;
}

template<class Key, class Dat>
void RBTree<Key, Dat>::setColor(Node<Key, Dat> *node, int color) {
    if (node == nullptr)
        return;
    node->color = color;
}

template<class Key, class Dat>
void RBTree<Key, Dat>::inserKey(const Key &key, const Dat &data) {
    Node<Key, Dat> *node = new Node<Key, Dat>();
    node->key = key;
    node->data = data;
    this->_root = insertRBTree(this->_root, node);
    saveTree(_root, node);
    insertCase1(node);
    versions.push_back(this->_root);
}


template<class Key, class Dat>
inline Node<Key, Dat> *RBTree<Key, Dat>::insertRBTree(Node<Key, Dat> *node, Node<Key, Dat> *ptr) {
    if (node == nullptr)
        return ptr;
    if (ptr->key < node->key) {
        node->left = insertRBTree(node->left, ptr);
        node->left->parent = node;
    } else if (ptr->key > node->key) {
        node->right = insertRBTree(node->right, ptr);
        node->right->parent = node;
    }

    return node;
}

template<class Key, class Dat>
void RBTree<Key, Dat>::rotateLeft(Node<Key, Dat> *node) {
    Node<Key, Dat> *rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != nullptr) {
        node->right->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr)
        this->_root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}

template<class Key, class Dat>
void RBTree<Key, Dat>::rotateRight(Node<Key, Dat> *node) {
    Node<Key, Dat> *leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr)
        node->left->parent = node;
    leftChild->parent = node->parent;
    if (node->parent == nullptr)
        this->_root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}

template<class Key, class Dat>
inline Node<Key, Dat> *RBTree<Key, Dat>::minKeyNode(Node<Key, Dat> *node) {
    Node<Key, Dat> *ptr = node;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template<class Key, class Dat>
inline Node<Key, Dat> *RBTree<Key, Dat>::maxKeyNode(Node<Key, Dat> *node) {
    Node<Key, Dat> *ptr = node;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}

template<class Key, class Dat>
void RBTree<Key, Dat>::insertCase1(Node<Key, Dat> *node) {
    if (node->parent == nullptr)
        node->color = black;
    else
        insertCase2(node);
}

template<class Key, class Dat>
void RBTree<Key, Dat>::insertCase2(Node<Key, Dat> *node) {
    if (node->parent->color == black)
        return;
    else
        insertCase3(node);
}

template<class Key, class Dat>
void RBTree<Key, Dat>::insertCase3(Node<Key, Dat> *node) {
    Node<Key, Dat> *u, *g;
    g = node->parent->parent;
    if (g != nullptr) {
        if (g->left == node->parent) {
            u = g->right;
        } else {
            u = g->left;
        }
    }

    if ((u != nullptr) && (u->color == red)) {
        node->parent->color = black;
        u->color = black;
        g->color = red;
        insertCase1(g);
    } else {
        insertCase4(node);
    }
}

template<class Key, class Dat>
void RBTree<Key, Dat>::insertCase4(Node<Key, Dat> *node) {
    Node<Key, Dat> *g = node->parent->parent;

    if (g != nullptr) {
        if (node == node->parent->right && node->parent == g->left) {
            rotateLeft(node->parent);
            node = node->left;
        } else if (node == node->parent->left && node->parent == g->right) {
            rotateRight(node->parent);
            node = node->right;
        }
    }
    insertCase5(node);
}

template<class Key, class Dat>
void RBTree<Key, Dat>::insertCase5(Node<Key, Dat> *node) {
    Node<Key, Dat> *g = node->parent->parent;
    node->parent->color = red;

    if (g != nullptr) {
        g->color = red;
        if (node == node->parent->left && node->parent == g->left) {
            rotateRight(g);
        } else {
            rotateLeft(g);
        }
    }
}

template<class Key, class Dat>
void RBTree<Key, Dat>::saveTree(Node<Key, Dat> *root, Node<Key, Dat> *node) {
    if (node == root)
        return;
    Node<Key, Dat> *parent = node->parent;
    if (node->parent == nullptr) {
        return;
    }
    Node<Key, Dat> *newParent = new Node<Key, Dat>(node->parent);
    if (parent->left) {
        parent->left->parent = newParent;
        newParent->left = parent->left;
    }
    if (parent->right) {
        parent->right->parent = newParent;
        newParent->right = parent->right;
    }

    if (node == parent->left) {
        parent->left = nullptr;
    } else if (node == parent->right) {
        parent->right = nullptr;
    }

    while (parent != root) {
        Node<Key, Dat> *grandparent = parent->parent;
        Node<Key, Dat> *newGrandparent = new Node<Key, Dat>(grandparent);
        if (grandparent->left == parent) {
            newGrandparent->left = newParent;
            if (grandparent->right != nullptr) {
                newGrandparent->right = grandparent->right;
                newGrandparent->right->parent = newGrandparent;
            }
        } else {
            newGrandparent->right = newParent;
            if (grandparent->left != nullptr) {
                newGrandparent->left = grandparent->left;
                newGrandparent->left->parent = newGrandparent;
            }
        }
        newParent->parent = newGrandparent;
        parent = parent->parent;
        newParent = newParent->parent;
    }
    this->_root = newParent;
}


