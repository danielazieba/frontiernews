#functions relating to taking parsed website data and converting it to JSON
#used as reference for this file: https://stackabuse.com/reading-and-writing-json-to-a-file-in-python/

import json
from gatech_scrape import *
from bs4 import BeautifulSoup

def gatech_to_json(articles):
    resulting_json = {}
    resulting_json['articles'] = []

    for index in range(len(articles)):
        resulting_json['articles'].append(
            {
                'source': "Georgia Institute of Technology",
                'title': articles[index].a.get_text(),
                'link': articles[index].a.get('href'),
                'date': get_gatech_timestamps("https://www.scs.gatech.edu" + articles[index].a.get('href')), 
                'content': get_gatech_article_content("https://www.scs.gatech.edu" + articles[index].a.get('href'))
            }
        )

    return resulting_json

def json_to_file(json_data):
    with open('gatech_data.json', 'w') as outfile:  
        json.dump(json_data, outfile)

json_to_file(gatech_to_json(get_gatech_news()))