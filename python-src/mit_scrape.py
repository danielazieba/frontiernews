#scrape http://news.mit.edu/topic/electrical-engineering-computer-science-eecs

import requests
import time

from bs4 import BeautifulSoup

#returns list of news articles from which title, link can be found
def get_mit_news_info():
    url = 'http://news.mit.edu/topic/electrical-engineering-computer-science-eecs'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get data
    soup = BeautifulSoup(html, "html.parser")
    article_info = soup.find_all('h3', attrs={"class": "title"})

    return article_info;

#returns list of corresponding timestamps
def get_mit_timestamps():
    url = 'http://news.mit.edu/topic/electrical-engineering-computer-science-eecs'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get
    soup = BeautifulSoup(html, "html.parser")
    timestamps = soup.find_all('em', attrs={"class": "date"})

    return timestamps;

#assuming URL is an MIT eecs news article, returns article text
def get_mit_article_content(url):
    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get data
    soup = BeautifulSoup(html, "html.parser")
    content = soup.find('div', attrs={"class": "field-item"}).get_text()

    return content;