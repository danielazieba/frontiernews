# Development Log

## 11/10 - 11/11:

* Created python scripts implementing BeautifulSoup which successfully web scrape CS@Illinois news and download to a JSON file

* Current JSON format is as such:

{
	‘articles’: [
		{
      ‘source’: ‘’,
	    ‘title’: ‘’,
	    ‘link’: ‘’,
	    ‘date’: ‘’
		}
  ]
}

* Began using rapidjson C++ library

## 11/12 - 11/16:

* Created oF application to visually load articles into a feed

  * Users can read about, description, settings, and list of articles

  * Application allows users to navigate given key inputs

  * Interface well-tested for exception inputs; for example, articles cannot be navigated on main landing page

  * Application currently stores a vector of articles using the same format as JSON file; built to easily scale to JSON data

  * Can dynamically display list of articles, creating the appropriate amount of pages required and resizing article content to fit the window

* Two other iterations of oF applications created, not used in the end; experimented with oFxGui components, which will be used later for settings feature (but was not needed for this week’s functionality)

## 11/24 - 11/26:

* Accomplished successful implementation of rapidjson C++ library to read in JSON generated through Python scripts and produce outputs in C++

* Modified JSON schema to include content

{
	‘articles’: [
		{
		    ‘source’: ‘’,
		    ‘title’: ‘’,
		    ‘link’: ‘’,
		    ‘date’: ‘’,
		    'content': ''
		}
  ]
}

* Created new web scraping script function to download article content in Python from CS@Illinois

## 11/27 - 11/29:

* Successfully modified original OF application to read in JSON article data and display it in the news feed

* Implemented a scroll feature to allow users to read the entirety of articles that would otherwise bleed off of the OF window

	* Learned through this, and frontend design from last week, that C++/openFrameworks requires a little (a lot!) more manual design of interfaces than web technologies 
	
	* Gained newfound appreciation for aforementioned web technologies; designing fluid interfaces is difficult
	
	* New forms of content storage were required to design scroll, as well as functions/variables to allow users to scroll using W, S keys

* Successfully web scraped Carnegie Mellon CS news website for content stored in JSON file

* Successfully displayed CMU CS news with no issues in same application for UIUC news

## 11/30 - 12/02

* Web scraped for MIT EECS news articles, can download to JSON

* Web scraped for Georgia Tech SCS news articles, can download to JSON

* Web scraped for Stanford Engineering news articles, can download to JSON

* Redesigned user interface
	
	* Decided on minor design improvements

	* Changed color of background from default to white

	* Used lessons learned from a previous class about document design to create interface (sans serif headings, serif body)
	* Imported, loaded multiple Google fonts to OF application

	* Debated heavily on sans serif vs. serif body text for content because sans serif is more common as a web standard, but ended up going with a serif font for main content to replicate the feeling of reading a book, research paper, etc.
	
## 12/03 - 12/06
	
* Created article class

	* Article class again changes format by storing a version of content which is a vector of each word in the article, vector of tags
	
	* Article class includes both a default and custom constructor such that JSON data can seamlessly be loaded into the article

	* Class implements get/set methods for all class variables, plus a function allowing for checking of whether or not an article has a specific tag and some helper initialization functions
	
	* Implemented unit testing for article class, which passes with 34 assertions
	
* Created feed class

	* Feed class stores a general base of articles from which a current feed can be generated

	* Implements get/set for all member variables, some helper functions
	
	* Helper functions carry out tasks such as sorting, updating feed

	* Search feature will be implemented by utilizing the updateFeed functions to update given new boundaries imposed by the user

* Began Date class used to store dates in a central manner rather than in potentially-differing formats from different websites

* Conducted minor restructure of GitHub file directory

## 12/08

* Created functionality for settings page toggles using sample data

	* Allows users to navigate between toggles for source, tag
	
* Updated About page 

## 12/09

* Finished implementation of Date class

* Refactored article, feed classes such that classes successfully integrate Date

* Made updates to web-scraping scripts such that scripts convert to the same date format of month/day/year to allow for potential manipulation of dates across different sources

## 12/10

* Finished implementation of Feed class

* Began integration of Feed class with UI

* Updated utils functions to utilize new Article class

## 12/11

* Successfully integrated Article class into UI

* Successfully conducted unit testing of Date class functions (which involved a significant amount of debugging)

## 12/12

* Successfully conducted unit testing of Feed class functions (also involving a significant amount of debugging)

* Successfully integrated Feed class with openFrameworks

* Implemented max/min date filtering

* Implemented source filtering



