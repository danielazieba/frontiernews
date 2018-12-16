#functions relating to taking parsed website data and converting it to JSON
#used as reference for this file: https://stackabuse.com/reading-and-writing-json-to-a-file-in-python/

import json
from mit_scrape import *
from bs4 import BeautifulSoup

def mit_to_json(articles, timestamps):
    resulting_json = {}
    resulting_json['articles'] = []

    for index in range(len(articles)):
        resulting_json['articles'].append(
            {
                'source': "MIT",
                'title': articles[index].a.get_text(),
                'link': articles[index].a.get('href'),
                'date': timestamps[index].get_text(), 
                'content': get_mit_article_content("http://news.mit.edu/" + articles[index].a.get('href'))
            }
        )

    return resulting_json

def json_to_file(json_data):
    with open('mit_data.json', 'w') as outfile:  
        json.dump(json_data, outfile)

json_to_file(mit_to_json(get_mit_news_info(), get_mit_timestamps()))