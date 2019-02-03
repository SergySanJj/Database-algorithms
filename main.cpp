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


int main() {
    HashTable ht({"Vogue", "New York Times", "Forbes", "Special"});
    cout << ht.exists("Vogue") << " " << ht.exists("Fox");
    return 0;
}