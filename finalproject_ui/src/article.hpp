#ifndef ARTICLE_H
#define ARTICLE_H

#include "date.hpp"
#include <string>
#include <vector>

using namespace std;

namespace article {

    enum Tag {
        RESEARCH,
        AI,
        ML,
        HCI
    };

    class Article
    {
    private:
        string source;
        string title;
        string link;
        string content;
        Date date;
        vector<string> display;
        vector<Tag> tags;

    public:
        Article();
        Article(string new_source, string new_title, string new_link, string new_content, string new_date);

        string getSource();
        void setSource(string new_source);

        string getTitle();
        void setTitle(string new_title);

        string getLink();
        void setLink(string new_link);

        string getContent();
        void setContent(string new_content);

        vector<string> getDisplay();
        void setDisplay(vector<string> new_display);

        Date getDate();
        void setDate(Date new_date);

        vector<Tag> getTags();
        void setTags(vector<Tag> new_tags);

        bool hasTag(Tag tag);

        void initDisplay();

        void tagArticle();
    };
}

#endif