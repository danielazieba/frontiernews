#functions relating to taking parsed website data and converting it to JSON
#used as reference for this file: https://stackabuse.com/reading-and-writing-json-to-a-file-in-python/

import json
from stanford_scrape import *
from bs4 import BeautifulSoup

def stanford_to_json(articles):
    resulting_json = {}
    resulting_json['articles'] = []

    for index in range(len(articles)):
        resulting_json['articles'].append(
            {
                'source': "Stanford University",
                'title': articles[index].a.get_text(),
                'link': articles[index].a.get('href'),
                'date': articles[index].find('div', attrs={"class","date-display-single"}), 
                'content': get_stanford_article_content("https://engineering.stanford.edu" + articles[index].a.get('href'))
            }
        )

    return resulting_json

def json_to_file(json_data):
    with open('stanford_data.json', 'w') as outfile:  
        json.dump(json_data, outfile)

json_to_file(stanford_to_json(get_stanford_news_info()))