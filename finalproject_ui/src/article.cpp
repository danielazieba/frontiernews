#include <string>
#include <vector>
#include "article.hpp"

using namespace article;

Article::Article() {
    source = "";
    title = "";
    link = "";
    content = "";
    display.resize(0);
    tags.resize(0);
    date = Date();
}
Article::Article(string new_source, string new_title, string new_link, string new_content, string new_date) {
    source = new_source;
    title = new_title;
    link = new_link;
    content = new_content;
    date = Date(new_date);
    initDisplay();
    tagArticle();
}

string Article::getSource() {
    return source;
}

void Article::setSource(string new_source) {
    source = new_source;
}

string Article::getTitle() {
    return title;
}
void Article::setTitle(string new_title) {
    title = new_title;
}

string Article::getLink() {
    return link;
}
void Article::setLink(string new_link) {
    link = new_link;
}

string Article::getContent() {
    return content;
}
void Article::setContent(string new_content) {
    content = new_content;
}

vector<string> Article::getDisplay() {
    return display;
}
void Article::setDisplay(vector<string> new_display){
    display = new_display;
}

vector<Tag> Article::getTags() {
    return tags;
}
void Article::setTags(vector<Tag> new_tags){
    tags = new_tags;
}

Date Article::getDate(){
    return date;
}

void Article::setDate(Date new_date){
    date = new_date;
}

bool Article::hasTag(Tag tag){
    for (int i = 0; i < tags.size(); i++) {
        if (tags[i] == tag) {
            return true;
        }
    }

    return false;
}

void Article::initDisplay(){
    /*
    take content string and create vector of strings to represent each word in article
    */
   string curr = "";
   char curr_char;

   for (int i = 0; i < content.size(); i++) {
       curr_char = content[i];

       if (curr_char != ' ') {
           curr += curr_char;

           if (curr_char == '.') {
               display.push_back(curr);
               curr = "";
           }
       } else {
           display.push_back(curr);
           curr = "";
       }
   }
}

void Article::tagArticle(){
    /*
    search through display form 
    check for tags
    if keywords are found, tag article appropriately
    */
   tags.resize(0);

   string curr;
   for (int i = 0; i < display.size(); i++) {
       curr = display[i];
       transform(curr.begin(), curr.end(), curr.begin(), ::tolower);

       if (curr.find("research") != std::string::npos && !hasTag(RESEARCH)) {
           tags.push_back(RESEARCH);
       }
   }
}