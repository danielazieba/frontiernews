#pragma once

#include "ofMain.h"
#include "json_utils.hpp"
#include <vector>

enum NewsState {
    LANDING = 0,
    ABOUT,
    SETTINGS,
    FEED,
    ARTICLE
};

enum ArticleComponent {
    TITLE,
    SOURCE,
    DATE,
    CONTENT
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    Feed feed;
    
    void initFeed(); // initialize feed with UIUC + CMU + GA Tech data
    
    /*begin fonts*/
    ofTrueTypeFont headerFont;
    ofTrueTypeFont titleFont;
    ofTrueTypeFont sansTitleFont;
    ofTrueTypeFont sansLandingFont;
    ofTrueTypeFont landingFont;
    /*end fonts*/
    
    NewsState app_state = LANDING; // used to keep track of page user should be on
    int NUM_ARTICLES = 10; // default number of articles utilized
    int num_pages = 1; // for now; this will be changed in initialization
    int curr_page = 1;
    int char_factor = 9; // char size on screen; used to calculate row size
    int page_index = 1;
    int max_per_page = 10;
    

    int max_content_lines = 39;
    int top_content_index = 0;
    int bottom_content_index = 38;
    
    int curr_article_index = -1;
    vector<vector<string>> articles; // stores article information
    vector<string> loaded_article; // stores current article content
    
    vector<article::Article::Article> articles_new;
    
    // settings page variables
    int curr_settings_index = -1;
    int curr_source_index = 0;
    int curr_tag_index = 0;
    int curr_max_date_index = 0;
    int curr_min_date_index = 0;
    
    Date max_date;
    Date min_date;
    
    bool containsSource(string poss_source);
    bool containsTag(Tag poss_tag);
    void removeFromSelected(string source);
    vector<string> sources;
    vector<string> selected_sources;
    vector<Tag> tags;
    vector<Tag> selected_tags;
    
    // settings page functions
    void drawSourceToggle();
    void drawCurrSource();
    
    void drawTagToggle();
    void drawCurrTag();
    
    void drawMaxDate();
    void drawMinDate();
    
    void drawCurrMaxDate();
    void drawCurrMinDate();
    
    void updateFeedSettings();
    
    void updateSettingsW();
    void updateSettingsS();
    void updateSettingsA();
    void updateSettingsD();
    void updateSettingsL();
    // end settings
    
    string articleTitle(int article_index); // returns article title given index
    string articleSource(int article_index); // returns article source given index
    string articleDate(int article_index); // returns article date given index
    string articleContent(int article_index); // returns article content given index
    
    void calculateMaxPage(); // uses articles to calculate maximum page number
    
    void jsonArticleInit(string file_name); // initializes articles
    void jsonCombinedArticleInit(vector<string> file_names);
    void drawLanding(); // draws landing page
    void drawAbout(); // draws about page
    void drawSettings(); // draws settings page
    void drawArticle(int article_index); // draws article given an article index
    void drawFeed(); // draws feed page
    void drawNav(); // draws article navigation
    void drawPage(); // displays current page footer
    void drawPageContent(); // displays current page content
    void drawSelectedContent(); // draws currently selected article
    void drawCurrentContent(); // draws current article content
    
    void updateIndexW(); //updates article index when W is pressed
    void updateIndexS(); // updates article index when S is pressed
    void updatePageIndexA(); //updates page index when A is pressed
    void updatePageIndexD(); //updates page index when D is pressed
    
    void updateContentW(); // updates content lines when W is pressed
    void updateContentS(); // updates content lines when S is pressed
    
    bool articleOnPage(); // returns true if article index is on current page, false otherwise
    bool articleOnPageW(); // returns true if prev article index is on current page, false otherwise
    
    void formatContent(int article_index); // formats desired article's content based on current window size
    void formatContentAll(); // formats all articles in vector based on current window size
    
    void loadContent(string content); // updates loaded article with given content
};
