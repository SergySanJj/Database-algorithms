#include <utility>

#include <utility>

//
// Created by isara on 13-Apr-19.
//

#ifndef BINOMIALHEAP_NEWS_H
#define BINOMIALHEAP_NEWS_H

#include <iostream>

class News {
public:
    News() : Views(-1), Title("default title"), Text("default text") {
        ID = -1;
    }

    News(int views, std::string title, std::string text) : Views(views),
                                                           Title(std::move(title)),
                                                           Text(std::move(text)) {
        ID = MAX_ID;
        MAX_ID++;
    }

    void print() const{
        std::cout << "Views: " << Views << "\nTitle: " << Title << "\nText: " << Text << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const News &news);

    friend bool operator==(const News &c1, const News &c2);

    friend bool operator<(const News &c1, const News &c2);

    friend bool operator<=(const News &c1, const News &c2);

    friend bool operator>(const News &c1, const News &c2);

    friend bool operator>=(const News &c1, const News &c2);

private:
    int ID;
    int Views;
    std::string Title;
    std::string Text;

    static int MAX_ID;
};

int News::MAX_ID = 0;

std::ostream &operator<<(std::ostream &out, const News &news) {
    out << news.Views;

    return out;
}

bool operator==(const News &c1, const News &c2) {
    return (c1.Views == c2.Views);
}

bool operator<(const News &c1, const News &c2) {
    return (c1.Views < c2.Views);
}

bool operator<=(const News &c1, const News &c2) {
    return (c1.Views <= c2.Views);
}

bool operator>(const News &c1, const News &c2) {
    return (c1.Views > c2.Views);
}

bool operator>=(const News &c1, const News &c2) {
    return (c1.Views >= c2.Views);
}

#endif //BINOMIALHEAP_NEWS_H
