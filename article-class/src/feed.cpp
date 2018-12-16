#include <string>
#include <vector>
#include <iostream>
#include "feed.hpp"

using namespace std;

Feed::Feed(){
    articles.resize(0);
    universities.resize(0);
    tags.resize(0);
    max_date = Date();
    min_date = Date();
    feed.resize(0);
}

Feed::Feed(vector<Article> new_articles){
    articles = new_articles;
    updateUnis();
    updateTags();
    updateDateBounds();
    updateFeed();
}

vector<Article> Feed::getArticles(){
    return articles;
}

void Feed::setArticles(vector<Article> new_articles){
    articles = new_articles;
    updateUnis();
    updateTags();
    updateFeed();
    updateDateBounds();
}

void Feed::setArticles(vector<vector<Article>> article_list){
    /*
    takes in vector of vectors to accomodate possibility of multiple article vectors
    this will allow for articles from multiple sources to be joined
    */
   vector<Article> curr;

   for (int i = 0; i < article_list.size(); i++) {
       curr = article_list[i];

       for (int list_i = 0; list_i < curr.size(); list_i++){
           articles.push_back(curr[list_i]);
       }
   }

   updateUnis();
   updateTags();
   updateFeed();
   updateDateBounds();
}

vector<string> Feed::getTitles() {
    vector<string> titles;

    for (int index = 0; index < articles.size(); index++){
        titles.push_back(articles[index].getTitle());
    }

    return titles;
}

vector<string> Feed::getUnis() {
    return universities;
}

void Feed::setUnis(vector<string> new_unis){
    universities = new_unis;
}

vector<Tag> Feed::getTags(){
    return tags;
}

 void Feed::setTags(vector<Tag> new_tags){
    tags = new_tags;
}

Date Feed::getMaxDate(){
    return max_date;
}

void Feed::setMaxDate(Date new_max_date){
    max_date = new_max_date;
}

Date Feed::getMinDate(){
    return min_date;
}

void Feed::setMinDate(Date new_min_date){
    min_date = new_min_date;
}

vector<Date> Feed::getDates(vector<Article> article_list){
    vector<Date> dates;

    for (Article curr: article_list){
        dates.push_back(curr.getDate());
    }

    return dates;
}

vector<Article> Feed::getFeed(){
    return feed;
}

void Feed::setFeed(vector<Article> new_feed){
    feed = new_feed;
}

void Feed::addArticle(Article article){
    articles.push_back(article);
    updateUnis();
    updateTags();
    updateFeed();
}

bool Feed::uniInList(string pos_uni, vector<string> unis){
    for(int i = 0; i < unis.size(); i++) {
        if(pos_uni == unis[i]) {
            return true;
        }
    }

    return false;
}

bool Feed::tagInList(Tag pos_tag, vector<Tag> tag_list){
    for (int i = 0; i < tag_list.size(); i++) {
        if (pos_tag == tag_list[i]){
            return true;
        }
    }

    return false;
}

bool Feed::tagsInList(Article article, vector<Tag> tag_list){
    vector<Tag> article_tags = article.getTags();

    for (int i = 0; i < article_tags.size(); i++){
        if (!tagInList(article_tags[i], tag_list)) {
            return false;
        }
    }

    return true;
}

void Feed::updateUnis(){
    /*
    search through articles
    check if source is unique
    add if so
    */
   universities.resize(0);

   for (Article curr: articles) {
       if (!uniInList(curr.getSource(), universities)) {
           universities.push_back(curr.getSource());
       }
   }
}

void Feed::updateTags(){
    /*
    search through articles
    check if tag is unique
    add if so
    */
   tags.resize(0);

   vector<Tag> curr_tags;
   for (Article curr: articles) {
       curr_tags = curr.getTags();

       for (int i = 0; i < curr_tags.size(); i++) {
           if (!tagInList(curr_tags[i], tags)) {
               tags.push_back(curr_tags[i]);
           }
       }
   }
}

void Feed::updateDateBounds(){
    Date min;
    Date max;
    Date curr_date;

    if (articles.size() > 0) {
        min = articles[0].getDate();
        max = articles[0].getDate();

        for (Article curr: articles) {
            curr_date = curr.getDate();

            if (curr_date.compareDate(min) == 1) {
                min = curr_date;
            }

            if (curr_date.compareDate(max) == 0) {
                max = curr_date;
            }
        }
    }

    max_date = max;
    min_date = min;
}

vector<Article> Feed::sortLexigraph(vector<Article> unsorted_articles){
    vector<string> titles = getTitles();
    sort(titles.begin(), titles.end());

    vector<Article> new_articles;

    /*
    search through titles
        current title;
        search through unsorted
            when unsorted matches current title
            push back the article
    return that 
    */

   for (int i = 0; i < titles.size(); i++){
       
       for (int j = 0; j < unsorted_articles.size(); j++){
           if (unsorted_articles[j].getTitle() == titles[i]) {
               new_articles.push_back(unsorted_articles[j]);
           }
       }
   }

    return new_articles;
}

// sorting algorithm implementation based on the following website implementation:
// https://www.geeksforgeeks.org/insertion-sort/
vector<Article> Feed::sortChrono(vector<Article> unsorted_articles){
    vector<string> titles = getTitles();
    vector<Date> dates = getDates(unsorted_articles);
    vector<Article> sorted_articles;

    int i, j;
    Date key; 
    for (i = 1; i < dates.size(); i++)
    { 
       key = dates[i]; 
       j = i-1; 
  
       /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
       while (j >= 0 && (dates[j].compareDate(key) == 1))
       { 
           dates[j+1] = dates[j]; 
           j = j-1; 
       } 
       dates[j+1] = key; 
   } 

    return sorted_articles;
}

void Feed::updateFeed(){
    feed.resize(0);
    feed = sortLexigraph(articles);
}

void Feed::updateFeed(vector<string> selected_unis, vector<Tag> selected_tags, Date max_selected_date, Date min_selected_date){
    /*
    search through general article list
    add all articles of specified university and tag to current feed
    sort lexigraphically and then chronologically
    */
   vector<Article> new_feed;
   bool valid_source;
   bool valid_tag;
   bool valid_date;

   for (Article curr: articles){
       /*
       if this article's tags and universities are in the lists
       */
      valid_source = (uniInList(curr.getSource(), selected_unis));
      valid_tag = (tagsInList(curr, selected_tags));
      valid_date = ((curr.getDate().compareDate(max_selected_date) != 0) && (curr.getDate().compareDate(min_selected_date) != 1));

      if (valid_source && valid_tag && valid_date) {
          new_feed.push_back(curr);
      }
   }

   feed = sortChrono(sortLexigraph(new_feed));
}

void Feed::updateFeed(vector<string> selected_unis){
    vector<Article> new_feed;
    bool valid_source;
    
    for (Article curr: articles){
        /*
         if this article's university is in the list
         */
        valid_source = (uniInList(curr.getSource(), selected_unis));
        
        if (valid_source) {
            new_feed.push_back(curr);
        }
    }
    
    feed = new_feed;
}

void Feed::updateFeed(vector<string> selected_unis, Date max_selected_date, Date min_selected_date){
    vector<Article> new_feed;
    bool valid_source;
    bool valid_date;
    
    for (Article curr: articles){
        /*
         if this article's university, date are possible
         */
        valid_source = (uniInList(curr.getSource(), selected_unis));
        valid_date = ((curr.getDate().compareDate(max_selected_date) != 0) && (curr.getDate().compareDate(min_selected_date) != 1));
        
        if (valid_source && valid_date) {
            new_feed.push_back(curr);
        }
    }
    
    feed = new_feed;
}
