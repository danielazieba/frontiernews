#include "ofApp.h"

using namespace rapidjson;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    headerFont.load("Lora-Regular.ttf", 10, true, true, true);
    titleFont.load("Lora-Bold.ttf", 10, true, true, true);
    sansTitleFont.load("Yantramanav-Thin.ttf", 18, true, true, true);
    sansLandingFont.load("Yantramanav-Thin.ttf", 35, true, true, true);
    landingFont.load("Lora-Regular.ttf", 15, true, true, true);
    ofSetWindowTitle("Frontier News");
    initFeed();
    articles_new = feed.getFeed();
    max_date = feed.getMaxDate();
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
            if (app_state == SETTINGS) {
                updateSettingsW();
            }
            break;
        case 'S':
            if (app_state == FEED) {
                updateIndexS();
            }
            if (app_state == ARTICLE) {
                updateContentS();
            }
            if (app_state == SETTINGS) {
                updateSettingsS();
            }
            break;
        case 'A':
            if (app_state == FEED) {
                updatePageIndexA();
            }
            if (app_state == SETTINGS) {
                updateSettingsA();
            }
            break;
        case 'D':
            if (app_state == FEED) {
                updatePageIndexD();
            }
            if (app_state == SETTINGS) {
                updateSettingsD();
            }
            break;
        case 'L':
            app_state = (app_state == FEED && curr_article_index >= 0) ? ARTICLE : app_state;
            if (app_state == SETTINGS){
                updateSettingsL();
            }
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

void ofApp::initFeed(){
    vector<string> file_names = {"uiuc_data.json", "cmu_data.json", "gatech_data.json"};
    feed.setArticles(multipleListsFromJSON(file_names));
    
    sources = feed.getUnis();
    tags = feed.getTags();
}

void ofApp::calculateMaxPage(){
    num_pages = articles_new.size() / max_per_page;
}

//--------------------------------------------------------------
// Draw functions
//--------------------------------------------------------------
void ofApp::drawLanding(){
    string title = "Welcome to Frontier News!\n";
    string message = "Navigate using WASD. Press L to select.\n";
    message += "About - press f \n";
    message += "Settings - press g \n";
    message += "Read - press h \n";
    ofSetColor(0, 0, 0);
    
    sansLandingFont.drawString(title, ofGetWindowWidth() / 4, ofGetWindowHeight() / 5);
    landingFont.drawString(message, ofGetWindowWidth() / 3, ofGetWindowHeight() / 2);
//    ofDrawBitmapString(message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void ofApp::drawAbout(){
    string about = "about.\n";
    string message = "";
    message += "\nFrontier News was created by Daniela Zieba in December 2018.\n\n";
    message += "This project uses articles scraped from various university computer science news websites to generate a\nfeed of interesting academic computing news. I wanted to create this because most technology websites\nare focused on industry-related issues, while academic publication venues can be guarded behind paywalls\nor are generally difficult to access. Additionally, many interesting advancements in computer science are\nopen-sourced, rather than published; I believed department news websites to be one way for finding such\ntechnologies.\n\n";
    message += "Articles can be filtered by source, type, and date. If you would like to update the articles used, re-run the\nPython scripts I used to download web data.\n\n\n";
    message += "Press B to go back.";
    
    ofSetColor(0, 0, 0);
    
    sansLandingFont.drawString(about, 10, ofGetWindowHeight() / 8);
    landingFont.drawString(message, 10, ofGetWindowHeight() / 6);
}

void ofApp::drawSettings(){
    string settings = "settings.\n";
    
    string apply = "Apply changes";
    if (curr_settings_index == 4) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }

    sansLandingFont.drawString(settings, 10, ofGetWindowHeight() / 8);
    landingFont.drawString(apply, 10, ofGetWindowHeight() / 2);
    drawSourceToggle();
    //drawTagToggle();
    drawMaxDate();
    drawMinDate();
}

void ofApp::drawSourceToggle(){
    string source = "Toggle sources: ";
    if (curr_settings_index == 0) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(source, 10, ofGetWindowHeight() / 6);
    drawCurrSource();
}

void ofApp::drawTagToggle(){
    string tag = "Toggle tags: ";
    if (curr_settings_index == 1) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(tag, 10, ofGetWindowHeight() / 5);
    drawCurrTag();
}

bool ofApp::containsSource(string poss_source){
    for (int i = 0; i < selected_sources.size(); i++) {
        if (poss_source == selected_sources[i]) {
            return true;
        }
    }
    
    return false;
}

bool ofApp::containsTag(Tag poss_tag) {
    for (int i = 0; i < selected_tags.size(); i++) {
        if (poss_tag == selected_tags[i]) {
            return true;
        }
    }
    
    return false;
}

void ofApp::drawCurrSource(){
    string curr_source = "";
    
    if (curr_source_index >= 0) {
        curr_source += sources[curr_source_index];
    }
    
    if(containsSource(sources[curr_source_index])){
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(curr_source, 175, ofGetWindowHeight() / 6);
}

void ofApp::drawCurrTag(){
    string curr_tag = "";
    
    if (curr_tag_index >= 0) {
        curr_tag += tags[curr_tag_index];
    }
    
    if(containsTag(tags[curr_tag_index])){
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(curr_tag, 175, ofGetWindowHeight() / 5);
}

void ofApp::drawMaxDate(){
    string max = "Max date: ";
    
    if (curr_settings_index == 2) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(max, 10, ofGetWindowHeight() / 4);
    drawCurrMaxDate();
}

void ofApp::drawCurrMaxDate(){
    string max_month = to_string(max_date.getMonth());
    
    if (curr_max_date_index == 1) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(max_month, 130, ofGetWindowHeight() / 4);
    
    string max_day = to_string(max_date.getDay());
    
    if (curr_max_date_index == 2) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(max_day, 160, ofGetWindowHeight() / 4);
    
    string max_year = to_string(max_date.getYear());
    
    if (curr_max_date_index == 3) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(max_year, 190, ofGetWindowHeight() / 4);
    
    string divisor = "/";
    
    landingFont.drawString(divisor, 176, ofGetWindowHeight() / 4);
    landingFont.drawString(divisor, 145, ofGetWindowHeight() / 4);
}

void ofApp::drawMinDate(){
    string min = "Min date: ";
    
    if (curr_settings_index == 3) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(min, 10, ofGetWindowHeight() / 3);
    drawCurrMinDate();
}

void ofApp::drawCurrMinDate(){
    string min_month = to_string(min_date.getMonth());
    
    if (curr_min_date_index == 1) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(min_month, 130, ofGetWindowHeight() / 3);
    
    string min_day = to_string(min_date.getDay());
    
    if (curr_min_date_index == 2) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(min_day, 160, ofGetWindowHeight() / 3);
    
    string min_year = to_string(min_date.getYear());
    
    if (curr_min_date_index == 3) {
        ofSetColor(50, 57, 73);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    landingFont.drawString(min_year, 190, ofGetWindowHeight() / 3);
    
    string divisor = "/";
    
    landingFont.drawString(divisor, 176, ofGetWindowHeight() / 3);
    landingFont.drawString(divisor, 145, ofGetWindowHeight() / 3);
}

void ofApp::drawFeed(){
    string message = "Frontier News\n\n";
    message += "controls - WASD to navigate. L to select. B to go back. \n";
    ofSetColor(0, 0, 0);
    
    titleFont.drawString(message, 10, ofGetWindowHeight() / 15);
    
    drawPageContent();
    drawPage();
}

void ofApp::drawPage(){
    string message = "Page " + to_string(curr_page) + " of " + to_string(num_pages);
    
    ofSetColor(0, 0, 0);
    headerFont.drawString(message, (ofGetWindowWidth() / 2) - 50, ofGetWindowHeight() - 10);
}

void ofApp::drawArticle(int article_index) {
    /*
     get article at given index from articles vector
     if current article index matches article index, display as white text
     otherwise, display as black text
     print article's title, source, and date
     */
    article::Article::Article selected_article = articles_new[article_index];
    
    string article = articleTitle(article_index);
    string article_desc = "\n" + articleSource(article_index) + "\n" + articleDate(article_index) + "\n";
    
    
    if (article_index != curr_article_index) {
        ofSetColor(0, 0, 0);
    } else {
        ofSetColor(50, 57, 73);
    }
    
    
    titleFont.drawString(article, 20, (ofGetWindowHeight() / 10) + (60*(page_index)));
    headerFont.drawString(article_desc, 20, (ofGetWindowHeight() / 10) + (60*(page_index)));
}

void ofApp::drawSelectedContent() {
    article::Article::Article selected_article = articles_new[curr_article_index];
    loadContent(selected_article.getContent());
    
    string title = "Frontier News";
    string message = "\npress b to go back.\n\n\n";
    
    string article = articleTitle(curr_article_index) + "\n" + articleSource(curr_article_index) + "\n" + articleDate(curr_article_index);
    
    drawCurrentContent();
    
    ofSetColor(0, 0, 0);
    sansTitleFont.drawString(title, 20, (ofGetWindowHeight() / 15));
    titleFont.drawString(article, 20, (ofGetWindowHeight() / 7));
    headerFont.drawString(message, 20, (ofGetWindowHeight() / 15));
}

void ofApp::drawPageContent(){
    page_index = 1;
    
    // display articles of current page
    for (int art_i = ((curr_page - 1) * max_per_page); art_i < (curr_page * max_per_page); art_i++){
        // make sure art_i is less than total size of articles
        if (art_i < articles_new.size()) {
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
    headerFont.drawString(displayed_content, 100, (ofGetWindowHeight() / 15));
}

//--------------------------------------------------------------
// Update functions
//--------------------------------------------------------------

void ofApp::updateSettingsW(){
    if (curr_settings_index <= 0){
        curr_settings_index = 0;
    } else if (curr_settings_index == 2) {
        Date possible_max_date = max_date;
        
        switch (curr_max_date_index) {
        case 1:
            possible_max_date.setMonth(max_date.getMonth() + 1);
            if (possible_max_date.valid()){
                max_date = possible_max_date;
            }
            break;
        case 2:
            possible_max_date.setDay(max_date.getDay() + 1);
            if (possible_max_date.valid()){
                max_date = possible_max_date;
            }
            break;
        case 3:
            possible_max_date.setYear(max_date.getYear() + 1);
            if (possible_max_date.valid()){
                max_date = possible_max_date;
            }
            break;
        default:
            curr_settings_index--;
            break;
        }
    } else if (curr_settings_index == 3) {
        Date possible_min_date = min_date;
        
        switch (curr_min_date_index) {
            case 1:
                possible_min_date.setMonth(min_date.getMonth() + 1);
                if (possible_min_date.valid()){
                    min_date = possible_min_date;
                }
                break;
            case 2:
                possible_min_date.setDay(min_date.getDay() + 1);
                if (possible_min_date.valid()){
                    min_date = possible_min_date;
                }
                break;
            case 3:
                possible_min_date.setYear(min_date.getYear() + 1);
                if (possible_min_date.valid()){
                    min_date = possible_min_date;
                }
                break;
            default:
                curr_settings_index--;
                break;
        }
    } else {
        curr_settings_index--;
    }
}

void ofApp::updateSettingsS(){
    if (curr_settings_index >= 4){
        curr_settings_index = 4;
    } else if (curr_settings_index == 2) {
        Date possible_max_date = max_date;
        
        switch (curr_max_date_index) {
            case 1:
                possible_max_date.setMonth(max_date.getMonth() - 1);
                if (possible_max_date.valid()){
                    max_date = possible_max_date;
                }
                break;
            case 2:
                possible_max_date.setDay(max_date.getDay() - 1);
                if (possible_max_date.valid()){
                    max_date = possible_max_date;
                }
                break;
            case 3:
                possible_max_date.setYear(max_date.getYear() - 1);
                if (possible_max_date.valid()){
                    max_date = possible_max_date;
                }
                break;
            default:
                curr_settings_index++;
                break;
        }
    } else if (curr_settings_index == 3) {
        Date possible_min_date = min_date;
        
        switch (curr_min_date_index) {
            case 1:
                possible_min_date.setMonth(min_date.getMonth() - 1);
                if (possible_min_date.valid()){
                    min_date = possible_min_date;
                }
                break;
            case 2:
                possible_min_date.setDay(max_date.getDay() - 1);
                if (possible_min_date.valid()){
                    min_date = possible_min_date;
                }
                break;
            case 3:
                possible_min_date.setYear(min_date.getYear() - 1);
                if (possible_min_date.valid()){
                    min_date = possible_min_date;
                }
                break;
            default:
                curr_settings_index++;
                break;
        }
    }else {
        curr_settings_index++;
    }
}

void ofApp::updateFeedSettings(){
    feed.updateFeed(selected_sources, max_date, min_date);
    articles_new = feed.getFeed();
    formatContentAll();
    calculateMaxPage();
}

void ofApp::updateSettingsL(){
    string curr_source = articles_new[curr_source_index + 1].getSource();
    
    switch (curr_settings_index) {
        case 0:
            if (containsSource(curr_source)) {
                removeFromSelected(curr_source);
            } else {
                selected_sources.push_back(curr_source);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            updateFeedSettings();
            break;
        default:
            break;
    }
}

void ofApp::updateSettingsA(){
    switch (curr_settings_index) {
        case 0:
            if (curr_source_index <= 0) {
                curr_source_index = 0;
            } else {
                curr_source_index--;
            }
    
            break;
        case 1:
            if (curr_tag_index <= 0) {
                curr_tag_index = 0;
            } else {
                curr_tag_index--;
            }
            break;
        case 2:
            if (curr_max_date_index <= 0) {
                curr_max_date_index = 0;
            } else {
                curr_max_date_index--;
            }
            break;
        case 3:
            if (curr_min_date_index <= 0) {
                curr_min_date_index = 0;
            } else {
                curr_min_date_index--;
            }
            break;
        default:
            break;
    }

}

void ofApp::updateSettingsD(){
    switch (curr_settings_index) {
        case 0:
            if (curr_source_index < 0) {
                curr_source_index = 0;
            } else if (curr_source_index >= sources.size() - 1) {
                curr_source_index = sources.size() - 1;
            } else {
                curr_source_index++;
            }
            break;
        case 1:
            if (curr_tag_index < 0) {
                curr_tag_index = 0;
            } else if (curr_tag_index >= tags.size() - 1) {
                curr_tag_index = tags.size() - 1;
            } else {
                curr_tag_index++;
            }
            break;
        case 2:
            if (curr_max_date_index < 0) {
                curr_max_date_index = 0;
            } else if (curr_max_date_index >= 3) {
                curr_max_date_index = 3;
            } else {
                curr_max_date_index++;
            }
            break;
        case 3:
            if (curr_min_date_index < 0) {
                curr_min_date_index = 0;
            } else if (curr_min_date_index >= 3) {
                curr_min_date_index = 3;
            } else {
                curr_min_date_index++;
            }
            break;
        default:
            break;
    }
}


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
    int max_index = articles_new.size() - 1;
    
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
        content = articleContent(article_index);
        articles_new[article_index].setContent(content.insert(cont_i, "\n"));
    }
}

void ofApp::formatContentAll() {
    for (int art_i = 0; art_i < articles_new.size(); art_i++) {
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
    return articles_new[article_index].getTitle();
}

string ofApp::articleSource(int article_index) {
    return articles_new[article_index].getSource();
}

string ofApp::articleDate(int article_index) {
    return articles_new[article_index].getDate().toString();
}

string ofApp::articleContent(int article_index) {
    return articles_new[article_index].getContent();
}

void ofApp::removeFromSelected(string source){
    vector<string> new_sources;
    
    for (int i = 0; i < selected_sources.size(); i++){
        if (selected_sources[i] != source) {
            new_sources.push_back(selected_sources[i]);
        }
    }
    
    selected_sources = new_sources;
}
