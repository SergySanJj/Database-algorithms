#include <iostream>


#include <queue>
#include <iostream>
#include <utility>
#include <vector>

enum Color {
    black, red
};

template<typename Key, typename Dat>
class Node {
public:
    Node(const Node<Key, Dat> *node) : key(node->key), data(node->data), color(node->color),
                                       left(node->left), right(node->right),
                                       parent(node->parent) {}

private:
    Key key;
    Dat data;

    Node<Key, Dat> *left = nullptr;
    Node<Key, Dat> *right = nullptr;
    Node<Key, Dat> *parent = nullptr;

    Color color = Color::red;
};

template<class TKey, class TData>
struct TNode {
    TNode() : color(red), left(nullptr), right(nullptr), parent(nullptr) {}

    TNode(const TNode<TKey, TData> *node) : key(node->key), data(node->data), color(node->color),
                                            left(node->left), right(node->right),
                                            parent(node->parent) {}

    TKey key;
    TData data;
    unsigned color;
    TNode<TKey, TData> *left;
    TNode<TKey, TData> *right;
    TNode<TKey, TData> *parent;
};

template<typename Key, typename Dat>
class Tree {
public:
    Tree() = default;

    ~Tree() = default;

    void insert(const Key &key, const Dat &data);

    void savetree(Node<Key, Dat> *root, Node<Key, Dat> *node);

private:
    Node<Key, Dat> Root = nullptr;
    std::vector<TNode<Key, Dat> *> versions;

    Color color(Node<Key, Dat> *node) { return (node == nullptr) ? black : node->color; }

    void setColor(Node<Key, Dat> *node, Color color) {
        if (node == nullptr)
            return;
        node->color = color;
    }

    Node<Key, Dat> *insertRBTree(Node<Key, Dat> *node, Node<Key, Dat> *ptr) {

    }

    void rotateLeft(Node<Key, Dat> *node) {
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

    void rotateRight(Node<Key, Dat> *node) {
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

    Node<Key, Dat> *minKeyNode(Node<Key, Dat> *node) {}

    Node<Key, Dat> *maxKeyNode(Node<Key, Dat> *node) {}

    void insertCase1(Node<Key, Dat> *node) {}

    void insertCase2(Node<Key, Dat> *node) {}

    void insertCase3(Node<Key, Dat> *node) {}

    void insertCase4(Node<Key, Dat> *node) {}

    void insertCase5(Node<Key, Dat> *node) {}

    void deleteTree(Node<Key, Dat> *node) {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;

    }
};


template<class TKey, class TData>
class RBTree {
public:
    ~RBTree();

    //functions to print the tree
    void printLevels(TNode<TKey, TData> *root) const;     //uses the queue to print tree level by level


    TData search(const TKey &key) const;

    void insertKey(const TKey &key, const TData &data);

    //Persistent set methods
    void saveTree(TNode<TKey, TData> *root, TNode<TKey, TData> *node);

    void print();

private:
    TNode<TKey, TData> *_root = nullptr;
    std::vector<TNode<TKey, TData> *> versions;

    TNode<TKey, TData> *searchKey(const TKey &key, TNode<TKey, TData> *node) const;

    void printPostTree(const TNode<TKey, TData> *node) const;

    void printPreTree(const TNode<TKey, TData> *node) const;

    void printInTree(const TNode<TKey, TData> *node) const;

    void deleteTree(TNode<TKey, TData> *node);

    int getColor(TNode<TKey, TData> *node);

    void setColor(TNode<TKey, TData> *node, int color);

    TNode<TKey, TData> *insertRBTree(TNode<TKey, TData> *node, TNode<TKey, TData> *ptr);

    void rotateLeft(TNode<TKey, TData> *node);

    void rotateRight(TNode<TKey, TData> *node);

    TNode<TKey, TData> *minKeyNode(TNode<TKey, TData> *node);

    TNode<TKey, TData> *maxKeyNode(TNode<TKey, TData> *node);

    void insertCase1(TNode<TKey, TData> *node);

    void insertCase2(TNode<TKey, TData> *node);

    void insertCase3(TNode<TKey, TData> *node);

    void insertCase4(TNode<TKey, TData> *node);

    void insertCase5(TNode<TKey, TData> *node);

    void print(int i);
};


template<class TKey, class TData>
RBTree<TKey, TData>::~RBTree() {
    deleteTree(this->_root);
}

template<class TKey, class TData>
struct Level {
    int level = 0;
    TNode<TKey, TData> *node = nullptr;
};


template<class TKey, class TData>
inline TData RBTree<TKey, TData>::search(const TKey &key) const {
    TNode<TKey, TData> *node = searchKey(key, this->_root);
    return node->data;
}

template<class TKey, class TData>
inline TNode<TKey, TData> *RBTree<TKey, TData>::searchKey(const TKey &key, TNode<TKey, TData> *node) const {
    if (node == nullptr)
        return nullptr;
    if (node->key == key)
        return node;
    if (node->key > key)
        return searchKey(key, node->left);
    if (node->key < key)
        return searchKey(key, node->right);
}

template<class TKey, class TData>
void RBTree<TKey, TData>::deleteTree(TNode<TKey, TData> *node) {
    if (node->left != nullptr)
        deleteTree(node->left);
    if (node->right != nullptr)
        deleteTree(node->right);
    delete node;
}

template<class TKey, class TData>
int RBTree<TKey, TData>::getColor(TNode<TKey, TData> *node) {
    if (node == nullptr)
        return black;
    return node->color;
}

template<class TKey, class TData>
void RBTree<TKey, TData>::setColor(TNode<TKey, TData> *node, int color) {
    if (node == nullptr)
        return;
    node->color = color;
}

template<class TKey, class TData>
void RBTree<TKey, TData>::insertKey(const TKey &key, const TData &data) {
    TNode<TKey, TData> *node = new TNode<TKey, TData>();
    node->key = key;
    node->data = data;
    this->_root = insertRBTree(this->_root, node);
    saveTree(_root, node);
    insertCase1(node);
    versions.push_back(this->_root);
}


template<class TKey, class TData>
inline TNode<TKey, TData> *RBTree<TKey, TData>::insertRBTree(TNode<TKey, TData> *node, TNode<TKey, TData> *ptr) {
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

template<class TKey, class TData>
void RBTree<TKey, TData>::rotateLeft(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *rightChild = node->right;
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

template<class TKey, class TData>
void RBTree<TKey, TData>::rotateRight(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *leftChild = node->left;
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

template<class TKey, class TData>
inline TNode<TKey, TData> *RBTree<TKey, TData>::minKeyNode(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *ptr = node;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template<class TKey, class TData>
inline TNode<TKey, TData> *RBTree<TKey, TData>::maxKeyNode(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *ptr = node;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}

template<class TKey, class TData>
void RBTree<TKey, TData>::insertCase1(TNode<TKey, TData> *node) {
    if (node->parent == nullptr)
        node->color = black;
    else
        insertCase2(node);
}

template<class TKey, class TData>
void RBTree<TKey, TData>::insertCase2(TNode<TKey, TData> *node) {
    if (node->parent->color == black)
        return;
    else
        insertCase3(node);
}

template<class TKey, class TData>
void RBTree<TKey, TData>::insertCase3(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *u, *g;
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

template<class TKey, class TData>
void RBTree<TKey, TData>::insertCase4(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *g = node->parent->parent;

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

template<class TKey, class TData>
void RBTree<TKey, TData>::insertCase5(TNode<TKey, TData> *node) {
    TNode<TKey, TData> *g = node->parent->parent;
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

template<class TKey, class TData>
void RBTree<TKey, TData>::saveTree(TNode<TKey, TData> *root, TNode<TKey, TData> *node) {
    if (node == root)
        return;
    TNode<TKey, TData> *parent = node->parent;
    if (node->parent == nullptr) {
        return;
    }
    TNode<TKey, TData> *newParent = new TNode<TKey, TData>(node->parent);
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
        TNode<TKey, TData> *grandparent = parent->parent;
        TNode<TKey, TData> *newGrandparent = new TNode<TKey, TData>(grandparent);
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


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}