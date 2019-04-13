#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iostream>


template<typename T>
struct BinomialNode {
    T mValue;
    BinomialNode *mRight;
    BinomialNode *mChild;

    BinomialNode(const T &value, BinomialNode *right, BinomialNode *child) {
        mValue = value;
        mRight = right;
        mChild = child;
    }
};


template<typename T>
class BinomialHeap {
public:
    BinomialHeap();

    ~BinomialHeap();

    BinomialHeap(const BinomialHeap &);

    BinomialHeap &operator=(const BinomialHeap &);

    void push(const T &);

    const T &top() const;

    void pop();

    void merge(BinomialHeap &other);

    size_t size() const;

    bool empty() const;

    void swap(BinomialHeap &other);

    void print(){
        for (auto &root:mHeap){
            std::cout << "( ";
            print(root);
            std::cout << " )";
        }
    }


private:
    std::vector<BinomialNode<T> *> mHeap;
    size_t mSize;

    void print(BinomialNode<T> *root){
        std::cout << root->mValue << " ";

    }
};

template<typename T>
bool CompareNodesByValue(const BinomialNode<T> *lhs,
                         const BinomialNode<T> *rhs) {
    if (!lhs || !rhs)
        return !lhs < !rhs;
    return lhs->mValue < rhs->mValue;
}

template<typename T>
BinomialNode<T> *MergeTrees(BinomialNode<T> *lhs, BinomialNode<T> *rhs) {
    if (rhs->mValue < lhs->mValue)
        std::swap(lhs, rhs);
    rhs->mRight = lhs->mChild;
    lhs->mChild = rhs;
    return lhs;
}


template<typename T>
void BinomialHeapMerge(std::vector<BinomialNode<T> *> &lhs,
                       std::vector<BinomialNode<T> *> &rhs) {
    std::vector<BinomialNode<T> *> result;
    const size_t maxOrder = std::max(lhs.size(), rhs.size());
    lhs.resize(maxOrder);
    rhs.resize(maxOrder);
    BinomialNode<T> *carry = nullptr;

    for (size_t order = 0; order < maxOrder; ++order) {
        std::vector<BinomialNode<T> *> trees;
        if (carry)
            trees.push_back(carry);
        if (lhs[order])
            trees.push_back(lhs[order]);
        if (rhs[order])
            trees.push_back(rhs[order]);

        if (trees.empty()) {
            result.push_back(nullptr);
            carry = nullptr;
        } else if (trees.size() == 1) {
            result.push_back(trees[0]);
            carry = nullptr;
        } else if (trees.size() == 2) {
            result.push_back(nullptr);
            carry = MergeTrees(trees[0], trees[1]);
        } else {
            result.push_back(trees[0]);
            carry = MergeTrees(trees[1], trees[2]);
        }
    }

    if (carry)
        result.push_back(carry);
    rhs.clear();
    lhs = result;
}


template<typename T>
void DestroyBinomialTree(BinomialNode<T> *root) {
    if (!root) return;
    DestroyBinomialTree(root->mRight);
    DestroyBinomialTree(root->mChild);
    delete root;
}

template<typename T>
BinomialNode<T> *CloneBinomialTree(BinomialNode<T> *root) {
    if (!root) return nullptr;
    return new BinomialNode<T>(root->mValue,
                               CloneBinomialTree(root->mRight),
                               CloneBinomialTree(root->mChild));
}

template<typename T>
BinomialHeap<T>::BinomialHeap() {
    mSize = 0;
}

template<typename T>
BinomialHeap<T>::~BinomialHeap() {
    std::for_each(mHeap.begin(), mHeap.end(), DestroyBinomialTree<T>);
}

template<typename T>
BinomialHeap<T>::BinomialHeap(const BinomialHeap &other) {
    mSize = other.mSize;
    for (size_t i = 0; i < mSize; ++i)
        mHeap.push_back(CloneBinomialTree(other.mHeap[i]));
}

template<typename T>
BinomialHeap<T> &BinomialHeap<T>::operator=(const BinomialHeap<T> &other) {
    BinomialHeap copy(other);
    swap(copy);
    return *this;
}

template<typename T>
void BinomialHeap<T>::swap(BinomialHeap &other) {
    mHeap.swap(other.mHeap);
    std::swap(mSize, other.mSize);
}

template<typename T>
size_t BinomialHeap<T>::size() const {
    return mSize;
}

template<typename T>
bool BinomialHeap<T>::empty() const {
    return size() == 0;
}

template<typename T>
const T &BinomialHeap<T>::top() const {
    return (*std::min_element(mHeap.begin(), mHeap.end(),
                              CompareNodesByValue<T>))->mValue;
}

template<typename T>
void BinomialHeap<T>::push(const T &value) {
    std::vector<BinomialNode<T> *> singleton;
    singleton.push_back(new BinomialNode<T>(value, nullptr, nullptr));
    BinomialHeapMerge(mHeap, singleton);
    mSize++;
}

template<typename T>
void BinomialHeap<T>::merge(BinomialHeap &other) {
    BinomialHeapMerge(mHeap, other.mHeap);
    mSize += other.mSize;
    other.mSize = 0;
}

template<typename T>
void BinomialHeap<T>::pop() {

    typename std::vector<BinomialNode<T> *>::iterator minElem =
            std::min_element(mHeap.begin(), mHeap.end(),
                             CompareNodesByValue<T>);
    std::vector<BinomialNode<T> *> children;
    for (BinomialNode<T> *child = (*minElem)->mChild;
         child != nullptr; child = child->mRight)
        children.push_back(child);

    std::reverse(children.begin(), children.end());

    for (size_t i = 0; i < children.size(); ++i)
        children[i]->mRight = nullptr;
    delete *minElem;
    *minElem = nullptr;
    if (minElem == mHeap.end() - 1)
        mHeap.pop_back();
    BinomialHeapMerge(mHeap, children);
    mSize--;
}

#include <iostream>

int main() {
    BinomialHeap<int> bh;
    bh.push(5);
    bh.push(8);
    bh.push(4);
    bh.push(2);

    bh.print();

    std::cout << bh.top() << " ";
    bh.pop();
    std::cout << bh.top();

}
