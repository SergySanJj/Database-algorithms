//
// Created by sju on 04.02.19.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>

class Agency {
public:
    Agency(std::string _name) :
            name(std::move(_name)) {
        id = MAXID;
        MAXID++;
    }

private:
    std::string name;
    int id;

    static int MAXID;
};

class News {
public:
    News() {
        title = "";
        text = "";
        categoryId = -1;
    }

    News(std::string _title, std::string _text, int _Id) :
            title(std::move(_title)), text(std::move(_text)), categoryId(_Id) {}

    std::string getTitle() const { return title; }

    void print() {
        std::cout << "Title: " << title << "\n" << "Text: " << text << std::endl;
    }

private:
    std::string title;
    std::string text;
    int categoryId;
    int agencyId;
};

class Category {
public:
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



