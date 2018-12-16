#functions relating to taking parsed website data and converting it to JSON
#used as reference for this file: https://stackabuse.com/reading-and-writing-json-to-a-file-in-python/

import json
from cmu_scrape import *
from bs4 import BeautifulSoup

def month_to_number(month):
    return {
        "January": 1,
        "February": 2,
        "March": 3,
        "April": 4,
        "May": 5,
        "June": 6,
        "July": 7,
        "August": 8,
        "September": 9,
        "October": 10,
        "November": 11,
        "December": 12,
    }[month]

def clean_date(date):
    day = date[9:-6]
    month = month_to_number(date[:len(date) - (len(date) - 9)].strip())
    year = date[-4:]

    return str(month) + "/" + str(day).strip() + "/" + str(year)

def cmu_to_json(articles):
    resulting_json = {}
    resulting_json['articles'] = []

    for index in range(10):
        resulting_json['articles'].append(
            {
                'source': "Carnegie Mellon University",
                'title': clean_title(articles[index].find('h2').get_text()),
                'link': articles[index].a.get('href'),
                'date': clean_date(articles[index].get_text()[len(articles[index].get_text()) - (9 + 17):-9]), 
                'content': get_cmu_article_content("https://www.cs.cmu.edu" + articles[index].find('a').get('href'))
            }
        )

    return resulting_json

def json_to_file(json_data):
    with open('cmu_data.json', 'w') as outfile:  
        json.dump(json_data, outfile)

json_to_file(cmu_to_json(get_cmu_news()))