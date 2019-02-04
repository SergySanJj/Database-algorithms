/*
Вариант 6
Предметная область  Агентство новостей
Объекты  Категории новостей, Новости
Примечание  Новости  сгруппированы  по
категориям. У каждой категории
имеется множество новостей.
 */

#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "HashTable.h"

using namespace std;

class Agency {
public:
    Agency(std::string _name) :
            name(std::move(_name)) {}

private:
    std::string name;
};

class News {
    News(std::string _title, std::string _text, int _Id) :
            title(std::move(_title)), text(std::move(_text)), categoryId(_Id) {}

private:
    std::string title;
    std::string text;
    int categoryId;
};

class Category {
    Category(const std::string &_name) : name(_name) {
        id = MAX_ID;
        MAX_ID++;
    }

    std::string getName() { return name; }

private:
    int id;
    std::string name;

    static int MAX_ID;
};

bool checkExistance(const string &s, const vector<string> vec) {
    for (auto &str:vec) {
        if (s == str)
            return true;
    }
    return
            false;
}

std::string randomString(std::string::size_type length) {
    static auto &chrs = "0123456789"
                        "abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
        s += chrs[pick(rg)];

    return s;
}

vector<string> randomStrings(std::size_t cnt, int maxLen) {
    srand(time(NULL));
    vector<string> res(cnt, "");

    for (int i = 0; i < res.size(); i++) {
        string newS;
        while (checkExistance(newS, res)) {
            int len = rand() % maxLen + 1;
            newS = randomString(len);
        }
        res[i] = newS;
    }
    return res;
}

int main() {
    //HashTable ht({"Vogue", "New York Times", "Forbes", "Special"});
    auto generated = randomStrings(3000, 100);
    HashTable ht(generated);
    cout << ht.exists(generated[1]) << endl;

    Statistics::printStat();
    return 0;
}