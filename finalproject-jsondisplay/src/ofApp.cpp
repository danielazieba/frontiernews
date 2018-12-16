#include "ofApp.h"

using namespace rapidjson;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Frontier News");
    jsonArticleInit("uiuc_data.json"); // initializes with UIUC articles
    formatContentAll();
    calculateMaxPage(); // uses article size to calculate pages needed to load articles
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // use a switch statement to determine which page to generate for user
    switch(app_state) {
        case LANDING:
            drawLanding();
            break;
        case ABOUT:
            drawAbout();
            break;
        case SETTINGS:
            drawSettings();
            break;
        case FEED:
            drawFeed();
            break;
        case ARTICLE:
            drawSelectedContent();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }
    
    int upper_key = toupper(key); // Standardize on upper case
    
    switch(upper_key) {
        case 'F':
            app_state = (app_state == LANDING) ? ABOUT : app_state;
            break;
        case 'G':
            app_state = (app_state == LANDING) ? SETTINGS : app_state;
            break;
        case 'H':
            app_state = (app_state == LANDING) ? FEED : app_state;
            break;
        case 'B':
            app_state = (app_state == ARTICLE) ? FEED : LANDING;
            break;
        case 'W':
            if (app_state == FEED) {
                updateIndexW();
            }
            if (app_state == ARTICLE) {
                updateContentW();
            }
            break;
        case 'S':
            if (app_state == FEED) {
                updateIndexS();
            }
            if (app_state == ARTICLE) {
                updateContentS();
            }
            break;
        case 'A':
            if (app_state == FEED) {
                updatePageIndexA();
            }
            break;
        case 'D':
            if (app_state == FEED) {
                updatePageIndexD();
            }
            break;
        case 'L':
            app_state = (app_state == FEED && curr_article_index >= 0) ? ARTICLE : app_state;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


//--------------------------------------------------------------
// Initialization functions
//--------------------------------------------------------------

void ofApp::sampleArticleInit(){
    /*
     push 10 sample articles into articles vector
     currently, outer vector holds articles
     inner vectors hold data in the format of:
     {string title, string source, string date, string content}
     */
    articles.push_back({"Article 1", "UIUC", "4/20/2018", "This lesson introduces the CCP and ECCP modules’ pulse-width modulation (PWM) modes, which allow us to control the average voltage (and power) supplied to a load. This is done by rapidly toggling one or more outputs with a variable duty cycle, which can be adjusted smoothly, with up to 10-bit resolution. As the duty cycle increases, so too does the average delivered power."});
    articles.push_back({"Article 2", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 3", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 4", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 5", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 6", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 7", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 8", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 9", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 10", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 11", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 12", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 13", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 14", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 15", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 16", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 17", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 18", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 19", "UIUC", "4/20/2018", "Here is some content please thank you"});
    articles.push_back({"Article 20", "UIUC", "4/20/2018", "Here is some content please thank you"});
}

void ofApp::jsonArticleInit(string file_name){
    Document json_tree = getDocumentFromString(file_name);
    
    
    /*
     assert that document is array and specific elements are strings
     (errors are caught here if this does not follow expected JSON format)
     */
    
    assert(json_tree.IsObject());
    assert(json_tree.HasMember("articles"));
    assert(json_tree["articles"].IsArray());
    
    vector<string> curr_article = {"", "", "", ""};
    
    for (SizeType i = 0; i < json_tree["articles"].Size(); i++){ // Uses SizeType instead of size_t

        curr_article[ArticleComponent::TITLE] = json_tree["articles"][i]["title"].GetString();
        curr_article[ArticleComponent::SOURCE] = json_tree["articles"][i]["source"].GetString();
        curr_article[ArticleComponent::DATE] = json_tree["articles"][i]["date"].GetString();
        curr_article[ArticleComponent::CONTENT] = json_tree["articles"][i]["content"].GetString();
        
        articles.push_back(curr_article);
    }
}

void ofApp::calculateMaxPage(){
    num_pages = articles.size() / max_per_page;
    
    std::cout << "article number: " << articles.size();
}

//--------------------------------------------------------------
// Draw functions
//--------------------------------------------------------------
void ofApp::drawLanding(){
    string message = "Welcome to Frontier News!\n";
    message += "about - press f \n";
    message += "settings - press g \n";
    message += "read - press h \n";
    ofSetColor(0, 0, 0);
    
    ofDrawBitmapString(message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void ofApp::drawAbout(){
    string message = "about.\n";
    message += "created by Daniela Zieba\n\n";
    message += "The goal of FrontierNews is to create a news feed for computer science research, \ngenerated by news feeds of university computer science departments. \nThis methodology allows for inclusion of research from diverse backgrounds and in bulk,\nas opposed to pre-filtered research reporting.\n\n";
    message += "press b to go back to landing.";
    
    ofSetColor(0, 0, 0);
    
    ofDrawBitmapString(message, 2, ofGetWindowHeight() / 2);
}

void ofApp::drawSettings(){
    string message = "settings.\n";
    message += "currently under construction!\n\n";
    message += "press b to go back to landing.";
    ofSetColor(0, 0, 0);
    
    ofDrawBitmapString(message, 2, ofGetWindowHeight() / 2);
}

void ofApp::drawFeed(){
    string message = "Frontier News\n\n";
    message += "controls - use WASD to navigate. l to select an article. b to go back to landing. \n";
    ofSetColor(0, 0, 0);
    
    ofDrawBitmapString(message, 10, ofGetWindowHeight() / 15);
    
    drawPageContent();
    drawPage();
}

void ofApp::drawPage(){
    string message = "Page " + to_string(curr_page) + " of " + to_string(num_pages);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(message, (ofGetWindowWidth() / 2) - 50, ofGetWindowHeight() - 10);
}

void ofApp::drawArticle(int article_index) {
    /*
     get article at given index from articles vector
     if current article index matches article index, display as white text
     otherwise, display as black text
     print article's title, source, and date
     */
    vector<string> selected_article = articles[article_index];
    
    string article = articleTitle(article_index) + "\n" + articleSource(article_index) + "\n" + articleDate(article_index) + "\n";
    
    
    if (article_index != curr_article_index) {
        ofSetColor(0, 0, 0);
    } else {
        ofSetColor(255, 255, 255);
    }
    
    ofDrawBitmapString(article, 10, (ofGetWindowHeight() / 8) + (50*(page_index)));
}

void ofApp::drawSelectedContent() {
    vector<string> selected_article = articles[curr_article_index];
    loadContent(selected_article[ArticleComponent::CONTENT]);
    
    string message = "Frontier News\n\npress b to go back.\n\n\n";
    
    string article = articleTitle(curr_article_index) + "\n" + articleSource(curr_article_index) + "\n" + articleDate(curr_article_index);
    
    drawCurrentContent();
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(message + article, 10, (ofGetWindowHeight() / 15));
}

void ofApp::drawPageContent(){
    page_index = 1;
    
    // display articles of current page
    for (int art_i = ((curr_page - 1) * max_per_page); art_i < (curr_page * max_per_page); art_i++){
        // make sure art_i is less than total size of articles
        if (art_i < articles.size()) {
            drawArticle(art_i);
            page_index++;
        }
    }
    
}

void ofApp::drawCurrentContent(){
    /*
     if top, bottom indexes exist within
     
     iterate through current article lines
     display each line plus \n
     top_content_index
     
     */
    string displayed_content = "\n\n\n\n\n\n\n\n";
    
    int begin_i = 0;
    int end_i = loaded_article.size();
    
    if (end_i >= top_content_index) {
        begin_i = top_content_index;
    }
    
    if (end_i >= bottom_content_index) {
        end_i = bottom_content_index;
    }
    
    for(int curr = begin_i; curr < end_i; curr++) {
        displayed_content += loaded_article[curr];
    }
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(displayed_content, 10, (ofGetWindowHeight() / 15));
}

//--------------------------------------------------------------
// Update functions
//--------------------------------------------------------------

void ofApp::updateIndexW(){
    if (curr_article_index == -1) {
        curr_article_index = 0;
    } else if (curr_article_index <= 0) {
        curr_article_index = 0;
    } else if (curr_article_index > (max_per_page * (curr_page - 1))){
        curr_article_index--;
    }
}

void ofApp::updateIndexS() {
    int max_index = articles.size() - 1;
    
    if (curr_article_index == -1) {
        curr_article_index = 0;
    } else if (curr_article_index < max_index && articleOnPage()) {
        // also check if article is on current page
        curr_article_index++;
    }
}

void ofApp::updatePageIndexA() {
    if (curr_page == -1 || curr_page == 0 || curr_page == 1) {
        curr_page = 1;
    } else {
        curr_page--;
        curr_article_index -= max_per_page;
    }
}

void ofApp::updatePageIndexD() {
    if (curr_page == -1) {
        curr_page = 1;
    } else if (curr_page != num_pages) {
        curr_page++;
        curr_article_index += max_per_page;
    }
}

bool ofApp::articleOnPage() {
    return ((curr_article_index + 1 > ((curr_page - 1) * max_per_page)) &&
            (curr_article_index + 1 < (curr_page * max_per_page)));
}

bool ofApp::articleOnPageW() {
    return ((curr_article_index - 1 > ((curr_page - 1) * max_per_page)) &&
            (curr_article_index - 1 < (curr_page * max_per_page)));
}

//--------------------------------------------------------------
// Functions to update scroll index
//--------------------------------------------------------------

void ofApp::updateContentW() {
    if (top_content_index <= 0) {
        top_content_index = 0;
    } else {
        top_content_index--;
        bottom_content_index--;
    }
}

void ofApp::updateContentS() {
    if (bottom_content_index >= loaded_article.size()) {
        bottom_content_index = loaded_article.size();
    } else {
        top_content_index++;
        bottom_content_index++;
    }
}

//--------------------------------------------------------------
// Article management functions
//--------------------------------------------------------------

void ofApp::formatContent(int article_index) {
    /*
     use current window width to insert /n characters
     this keeps article content on the page and keeps it from wrapping off of the screen
     
     search through content char by char
     at each index such that i = window width - 1, insert \n
     */
    int width = ofGetWindowWidth() / char_factor;
    
    string content = articleContent(article_index);
    
    for (int cont_i = width; cont_i < content.size(); cont_i += width) {
        articles[article_index][static_cast<int>(ArticleComponent::CONTENT)].insert(cont_i, "\n");
    }
}

void ofApp::formatContentAll() {
    for (int art_i = 0; art_i < articles.size(); art_i++) {
        formatContent(art_i);
    }
}

void ofApp::loadContent(string content) {
    /*
     store selected article content in current content vector
     */
    loaded_article.resize(0);
    
    int width = ofGetWindowWidth() / char_factor;
    bool enter = false;
    
    string line = "";
    for (int i = 0; i < content.size(); i++){
        char curr = content[i];
        
        if (curr == '\n') {
            line += curr;
            loaded_article.push_back(line);
            line = "";
        } else {
            line += curr;
            
            if (line.size() >= width) {
                loaded_article.push_back(line);
                line = "";
            }
        }
    }
}

string ofApp::articleTitle(int article_index) {
    return articles[article_index][static_cast<int>(ArticleComponent::TITLE)];
}

string ofApp::articleSource(int article_index) {
    return articles[article_index][static_cast<int>(ArticleComponent::SOURCE)];
}

string ofApp::articleDate(int article_index) {
    return articles[article_index][static_cast<int>(ArticleComponent::DATE)];
}

string ofApp::articleContent(int article_index) {
    return articles[article_index][static_cast<int>(ArticleComponent::CONTENT)];
}

