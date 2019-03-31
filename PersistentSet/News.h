//
// Created by Sergey on 17.02.2019.
//

#ifndef ORDERSTATISTICSTREE_NEWS_H
#define ORDERSTATISTICSTREE_NEWS_H

#include <string>
#include <iostream>
#include <fstream>

class News {
public:
    News() {
        title = "";
        text = "";
        categoryId = -1;
        agencyId = -1;
        views = 0;
    }

    News(std::string _title, std::string _text, int _Id, int _arencyId, int _views) :
            title(std::move(_title)), text(std::move(_text)), categoryId(_Id), agencyId(_arencyId), views(_views) {}

    std::string getTitle() const { return title; }

    int getViews() const { return views; }

    void print() {
        std::cout << "Title: " << title << "\n" << "Text: " << text << '\n' << "Views: " << views << std::endl;
    }

    void print(std::ofstream &fout) {
        fout << title << "\n" << text << '\n' << categoryId << '\n' << agencyId << '\n' << views << '\n';
    }

    static int cmpVIEWS(News &a, News &b) {
        if (a.views == b.views)
            return 1;
        return (a.views < b.views) ? 0 : 2;
    }

    static int cmpTITLE(News &a, News &b) {
        if (a.title == b.title)
            return 1;
        return (a.title < b.title) ? 0 : 2;
    }

private:
    std::string title;
    std::string text;
    int categoryId;
    int agencyId;
    int views;
};

std::ostream& operator<< (std::ostream &out, const News &news)
{
    out << news.getTitle();
    return out;
}

#endif //ORDERSTATISTICSTREE_NEWS_H
