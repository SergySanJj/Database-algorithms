//
// Created by Sergey on 17.02.2019.
//

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

#include "words.h"
#include "random.hpp"
#include "News.h"

#ifndef ORDERSTATISTICSTREE_GENERATORS_H
#define ORDERSTATISTICSTREE_GENERATORS_H


using Random = effolkronium::random_static;


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


std::string getRandomText(int wordCount) {
    std::size_t sz = words.size();
    std::string res = "";

    for (int i = 0; i < wordCount; i++) {
        res += words[Random::get(0, (int) sz - 1)] + " ";
    }
    return res;
}

void textualize(std::string &s) {
    if (!s.empty())
        s[0] = static_cast<char>(toupper(s[0]));
}

News createRandomNews() {
    std::string title = getRandomText(Random::get(3, 10));
    textualize(title);
    std::string text = getRandomText(Random::get(10, 30));
    textualize(text);
    text[text.size() - 1] = '.';
    int categoryId = Random::get(1, 10);
    int agencyId = Random::get(1, 40);
    int views = Random::get(100, 3000);

    return News(title, text, categoryId, agencyId, views);
}

void generateNewsFile(int n) {
    std::ofstream fout("news.txt");
    fout << n << '\n';
    for (int i = 0; i < n; i++) {
        createRandomNews().print(fout);
    }
}

std::vector<News> getNewsFromFile(const std::string &name) {
    std::vector<News> res;
    std::ifstream fin(name);
    std::string buff;
    int n;
    std::getline(fin, buff);
    n = std::stoi(buff);
    std::string title;
    std::string text;
    int categoryId;
    int agencyId;
    int views;

    for (int i = 0; i < n; i++) {
        std::getline(fin, title);
        std::getline(fin, text);

        std::getline(fin, buff);
        categoryId = std::stoi(buff);

        std::getline(fin, buff);
        agencyId = std::stoi(buff);

        std::getline(fin, buff);
        views = std::stoi(buff);
        News tmp(title, text, categoryId, agencyId, views);
        res.push_back(tmp);
    }
    return res;
}

#endif //ORDERSTATISTICSTREE_GENERATORS_H
