# Project Proposal

# Summary

Research in computer science is often reported on through many general computing/technology websites, but comes pre-filtered and in short stock. On general technology websites, research is usually uncommon in favor of tech news focused on Silicon Valley culture. This project proposes to provide users with a computer science research feed and interface generated by pulling news articles from the websites of university computer science departments. Diving immediately into research papers has its flaws from a user experience perspective as well as in the issue of legitimacy if searching through potentially predatory journals. In addition, some interesting research may not culminate in publication if affiliated with industry or for ethical reasons.

# Project Plan

I intend to first successfully scrape some initial data with which a rudimentary feed could be constructed. After this, I can then create a user interface in openFrameworks using this information to identify an optimal interface layout. As the functionality of the project develops, I expect the frontend interface to undergo multiple iterations of improvements. Some planned features/iterations include the following, and will be developed in this order:
* Successful web scraping of university websites
* Using university list to access university computer science departmental website news pages
* Display above data using openFrameworks interface
* Allow users to filter articles display through parameter adjustment

# External Libraries

The following external libraries have been identified for use in this project:
* BeautifulSoup, which is a Python library used for web scraping
* rapidJSON, a C++ library allowing for elegant and fast JSON parsing