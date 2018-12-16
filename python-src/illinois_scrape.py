#scrape https://cs.illinois.edu/news

import requests
import time

from bs4 import BeautifulSoup

#returns list of news articles in h3 tag format
def get_illinois_news():
    url = 'https://cs.illinois.edu/news'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    links = soup.find('div', attrs={"id": "content"}).find_all('h3')

    return links;

#returns list of corresponding timestamps
def get_illinois_timestamps():
    url = 'https://cs.illinois.edu/news'

    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    links = soup.find_all('span', attrs={"class": "date-display-single"})

    return links;

#assuming URL is a CS@Illinois news article, returns article text
def get_illinois_article_content(url):
    response = requests.get(url)
    html = response.content

    # give HTML to BeautifulSoup to get user data
    soup = BeautifulSoup(html, "html.parser")
    content = soup.find('div', attrs={"class": "blog-carousel-desc"})

    return content.get_text();

print (get_illinois_news())
print (get_illinois_timestamps())
print (get_illinois_article_content("https://cs.illinois.edu/news/preventing-spread-misinformation-online"))