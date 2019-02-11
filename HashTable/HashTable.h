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

using namespace std;

class Statistics {
public:
    static int elements;
    static unsigned long totalHashChange;
    static int totalBuckets;
    static int totalBucketElements;
    static int maxBucket;
    static int mas[500];

    static void printStat() {
        cout << "Total elements - " << elements << "\n";
        cout << "Total Hash Changes - " << totalHashChange << "\n";
        cout << "Max bucket size - " << maxBucket << endl;
        cout << "dist: " << endl;
        for (int i=0;i<maxBucket+1;i++)
        {
            cout << "(" << i << ", "  << mas[i] << ") ";
        }
    }

    static void clear()
    {
        elements = 0;
        totalHashChange = 0;
        totalBuckets = 0;
        totalBucketElements = 0;
        maxBucket = -1;
    }
};


class HashTable {
public:
    HashTable(const vector<string> &_values) {
        Statistics::elements = _values.size();
        capacity = _values.size()+1;

        srand(time(NULL));
        prime = HashTable::nextPrime(_values.size() + 1);
        bool finished = false;
        while (!finished) {

            hashTable.clear();
            hashTable.resize(prime + 1);
            vector<vector<string> > tmpVec(prime + 1);
            a = rand() % 10000 + 3;
            b = rand() % 10000 + 3;
            for (auto &val:_values) {
                tmpVec[firstHash(val)].push_back(val);
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

    ~HashTable() = default;

    void findStatistics()
    {
        int maxBucket = -1;
        for (int i=0;i<hashTable.size();i++)
        {

            if (maxBucket<hashTable[i].getBucketSize())
            {
                maxBucket = hashTable[i].getBucketSize();
            }
        }
        Statistics::maxBucket = maxBucket;
        for (int i=0;i<hashTable.size();i++)
        {
            Statistics::mas[hashTable[i].getBucketSize()]++;
        }

    }

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
        return size_t(((a * hash<string>()(str) + b) % prime)%capacity);
    }


    class Node {
    public:
        Node() {}

        int getBucketSize() const { return values.size(); }

        bool fill(const vector<string> _values) {
            if (_values.empty())
                return true;
            else
                Statistics::totalBuckets++;

            int cntTry = 0;
            int lim = _values.size() * 100;

            srand(time(NULL));
            m = HashTable::nextPrime(_values.size() * _values.size());
            values.resize(m, "");
            bool filled = false;
            while (!filled) {
                a = rand() % 10000 + 3;
                b = rand() % 10000 + 3;
                for (auto &str:values)
                    str = "";
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

        bool addValue(const string &val) {
            unsigned int tmp = Node::secondHash(val, a, b, m);
            if (!values[tmp].empty())
                return false;
            else {
                values[tmp] = val;
            }
            return true;
        }

        bool exists(const string &val) {
            unsigned int sHash = Node::secondHash(val, a, b, m);
            if (!values[sHash].empty()) {
                return (values[sHash] == val);
            } else
                return false;
        }

    private:
        unsigned int a, b, m;
        bool ready = false;
        vector<string> values;
    };

    vector<Node> hashTable;
    unsigned int a, b, prime, capacity;
};

