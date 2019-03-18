#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>

#include <limits.h>


template<typename T>
using Matrix =  std::vector<std::vector<T>>;

using namespace std;

template<typename Grid>
void print(Grid &theGrid) {
    int x = theGrid.at(0).size();
    for (int jj = 0; jj < x; ++jj) {
        for (int ii = 0; ii < x; ++ii) {
            std::cout << std::setprecision(2);
            std::cout << std::setw(10) << theGrid.at(jj).at(ii) << ' ';
        }
        std::cout << '\n';
    }
}

template<typename KEY, typename DAT>
class Node {
public:
    Node(const KEY &_key, const DAT &_data) : key(_key), data(_data) {}

    KEY key;
    DAT data;
    Node *left = nullptr;
    Node *right = nullptr;
};

template<typename KEY, typename DAT>
class tmpNode {
public:
    tmpNode(Node<KEY, DAT> *_node, int _begin, int _end, int _r) : node(_node), begin(_begin),
                                                                                  end(_end),
                                                                                  r(_r) {}

    Node<KEY, DAT> *node;
    int begin, end, r;
};


template<typename KEY, typename DAT>
class OptimalBST {
public:
    OptimalBST() = delete;

    OptimalBST(std::vector<std::pair<KEY, DAT> > &data,
               std::vector<double> &freq) {
        auto root = makeMatrix(freq, data.size());

        int begin = 1;
        int end = root.size() - 1;
        int tmp_r;
        int r = this->build(root, data, begin, end);

        Root = new Node<KEY, DAT>(data[r - 1].first, data[r - 1].second);
        Node<KEY, DAT> *node;
        auto *tmp = new tmpNode<KEY, DAT>(Root, begin, end, r);

        std::stack<tmpNode<KEY, DAT> *> S;
        S.push(tmp);
        while (!S.empty()) {
            tmp = S.top();
            S.pop();
            node = tmp->node;
            begin = tmp->begin;
            end = tmp->end;
            r = tmp->r;
            delete tmp;
            if (begin > end || (r <= begin && r >= end))
                continue;
            if (r > begin && r <= end) {
                tmp_r = this->build(root, data, begin, r - 1);
                node->left = new Node<KEY, DAT>(data[tmp_r - 1].first, data[tmp_r - 1].second);
                tmp = new tmpNode<KEY, DAT>(node->left, begin, r - 1, tmp_r);
                S.push(tmp);
            }
            if (r >= begin && r < end) {
                tmp_r = this->build(root, data, r + 1, end);
                node->right = new Node<KEY, DAT>(data[tmp_r - 1].first, data[tmp_r - 1].second);
                tmp = new tmpNode<KEY, DAT>(node->right, r + 1, end, tmp_r);
                S.push(tmp);
            }
        }

    }

    bool exists(KEY key) {
        auto curr = Root;
        while (curr != nullptr) {
            if (key == curr->key)
                return true;
            if (curr->key > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return false;
    }

    Node<KEY,DAT>* getRoot() { return Root;}

private:
    Node<KEY, DAT> *Root;

    int build(const std::vector<std::vector<int>> &_root, const std::vector<std::pair<KEY, DAT>> &data,
                   int begin, int end) {
        int r = _root[begin][end];
        return r;
    }

    Matrix<int> makeMatrix(const std::vector<double> &freq, int n) {
        Matrix<double> e(n + 2, std::vector<double>(n + 2, 0));
        Matrix<double> w(n + 2, std::vector<double>(n + 2, 0));
        Matrix<int> root(n + 1, std::vector<int>(n + 1, 0));

        for (std::size_t i = 1; i <= n + 1; ++i) {
            e[i][i - 1] = freq[i - 1];
            w[i][i - 1] = freq[i - 1];
        }

        for (std::size_t l = 1; l <= n + 1; ++l) {
            for (unsigned i = 1; i <= n - l + 1; ++i) {
                std::size_t j = i + l - 1;
                e[i][j] = INT_MAX;
                w[i][j] = w[i][j - 1] + freq[j];
                for (unsigned r = i; r <= j; ++r) {
                    double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                    if (t < e[i][j]) {
                        e[i][j] = t;
                        root[i][j] = r;
                    }
                }
            }
        }

        std::cout << "expectation: " << e[1][n] << "\n";
        print(e);
        std::cout << "----------------------------------------------------------\n";
        print(root);
        std::cout << "----------------------------------------------------------\n";

        return root;
    }

};



int main() {
    std::vector<std::pair<int, int> > v = {std::make_pair(2, 1),
                                           std::make_pair(4, 2),
                                           std::make_pair(6, 3),
                                           std::make_pair(8, 4)};
    std::vector<double> freq = {0.1, 0.5, 0.1, 0.3};
    OptimalBST<int, int> t(v, freq);
    std::cout << "\n" << t.exists(2) << " " << t.exists(-1) << "\n";

    return 0;
}