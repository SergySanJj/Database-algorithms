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
#include "HashTableNews.h"
#include "Agency.h"

using namespace std;


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
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ       ";

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

vector<News> randomNews(std::size_t cnt, int maxLenName, int maxLenText)
{
    srand(time(NULL));
    vector<News> res;
    auto names = randomStrings(cnt,maxLenName);
    auto texts = randomStrings(cnt,maxLenText);
    for (int i=0;i<cnt;i++)
    {
        News news(names[i],texts[i],i);
        res.push_back(news);
    }
    return res;
}

int main() {
    //HashTable ht({"Vogue", "New York Times", "Forbes", "Special"});
    auto generated = randomStrings(10000, 100);
    auto rndNews = randomNews(300,30,200);


    HashTable ht(generated);
    cout << ht.exists(generated[1]) << " " << ht.exists("---") << endl;
    ht.findStatistics();
    Statistics::printStat();
    //cout << "\n\n NEWS \n\n";

    //Statistics::clear();

    //HashTableNews newsTable(rndNews);
    //cout << newsTable.exists(rndNews[1].getTitle()) << " " << newsTable.exists("---") << endl;
    //Statistics::printStat();
    return 0;
}