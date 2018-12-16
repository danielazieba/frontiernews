#scrape https://engineering.stanford.edu/news/school-news

import requests
import time

from bs4 import BeautifulSoup

#returns list of news articles from which title, link can be found
def get_stanford_news_info():
    url = 'https://engineering.stanford.edu/news/school-news'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get data
    soup = BeautifulSoup(html, "html.parser")
    article_info = soup.find_all('div', attrs={"class": "postcard-content"})

    return article_info[0:-2];

#assuming URL is a stanford engineering news article, returns article text
def get_stanford_article_content(url):
    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get data
    soup = BeautifulSoup(html, "html.parser")
    content = soup.find('div', attrs={"class": "field-type-text-with-summary"}).get_text()

    return content;