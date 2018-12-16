//
//  json_utils.cpp
//  finalproject-jsondisplay
//
//  Created by Daniela Zieba on 11/29/18.
//
//

#include "json_utils.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace rapidjson;

string getJSONFromFile(string file_name) {
    
    string json_output;
    
    ifstream json_stream("/Users/danielazieba/Desktop/finalproject_ui/src/" + file_name);
    
    if (json_stream.is_open()) {
        string curr_line;
        
        while (getline(json_stream, curr_line)) {
            json_output += curr_line;
        }
        json_stream.close();
    } else {
        cout << "JSON file not found.";
    }
    
    return json_output;
}

Document getDocumentFromString(string file_name) {
    string file_json = getJSONFromFile(file_name);
    
    char file_json_arr[file_json.length() + 1];
    strcpy(file_json_arr, file_json.c_str());
    
    Document json_articles;
    json_articles.Parse(file_json_arr);
    return json_articles;
}

vector<article::Article::Article> articleListFromJSON(string file_name){
    vector<article::Article::Article> articles;
    Document json_tree = getDocumentFromString(file_name);
    
    /*
     assert that document is array and specific elements are strings
     (errors are caught here if this does not follow expected JSON format)
     */
    
    assert(json_tree.IsObject());
    assert(json_tree.HasMember("articles"));
    assert(json_tree["articles"].IsArray());
    
    string curr_date;
    string curr_source;
    string curr_title;
    string curr_content;
    string curr_link;
    
    for (SizeType i = 0; i < json_tree["articles"].Size(); i++){ // Uses SizeType instead of size_t
        curr_title = json_tree["articles"][i]["title"].GetString();
        curr_source = json_tree["articles"][i]["source"].GetString();
        curr_date = json_tree["articles"][i]["date"].GetString();
        curr_content = json_tree["articles"][i]["content"].GetString();
        curr_link =json_tree["articles"][i]["link"].GetString();
        articles.push_back(article::Article::Article(curr_source, curr_title, curr_link, curr_content, curr_date));
    }
    
    return articles;
}

vector<vector<article::Article::Article>> multipleListsFromJSON(vector<string> file_names){
    vector<vector<article::Article::Article>> article_lists;
    
    for (int i = 0; i < file_names.size(); i++){
        article_lists.push_back(articleListFromJSON(file_names[i]));
    }
    
    return article_lists;
}
