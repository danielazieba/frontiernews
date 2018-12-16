#functions relating to taking parsed website data and converting it to JSON
#used as reference for this file: https://stackabuse.com/reading-and-writing-json-to-a-file-in-python/

import json
from illinois_scrape import *
from bs4 import BeautifulSoup

def get_month_number(month):
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

def get_month(index):
    return {
        1: "January",
        2: "February",
        3: "March",
        4: "April",
        5: "May",
        6: "June",
        7: "July",
        8: "August",
        9: "September",
        10: "October",
        11: "November",
        12: "December",
    }[index]

def clean_date(date_text):
    year = date_text[-4:]
    day = date_text[-8:-6]

    for index in range(1, 13):
        curr = date_text.find(get_month(index))
        if(curr >= 0):
            return str(get_month_number(date_text[curr:-(len(date_text) - len(get_month(index)) - curr)])) + "/" + str(day).strip() + "/" + str(year)
    

def to_json(source, link_list, timestamps):
    resulting_json = {}
    resulting_json['articles'] = []

    for index in range(len(link_list)):
        resulting_json['articles'].append(
            {
                'source': source,
                'title': link_list[index].get_text(),
                'link': link_list[index].a.get('href'),
                'date': clean_date(timestamps[index].get_text()),
                'content': get_illinois_article_content("https://cs.illinois.edu" + link_list[index].a.get('href'))
            }
        )

    return resulting_json

def json_to_file(json_data):
    with open('uiuc_data.json', 'w') as outfile:  
        json.dump(json_data, outfile)

#print(to_json('University of Illinois', get_illinois_news(), get_illinois_timestamps()))

json_to_file(to_json('University of Illinois', get_illinois_news(), get_illinois_timestamps()))