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
    
    ifstream json_stream("/Users/danielazieba/Desktop/finalproject-jsondisplay/src/" + file_name);
    
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
