# Welcome to Frontier News!

Frontier News is a project I built primarily using C++ and openFrameworks. Other technologies incorporated include the Catch 2 framework for unit testing, rapidJSON for parsing JSON, and BeautifulSoup for scraping news websites.

# Project overview

Frontier News is a news feed generated of articles downloaded from university computer science department websites using BeautifulSoup. From there, the articles are parsed and stored in JSON files. Using rapidJSON, these JSON files are then processed in C++ before moving on to storage in object representation visualized by openFrameworks.

The JSON structure utilized in this project is as such:

 * {
 'articles' : [
     {
       'source': string,
       'title': string,
       'link': string,
       'date': string,
       'content': string
     } ]
}

Some challenges I faced in project development included parsing JSON data from different sources into the same format, as well as the general decision-making required throughout the process of moving data from HTML to Python to JSON to C++ to a visual format in openFrameworks. I took many things for granted in web technologies before working on this project such as scrolling, text-wrapping, and interfacing between pages with one link embed. A significant driving factor in development was scalability of this project, and the result is that any JSON file formatted correctly can be read in to generate an article feed.

# Breakdown of repository components

The following is a description of the directories in this repository and what they do:

* article-class: This stores article-related C++ code and the associated unit testing conducted.

* finalproject-gui: An initial project increment developed such that articles, without any JSON data integration, could be displayed in openFrameworks.

* finalproject-jsondisplay: An initial increment of this project which successfully reads in and displays data from JSON files following the article format correctly.

* finalproject-ui: The final result, which combines components from everything else. This involved significant user interface reform, implementation of a settings page, an update to the old about page, and integration with the code stored in article-class.

* news-json: Stores JSON files gathered from various websites.

* python-src: Stores all scripts used to download JSON files.

# Build instructions

Any of the openFrameworks applications included in this project should be executed following the general OF instructions for execution. I personally utilized XCode, in which the only configuration required should involve running the "[project name] Debug" scheme and updating the application in the openFrameworks project creator.

To run the python scripts and download JSON, execute any of the "[source]_to_json.py" files. 

# Ideas for future additions to this project

There are multiple fronts through which this project could be incremented. Some of my thoughts include:

* Making tagging work. If you look at the code, you will see successful tagging functionality included for articles but commented out. The only missing part is determining the tags themselves, and depending on the complexity, tagging could be as simple as checking for one word and adding the tag accordingly.

* Improving detail of web-scraping. The general news engine can be used with article data of ANY kind. Many kinds of feeds could be made!

* Creating a more visually pleasing user experience

* Creating a collision system and/or more efficient method of article storage

* Adding more methods of Tag parsing, as well as more tags in general to the current enum

* Moving the entire project away from openFrameworks and into a web application, solving many issues relating to user interface deficiencies
