//
//  json_utils.hpp
//  finalproject-jsondisplay
//
//  Created by Daniela Zieba on 11/29/18.
//
//

#ifndef json_utils_hpp
#define json_utils_hpp

#include <stdio.h>

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

string getJSONFromFile(string file_name); // given file name, returns string of JSON

Document getDocumentFromString(string file_name); // given file name, returns rapidjson Document representing JSON

#endif /* json_utils_hpp */
