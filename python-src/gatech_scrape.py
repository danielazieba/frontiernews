#scrape https://www.scs.gatech.edu/news

import requests
import time
import numpy

from bs4 import BeautifulSoup

#returns list of news articles
def get_gatech_news():
    url = 'https://www.scs.gatech.edu/news'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    articles = soup.find_all('h3', attrs={"class": "news-title"})

    return articles;

# finds and returns gatech article text content
def get_gatech_article_content(url):
    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    content = soup.find('div', attrs={"class": "field-name-field-news-body"})

    return content.get_text();

def get_gatech_timestamps(url):
    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    timestamps = soup.find('span', attrs={"class": "date-display-single"})

    return timestamps.get_text()[5:];
