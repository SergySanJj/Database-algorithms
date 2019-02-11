#include <iostream>

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

template<typename T>
class Node {
public:
    Node(T _data);

    ~Node() = default;

    template<typename DAT, typename F> friend class OrderStatisticsTree;

private:
    T data;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    bool color = false; // false - red, true - black
};

template<typename T, typename F>
class OrderStatisticsTree {
public:
private:
    Node<T> *Root = nullptr;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}