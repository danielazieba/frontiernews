#pragma once

#include "ofMain.h"
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
        NewsState app_state = LANDING; // used to keep track of page user should be on
        int NUM_ARTICLES = 10; // default number of articles utilized
        int num_pages = 1; // for now; this will be changed in initialization
        int curr_page = 1;
        int char_factor = 9; // char size on screen; used to calculate row size
        int page_index = 1;
        int max_per_page = 10;
        int curr_article_index = -1;
        vector<vector<string>> articles; // stores article information
    
        string articleTitle(int article_index); // returns article title given index
        string articleSource(int article_index); // returns article source given index
        string articleDate(int article_index); // returns article date given index
        string articleContent(int article_index); // returns article content given index
    
        void calculateMaxPage(); // uses articles to calculate maximum page number
    
        void sampleArticleInit(); // initializes articles with sample data
        void drawLanding(); // draws landing page
		void drawAbout(); // draws about page
        void drawSettings(); // draws settings page
        void drawArticle(int article_index); // draws article given an article index
        void drawFeed(); // draws feed page
        void drawNav(); // draws article navigation
        void drawPage(); // displays current page footer
        void drawPageContent(); // displays current page content
        void drawSelectedContent(); // draws currently selected article
    
        void updateIndexW(); //updates article index when W is pressed
        void updateIndexS(); // updates article index when S is pressed
        void updatePageIndexA(); //updates page index when A is pressed
        void updatePageIndexD(); //updates page index when D is pressed
        bool articleOnPage(); // returns true if article index is on current page, false otherwise
        bool articleOnPageW(); // returns true if prev article index is on current page, false otherwise
    
        void formatContent(int article_index); // formats desired article's content based on current window size
        void formatContentAll(); // formats all articles in vector based on current window size
};
