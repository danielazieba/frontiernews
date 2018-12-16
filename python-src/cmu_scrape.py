#scrape https://www.cs.cmu.edu/news

import requests
import time
import numpy

from bs4 import BeautifulSoup

#returns list of news articles
def get_cmu_news():
    url = 'https://www.cs.cmu.edu/news'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    articles = soup.find_all('article')

    return articles;

# finds and returns CMU article text content
def get_cmu_article_content(url):
    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    content = soup.find('div', attrs={"class": "article__copy"})
    print("Parsing article: " + url);

    return content.get_text();

#returns a cleaned version of CMU article titles
def clean_title(title_text):
    return title_text[15:-12]
