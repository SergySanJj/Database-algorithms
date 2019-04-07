#include <iostream>
#include <vector>

template<typename KEY, typename DAT>
class Node {
public:
    bool isLeaf;
    Node<KEY, DAT> *parent;
    // brothers:
    Node<KEY, DAT> *right;
    Node<KEY, DAT> *left;

    std::vector<KEY> keys;
    std::vector<DAT *> data;
    std::vector<Node<KEY, DAT> *> children;


    int size() { return keys.size(); }

private:
};

template<typename KEY, typename DAT>
class BPlusTree {
public:
    BPlusTree() = delete;

    explicit BPlusTree(std::size_t _t) : t(_t) {}

    ~BPlusTree() = default;

    bool insert(KEY key, DAT data) {
        auto leaf = find_leaf(key);

    }

    {
        bool insert(T: BPlusTree, key: int, value: Info):
            leaf = find_key(T, key)
            if key ∈ leaf
            return false

            // Ищем позицию для нового ключа
            pos = 0
            while
                pos < leaf.key_num and leaf.key[pos] < key
                        ++
            pos

            // Вставляем ключ
            for
            i = leaf.key_num
            downto
            pos + 1
            leaf.key[i] = leaf.key[i - 1]
            leaf.pointers[i] = leaf.pointer[i - 1]
            leaf.key[pos] = key
            leaf.pointers[pos] = value
                    ++
            leaf.key_num

            if leaf.key_num == 2 * t              // t — степень дерева
            split(T, leaf)                   // Разбиваем узел
            return true
    }
private:
    std::size_t t = 2;
    Node<KEY, DAT> *Root = nullptr;

    Node<KEY, DAT> *find_leaf(const KEY &key) const {
        auto cur = Root;
        while (!cur->isLeaf) {
            for (int i = 0; i < cur->keys.size(); i++) {
                if (i == cur->keys.size() || key < cur->keys[i]) {
                    cur = cur->children[i];
                    break;
                }
            }
        }
        return cur;
    }
};


int main() {

    return 0;
}