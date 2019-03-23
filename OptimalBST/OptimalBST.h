//
// Created by sju on 18.03.19.
//

#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <queue>

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

void printm(int **m, int n) {

    for (int jj = 0; jj < n; ++jj) {
        for (int ii = 0; ii < n; ++ii) {
            std::cout << std::setprecision(2);
            std::cout << std::setw(10) << m[jj][ii] << ' ';
        }
        std::cout << '\n';
    }
}

template<typename KEY, typename DAT>
class Node {
public:
    Node(const KEY &_key, const DAT &_data) : key(_key), data(_data) {}

    Node() = default;

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
               std::vector<int> &freq) {
        MAX = data.size()+2;
        prf.resize(MAX);

        dp.resize(MAX, std::vector<int>(MAX));
        opt.resize(MAX, std::vector<int>(MAX));

        matrix(freq, data.size());
        build(data, data.size());
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

    void printTree(int ident = 0) {
        displayNodeFancy(Root, 2);
    }

    void displayNodeFancy(Node<KEY, DAT> *node, int tabs) {
        if (node == nullptr)
            return;
        if (node->right != nullptr)
            displayNodeFancy(node->right, tabs + 4);
        else cout << endl;
        for (int i = 0; i < tabs; i++)
            cout << " ";
        cout << node->data.getTitle() << "(" << node->data.getViews() << ")";
        if (node->left != NULL)
            displayNodeFancy(node->left, tabs + 4);
        else cout << endl;

    }

private:
    Node<KEY, DAT> *Root;

    int MAX = 10;
    const static int INF = 1000000;

    std::vector<int> prf;
    std::vector<std::vector<int>> dp, opt;


    void matrix(const std::vector<int> &freq, int n) {
        auto sum = [this](int l, int r) {
            return prf[r] - prf[l - 1];
        };

        for (int i = 1; i <= n; ++i)
            prf[i] = prf[i - 1] + freq[i - 1];

        for (int len = 1; len <= n; ++len) {
            for (int start = 1; start <= n - len + 1; ++start) {
                int end = start + len - 1;
                dp[start][end] = INF;
                for (int mid = start; mid <= end; ++mid) {
                    int upd = dp[start][mid - 1] + dp[mid + 1][end] + sum(start, mid - 1) + sum(mid + 1, end);
                    if (upd < dp[start][end]) {
                        dp[start][end] = min(dp[start][end], upd);
                        opt[start][end] = mid;
                    }
                }
            }
        }
        print(dp);
        std::cout << "***\n";
        print(opt);

    }

    void build(std::vector<std::pair<KEY, DAT> > &data, int n) {
        cout.precision(4);
        cout.setf(ios::fixed);
        queue<pair<pair<int, int>, int> > que;
        std::vector<std::pair<KEY, DAT>> res(data.size());
        que.push({{1, n}, 0});
        int cnt = 0;
        while (!que.empty()) {
            int l = que.front().first.first, r = que.front().first.second, h = que.front().second;
            que.pop();
            if (l <= r) {
                int now = opt[l][r];
                DAT item = data[now - 1].second;

                cout << setw(25) << item.getTitle() << setw(7) << item.getViews()/*/sum*/ << setw(3) << h
                     << setw(7) << item.getViews()/*/sum*/* h << setw(10) << dp[l][r] << endl;

                res[cnt].first = data[now - 1].first;
                res[cnt].second = data[now - 1].second;

                que.push({{l, now - 1}, h + 1});
                que.push({{now + 1, r}, h + 1});

                cnt++;
            }
        }
        create(res);
    }

    void create(std::vector<std::pair<KEY, DAT>> &data) {
        Root = new Node<KEY, DAT>(data[0].first, data[0].second);
        for (int i = 1; i < data.size(); i++) {
            insertBinary(data[i]);
        }
    }

    void insertBinary(std::pair<KEY, DAT> value) {
        if (Root == nullptr)
            Root = new Node<KEY, DAT>(value.first, value.second);
        auto curr = Root;
        auto prev = Root;
        while (curr != nullptr) {
            prev = curr;
            if (value.first <= curr->key) {
                curr = curr->left;
            } else
                curr = curr->right;
        }
        if (value.first <= prev->key)
            prev->left = new Node<KEY, DAT>(value.first, value.second);
        else
            prev->right = new Node<KEY, DAT>(value.first, value.second);
    }
};