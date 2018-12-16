#ifndef FEED_H
#define FEED_H

#include "article.hpp"
#include "date.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace article;

class Feed 
{
    private:
        vector<Article> articles; // stores all articles given
        vector<string> universities; // stores total universities
        vector<Tag> tags; // stores total tags
        Date max_date;
        Date min_date;
        vector<Article> feed; // stores only current feed generated from article base

    public:
        Feed();
        Feed(vector<Article> new_articles);

        vector<Article> getArticles();
        void setArticles(vector<Article> new_articles);
        void setArticles(vector<vector<Article>> article_list);

        vector<string> getTitles();

        vector<string> getUnis();
        void setUnis(vector<string> new_unis);

        vector<Tag> getTags();
        void setTags(vector<Tag> new_tags);

        vector<Date> getDates(vector<Article> article_list);

        Date getMaxDate();
        void setMaxDate(Date new_max_date);

        Date getMinDate();
        void setMinDate(Date new_min_date);

        vector<Article> getFeed();
        void setFeed(vector<Article> new_feed);

        bool tagInList(Tag pos_tag, vector<Tag> tag_list);
        bool tagsInList(Article article, vector<Tag> tag_list);
        bool uniInList(string pos_uni, vector<string> unis);
        void addArticle(Article article);
        void updateUnis(); // updates university list
        void updateTags(); // updates tag list
        void updateDateBounds(); // updates min, max dates

        vector<Article> sortLexigraph(vector<Article> unsorted_articles); // sorts feed articles lexigraphically
        vector<Article> sortChrono(vector<Article> unsorted_articles); // sorts feed articles by date

        void updateFeed();
        void updateFeed(vector<string> selected_unis);
        void updateFeed(vector<string> selected_unis, Date max_selected_date, Date min_selected_date);
        void updateFeed(vector<string> selected_unis, vector<Tag> selected_tags, Date max_selected_date, Date min_selected_date);
};

#endif
