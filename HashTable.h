//
// Created by Sergey on 03.02.2019.
//

#pragma once

#include <vector>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <string>

using namespace std;

class HashTable {
public:
    HashTable(const vector<string> &_values) {
        srand(time(NULL));
        prime = HashTable::nextPrime(_values.size() + 1);
        hashTable.resize(prime+1);
        vector<vector<string> > tmpVec(prime+1);
        a = HashTable::nextPrime(rand() % 10000 + 3);
        for (auto &val:_values) {
            tmpVec[firstHash(val)].push_back(val);
        }
        for (int i = 0; i < prime; i++) {
            hashTable[i].fill(tmpVec[i]);
        }
    }

    ~HashTable() = default;

    bool exists(const string &val) {
        unsigned int fHash = firstHash(val);
        if (hashTable[fHash].isReady()) {
            return (hashTable[fHash].exists(val));
        } else
            return false;
    }

private:
    static bool isPrime(unsigned int val);

    static unsigned int nextPrime(unsigned int val);

    unsigned int firstHash(const string &str) const {
        unsigned int hash = 0;
        int ml = a;
        for (char ch:str) {
            hash += (ch * ml) % prime;
            ml *= a;
        }
        return hash;
    }


    class Node {
    public:
        Node() {

        }

        void fill(const vector<string> _values) {
            srand(time(NULL));
            m = _values.size() * _values.size();
            values.resize(m, "");
            bool filled = false;
            while (!filled) {
                a = HashTable::nextPrime(rand() % 10000 + 3);
                for (auto &str:values)
                    str = "";
                for (auto &val:_values) {
                    if (addValue(val))
                        filled = true;
                    else {
                        filled = false;
                        break;
                    }
                }
            }
            ready = true;
        }

        static unsigned int secondHash(const string &str, unsigned int mult, unsigned int prime) {
            unsigned int hash = 0;
            int ml = mult;
            for (char ch:str) {
                hash += (ch * (ml + 1)) % prime;
                ml *= mult;
            }
            return hash;
        }

        unsigned int getMult() const { return a; }

        unsigned int getPrime() const { return m; }

        bool isReady() const { return ready; }

        bool addValue(const string &val) {
            unsigned int tmp = Node::secondHash(val, a, m);
            if (values[tmp].empty())
                return false;
            else
                values[tmp] = val;
            return true;
        }

        bool exists(const string &val) {
            return (!values[Node::secondHash(val, a, m)].empty());
        }

    private:
        unsigned int a, m;
        bool ready = false;
        vector<string> values;
    };

    vector<Node> hashTable;
    unsigned int a, prime;
};

