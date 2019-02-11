//
// Created by Sergey on 03.02.2019.
//

#include "HashTableNews.h"

bool HashTableNews::isPrime(unsigned int val) {
    if (val == 1 || val == 2 || val == 3)
        return true;
    int sqr = static_cast<int>(std::sqrt(val) + 1);
    for (int i = 2; i < sqr + 1; i++) {
        if (val % i == 0)
            return false;
    }
    return true;
}

unsigned int HashTableNews::nextPrime(unsigned int val) {
    unsigned int i = val + 1;
    while (!HashTableNews::isPrime(i))
        i++;
    return i;
}
