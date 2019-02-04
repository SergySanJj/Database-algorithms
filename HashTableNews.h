//
// Created by Sergey on 03.02.2019.
//

#pragma once

#include <vector>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <string>
#include <iostream>

#include "HashTable.h"
#include "Agency.h"

using namespace std;

class HashTableNews {
public:
    HashTableNews(const vector<News> &_values) {
        Statistics::elements = _values.size();

        srand(time(NULL));
        prime = HashTableNews::nextPrime(_values.size() + 1);
        bool finished = false;
        while (!finished) {

            hashTable.clear();
            hashTable.resize(prime + 1);
            vector<vector<News> > tmpVec(prime + 1);
            a = rand() % 10001 + 3;
            b = rand() % 10001 + 3;
            for (auto &val:_values) {
                tmpVec[firstHash(val.getTitle())].push_back(val);
                Statistics::totalBucketElements++;
            }
            for (int i = 0; i < prime; i++) {
                if (!hashTable[i].fill(tmpVec[i])) {
                    finished = false;
                    //cout << "FIRST\n";
                    break;
                }
                finished = true;
            }
        }
    }

    ~HashTableNews() = default;

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
        return size_t((a * hash<string>()(str) + b) % prime);
    }


    class Node {
    public:
        Node() {}

        bool fill(const vector<News> _values) {
            if (_values.empty())
                return true;
            else
                Statistics::totalBuckets++;

            int cntTry = 0;
            int lim = _values.size() * 100;

            srand(time(NULL));
            m = HashTableNews::nextPrime(_values.size() * _values.size());
            values.resize(m);
            bool filled = false;
            while (!filled) {
                a = rand() % 10001 + 3;
                b = rand() % 10001 + 3;
                for (auto &str:values)
                    str = News();
                for (auto &val:_values) {
                    if (addValue(val))
                        filled = true;
                    else {
                        filled = false;
                        cntTry++;
                        Statistics::totalHashChange++;
                        //std::cout << _values.size() << " second\n" ;
                        break;
                    }
                }
                if (cntTry > lim)
                    return false;
            }
            ready = true;
            return true;
        }

        static unsigned int secondHash(const string &str, unsigned int mult, unsigned int adder, unsigned int prime) {
            return size_t((mult * hash<string>()(str) + adder) % prime);
        }

        unsigned int getMult() const { return a; }

        unsigned int getPrime() const { return m; }

        bool isReady() const { return ready; }

        bool addValue(const News &val) {
            unsigned int tmp = Node::secondHash(val.getTitle(), a, b, m);
            if (!values[tmp].getTitle().empty())
                return false;
            else {
                values[tmp] = val;
            }
            return true;
        }

        bool exists(const string &val) {
            unsigned int sHash = Node::secondHash(val, a, b, m);
            if (!values[sHash].getTitle().empty()) {
                if (values[sHash].getTitle() == val) {
                    values[sHash].print();
                    return true;
                }
                return false;
            } else
                return false;
        }

    private:
        unsigned int a, b, m;
        bool ready = false;
        vector<News> values;
    };

    vector<Node> hashTable;
    unsigned int a, b, prime;
};

