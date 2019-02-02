#include <utility>
/*
Вариант 6
Предметная область  Агентство новостей
Объекты  Категории новостей, Новости
Примечание  Новости  сгруппированы  по
категориям. У каждой категории
имеется множество новостей.
 */

#include <iostream>

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

/// Hasher ///

class Hash {
    static int universalHash(int a, int b, int p, int m, int x) {
        int hash = ((a * x + b) % p) % m;
        return hash;
    }
};

template<typename T>
class HashTable {
    HashTable<T>(const T[]);

    bool exists(const T &val);


};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}