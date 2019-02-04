//
// Created by Sergey on 03.02.2019.
//

#include "HashTable.h"


bool HashTable::isPrime(unsigned int val) {
    if (val == 1 || val == 2 || val == 3)
        return true;
    int sqr = static_cast<int>(std::sqrt(val) + 1);
    for (int i = 2; i < sqr + 1; i++) {
        if (val % i == 0)
            return false;
    }
    return true;
}

unsigned int HashTable::nextPrime(unsigned int val) {
    unsigned int i = val + 1;
    while (!HashTable::isPrime(i))
        i++;
    return i;
}

unsigned long Statistics::totalHashChange = 0;
int Statistics::totalBuckets = 0;
int Statistics::totalBucketElements = 0;
int Statistics::elements = 0;