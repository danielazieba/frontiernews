#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch.hpp"
#include "../src/article.cpp"
#include "../src/date.cpp"
#include "../src/feed.cpp"

using namespace std;
using namespace article;

TEST_CASE("[Default constructor]")
{
    article::Article::Article article;

    SECTION("Source")
    {
        REQUIRE(article.article::Article::getSource() == "");
    }

    SECTION("Title")
    {
        REQUIRE(article.getTitle() == "");
    }

    SECTION("Link")
    {
        REQUIRE(article.getLink() == "");
    }

    SECTION("Content")
    {
        REQUIRE(article.getContent() == "");
    }

    SECTION("Display")
    {
        REQUIRE(article.getDisplay().size() == 0);
    }

    SECTION("Tags")
    {
        REQUIRE(article.getTags().size() == 0);
    }

    SECTION("Date")
    {
        REQUIRE(article.getDate().getDay() == 1);
        REQUIRE(article.getDate().getMonth() == 1);
        REQUIRE(article.getDate().getYear() == 2018);
    }
}

TEST_CASE("[Custom Constructor]") {
    string source = "Test source";
    string title = "Test title";
    string link = "https://www.fsf.org/";
    string content = "A brief inquiry into online relationships.";
    string date = "12/17/2001";

    article::Article::Article article = Article(source, title, link, content, date);

    SECTION("Source")
    {
        REQUIRE(article.article::Article::getSource() == "Test source");
    }

    SECTION("Title")
    {
        REQUIRE(article.getTitle() == "Test title");
    }

    SECTION("Link")
    {
        REQUIRE(article.getLink() == "https://www.fsf.org/");
    }

    SECTION("Content")
    {   
        REQUIRE(article.getContent() == "A brief inquiry into online relationships.");
    }

    SECTION("Display")
    {
        REQUIRE(article.getDisplay().size() == 6);
    }

    SECTION("Tags")
    {
        REQUIRE(article.getTags().size() == 0);
    }

    SECTION("Date")
    {
        REQUIRE(article.getDate().getDay() == 17);
        REQUIRE(article.getDate().getMonth() == 12);
        REQUIRE(article.getDate().getYear() == 2001);
    }
}

TEST_CASE("[setSource]"){
    article::Article::Article article;
    string test;

    article.setSource(test);

    SECTION("Empty string"){
        REQUIRE(article.getSource() == "");
    }

    article.setSource("test source");

    SECTION("Non-empty string"){
        REQUIRE(article.getSource() == "test source");
    }

}

TEST_CASE("[setTitle]"){
    article::Article::Article article;
    string test;

    article.setTitle(test);

    SECTION("Empty string"){
        REQUIRE(article.getTitle() == "");
    }

    article.setTitle("test title");

    SECTION("Non-empty string"){
        REQUIRE(article.getTitle() == "test title");
    }

}

TEST_CASE("[setLink]"){
    article::Article::Article article;
    string test;

    article.setLink(test);

    SECTION("Empty string"){
        REQUIRE(article.getLink() == "");
    }

    article.setLink("test link");

    SECTION("Non-empty string"){
        REQUIRE(article.getLink() == "test link");
    }

}

TEST_CASE("[setContent]"){
    article::Article::Article article;
    string test;

    article.setContent(test);

    SECTION("Empty string"){
        REQUIRE(article.getContent() == "");
    }

    article.setContent("test content");

    SECTION("Non-empty string"){
        REQUIRE(article.getContent() == "test content");
    }

}

TEST_CASE("[setDisplay]"){
    article::Article::Article article;
    vector<string> test;

    article.setDisplay(test);

    SECTION("Empty vector"){
        REQUIRE(article.getDisplay().size() == 0);
    }

    article.setDisplay({"How", "to", "draw"});
    vector<string> non_empty = article.getDisplay();

    SECTION("Non-empty vector"){
        REQUIRE(non_empty.size() == 3);
        REQUIRE(non_empty[0] == "How");
        REQUIRE(non_empty[1] == "to");
        REQUIRE(non_empty[2] == "draw");
    }

}

TEST_CASE("[tagArticle]"){
    article::Article::Article article;
    vector<string> test = {"research"};

    article.setDisplay(test);
    article.tagArticle();

    SECTION("Contains research tag"){
        REQUIRE(article.getTags()[0] == RESEARCH);
    }

    test.resize(0);
    article.setDisplay(test);
    article.tagArticle();

    SECTION("Should not contain tags"){
        REQUIRE(article.getTags().size() == 0);
    }

    test = {"Hello", "I","am","cat"};
    article.setDisplay(test);
    article.tagArticle();

    SECTION("Should not contain tags"){
        REQUIRE(article.getTags().size() == 0);
    }

    test = {"research", "research", "research"};
    article.setDisplay(test);
    article.tagArticle();

    SECTION("Should only contain one tag"){
        REQUIRE(article.getTags()[0] == RESEARCH);
        REQUIRE(article.getTags().size() == 1);
    }
}

TEST_CASE("[hasTag]"){
    article::Article::Article article;
    vector<string> test = {"research"};

    article.setDisplay(test);
    article.tagArticle();

    SECTION("Contains research tag"){
        REQUIRE(article.hasTag(RESEARCH) == true);
    }

    test.resize(0);
    article.setDisplay(test);
    article.tagArticle();

    SECTION("Should not contain tags"){
        REQUIRE(article.hasTag(RESEARCH) == false);
    }

    test = {"Hello", "I","am","cat"};
    article.setDisplay(test);
    article.tagArticle();

    SECTION("Should not contain tag"){
        REQUIRE(article.hasTag(RESEARCH) == false);
    }

    test = {"research", "research", "research"};
    article.setDisplay(test);
    article.tagArticle();

    SECTION("Should contain tag"){
        REQUIRE(article.hasTag(RESEARCH) == true);
    }
}

// Date tests
TEST_CASE("[Default date constructor]")
{
    Date::Date date;

    SECTION("Month")
    {
        REQUIRE(date.getMonth() == 1);
    }

    SECTION("Day")
    {
        REQUIRE(date.getDay() == 1);
    }

    SECTION("Year")
    {
        REQUIRE(date.getYear() == 2018);
    }
}

TEST_CASE("[Custom integer date constructor]")
{
    Date::Date date = Date(2,3,2003);
    Date::Date unusual_date = Date(3000, 2947, 17363);

    SECTION("Month")
    {
        REQUIRE(date.getMonth() == 2);
    }

    SECTION("Day")
    {
        REQUIRE(date.getDay() == 3);
    }

    SECTION("Year")
    {
        REQUIRE(date.getYear() == 2003);
    }

    SECTION("Unusual month")
    {
        REQUIRE(unusual_date.getMonth() == 3000);
    }

    SECTION("Unusual day")
    {
        REQUIRE(unusual_date.getDay() == 2947);
    }

    SECTION("Unusual year")
    {
        REQUIRE(unusual_date.getYear() == 17363);
    }
}

TEST_CASE("[Custom string date constructor]")
{
    Date::Date date_single_digits = Date("2/3/2003");
    Date::Date date_double_digits = Date("12/13/2003");
    Date::Date date_single_day = Date("12/3/2003");
    Date::Date date_single_month = Date("2/13/2003");
    Date::Date unusual_date = Date("2000/5239/3");

    // date with single digit day, month 
    SECTION("Single digits month")
    {
        REQUIRE(date_single_digits.getMonth() == 2);
    }

    SECTION("Single digits day")
    {
        REQUIRE(date_single_digits.getDay() == 3);
    }

    SECTION("Single digits year")
    {
        REQUIRE(date_single_digits.getYear() == 2003);
    }

    // date with double digit day, month
    SECTION("Double digits month")
    {
        REQUIRE(date_double_digits.getMonth() == 12);
    }

    SECTION("Double digits day")
    {
        REQUIRE(date_double_digits.getDay() == 13);
    }

    SECTION("Double digits year")
    {
        REQUIRE(date_double_digits.getYear() == 2003);
    }

    //date with double digit month, single digit day
    SECTION("Double digits month, single digit day")
    {
        REQUIRE(date_single_day.getMonth() == 12);
    }

    SECTION("Double digits month, single digit day")
    {
        REQUIRE(date_single_day.getDay() == 3);
    }

    SECTION("Double digits month, single digit day")
    {
        REQUIRE(date_single_day.getYear() == 2003);
    }

    //date with single digit month, double digit day
    SECTION("Single digit month, double digit day")
    {
        REQUIRE(date_single_month.getMonth() == 2);
    }

    SECTION("Single digit month, double digit day")
    {
        REQUIRE(date_single_month.getDay() == 13);
    }

    SECTION("Single digit month, double digit day")
    {
        REQUIRE(date_single_month.getYear() == 2003);
    }

    // unusual date; probably not on the gregorian calendar
    SECTION("Unusual date month")
    {
        REQUIRE(unusual_date.getMonth() == 2000);
    }

    SECTION("Unusual date day")
    {
        REQUIRE(unusual_date.getDay() == 5239);
    }

    SECTION("Unusual date year")
    {
        REQUIRE(unusual_date.getYear() == 3);
    }
}

TEST_CASE("[setMonth]")
{
    Date::Date date;

    SECTION("set month to normal month")
    {
        date.setMonth(12);
        REQUIRE(date.getMonth() == 12);
    }

    SECTION("set month to unusual month")
    {
        date.setMonth(19374);
        REQUIRE(date.getMonth() == 19374);
    }

    SECTION("set month to zero")
    {
        date.setMonth(0);
        REQUIRE(date.getMonth() == 0);
    }
}

TEST_CASE("[setDay]")
{
    Date::Date date;

    SECTION("set day to normal day")
    {
        date.setDay(12);
        REQUIRE(date.getDay() == 12);
    }

    SECTION("set day to unusual day")
    {
        date.setDay(19374);
        REQUIRE(date.getDay() == 19374);
    }

    SECTION("set day to zero")
    {
        date.setDay(0);
        REQUIRE(date.getDay() == 0);
    }
}

TEST_CASE("[setYear]")
{
    Date::Date date;

    SECTION("set year to normal year")
    {
        date.setYear(2001);
        REQUIRE(date.getYear() == 2001);
    }

    SECTION("set year to unusual year")
    {
        date.setYear(19374);
        REQUIRE(date.getYear() == 19374);
    }

    SECTION("set year to zero")
    {
        date.setYear(0);
        REQUIRE(date.getYear() == 0);
    }
}

TEST_CASE("[valid]")
{
    Date::Date valid_date = Date(12, 17, 1999);
    Date::Date oversized_month_date = Date(15, 15, 1999);
    Date::Date oversized_day_date = Date(12, 50, 1999);
    Date::Date leap_day = Date(2, 29, 2020);
    Date::Date invalid_leap = Date(2, 29, 2019);

    SECTION("Valid date")
    {
        REQUIRE(valid_date.valid() == true);
    }

    SECTION("Invalid month")
    {
        REQUIRE(oversized_month_date.valid() == false);
    }

    SECTION("Invalid day")
    {
        REQUIRE(oversized_day_date.valid() == false);
    }

    SECTION("Valid leap year")
    {
        REQUIRE(leap_day.valid() == true);
    }

    SECTION("Invalid leap year")
    {
        REQUIRE(invalid_leap.valid() == false);
    }
}

TEST_CASE("[compareDate]")
{
    Date::Date jan_1_2018 = Date(1, 1, 2018);
    Date::Date jan_2_2018 = Date(1, 2, 2018);
    Date::Date feb_1_2018 = Date(2, 1, 2018);
    Date::Date jan_1_2017 = Date(1, 1, 2017);

    SECTION("Jan 1 2018 vs Jan 2 2018")
    {
        REQUIRE(jan_1_2018.compareDate(jan_2_2018) == 1);
    }

    SECTION("Jan 1 2018 vs Feb 1 2018")
    {
        REQUIRE(jan_1_2018.compareDate(feb_1_2018) == 1);
    }

    SECTION("Jan 1 2018 vs. Jan 1 2018")
    {
        REQUIRE(jan_1_2018.compareDate(jan_1_2018) == -1);
    }

    SECTION("Jan 1 2018 vs. Jan 1 2017")
    {
        REQUIRE(jan_1_2018.compareDate(jan_1_2017) == 0);
    }

    SECTION("Jan 1 2017 vs. Jan 1 2018")
    {
        REQUIRE(jan_1_2017.compareDate(jan_1_2018) == 1);
    }

    SECTION("Feb 1 2018 vs. Jan 1 2018")
    {
        REQUIRE(feb_1_2018.compareDate(jan_1_2018) == 0);
    }
}

TEST_CASE("[toString]")
{
    Date::Date default_date = Date();
    Date::Date two_digit_date = Date(12, 17, 1999);
    Date::Date unusual_date = Date(137, 212, 4000);
    
    SECTION("Default date")
    {
        REQUIRE(default_date.toString() == "1/1/2018");
    }

    SECTION("Two digit date")
    {
        REQUIRE(two_digit_date.toString() == "12/17/1999");
    }

    SECTION("Unusual date")
    {
        REQUIRE(unusual_date.toString() == "137/212/4000");
    }
}

TEST_CASE("[getCharIndex]")
{
    Date::Date double_digit_date = Date("12/17/1999");
    Date::Date single_digit_date = Date("1/1/2018");
    Date::Date big_date = Date("300/38573/201");

    vector<int> results;

    SECTION("Double digit date string")
    {
        results = double_digit_date.getCharIndex(double_digit_date.toString(), '/');
        REQUIRE(results.size() == 2);
        REQUIRE(results[0] == 2);
        REQUIRE(results[1] == 5);
    }

    SECTION("Single digit date string")
    {
        results = single_digit_date.getCharIndex(single_digit_date.toString(), '/');
        REQUIRE(results.size() == 2);
        REQUIRE(results[0] == 1);
        REQUIRE(results[1] == 3);
    }

    SECTION("Big date string")
    {
        results = big_date.getCharIndex(big_date.toString(), '/');
        REQUIRE(results.size() == 2);
        REQUIRE(results[0] == 3);
        REQUIRE(results[1] == 9);
    }

    SECTION("Char is not found")
    {
        results = big_date.getCharIndex(big_date.toString(), 'a');
        REQUIRE(results.size() == 0);
    }

}

//feed unit tests
TEST_CASE("Default feed constructor")
{
    Feed::Feed feed = Feed();
    
    SECTION("Articles size")
    {
        REQUIRE(feed.getArticles().size() == 0);
    }

    SECTION("Uni size")
    {
        REQUIRE(feed.getUnis().size() == 0);
    }

    SECTION("Tag size")
    {
        REQUIRE(feed.getTags().size() == 0);
    }

    SECTION("Max date")
    {
        REQUIRE(feed.getMaxDate().toString() == "1/1/2018");
    }

    SECTION("Min date")
    {
        REQUIRE(feed.getMinDate().toString() == "1/1/2018");
    }

    SECTION("Feed size")
    {
        REQUIRE(feed.getFeed().size() == 0);
    }
}

TEST_CASE("Custom constructor")
{
    string source = "Test source";
    string title = "Test title";
    string link = "https://www.fsf.org/";
    string content = "A brief inquiry into online relationships.";
    string date = "12/17/2001";
    
    Article article = Article(source, title, link, content, date);
    vector<article::Article::Article> articles;
    articles.push_back(Article(source, title, link, content, date));
    
    Feed::Feed feed = Feed(articles);

    SECTION("Articles")
    {
        Article curr_article = articles[0];

        REQUIRE(articles.size() == 1);
        REQUIRE(curr_article.getSource() == source);
        REQUIRE(curr_article.getTitle() == title);
        REQUIRE(curr_article.getLink() == link);
        REQUIRE(curr_article.getContent() == content);
        REQUIRE(curr_article.getDate().toString() == date);
    }

    SECTION("Uni size")
    {
        REQUIRE(feed.getUnis().size() == 1);
    }

    SECTION("Tag size")
    {
        REQUIRE(feed.getTags().size() == 0);
    }

    SECTION("Max date")
    {
        REQUIRE(feed.getMaxDate().toString() == "12/17/2001");
    }

    SECTION("Min date")
    {
        REQUIRE(feed.getMinDate().toString() == "12/17/2001");
    }

    SECTION("Feed size")
    {
        REQUIRE(feed.getFeed().size() == 1);
    }
}

TEST_CASE("[setArticles, vector<Article>]")
{
    string source = "Test source";
    string title = "Test title";
    string link = "https://www.fsf.org/";
    string content = "A brief inquiry into online relationships.";
    string date = "12/17/2001";
    
    Article article = Article(source, title, link, content, date);
    vector<article::Article::Article> articles;
    articles.push_back(Article(source, title, link, content, date));

    Feed::Feed feed;
    feed.setArticles(articles);

    SECTION("Articles size")
    {
        REQUIRE(feed.getArticles().size() == 1);
    }

    SECTION("Article content")
    {
        Article test_article = articles[0];
        
        REQUIRE(test_article.getSource() == source);
        REQUIRE(test_article.getTitle() == title);
        REQUIRE(test_article.getLink() == link);
        REQUIRE(test_article.getContent() == content);
        REQUIRE(test_article.getDate().toString() == date);
    }
}

TEST_CASE("[setArticles] vector<vector<Article>>")
{
    string source = "Test source";
    string title = "Test title";
    string link = "https://www.fsf.org/";
    string content = "A brief inquiry into online relationships.";
    string date = "12/17/2001";
    
    vector<vector<Article>> articles = {{Article()}, {Article(source, title, link, content, date)}};

    Feed::Feed feed;
    feed.setArticles(articles);

    SECTION("Articles size")
    {
        REQUIRE(feed.getArticles().size() == 2);
    }

    SECTION("Article content")
    {
        vector<Article> combined_articles = feed.getArticles();
        Article blank_article = combined_articles[0];
        Article sample_article = combined_articles[1];
        
        REQUIRE(blank_article.getTitle() == "");
        REQUIRE(blank_article.getSource() == "");
        REQUIRE(blank_article.getLink() == "");
        REQUIRE(blank_article.getContent() == "");
        REQUIRE(blank_article.getDate().toString() == "1/1/2018");

        REQUIRE(sample_article.getSource() == source);
        REQUIRE(sample_article.getTitle() == title);
        REQUIRE(sample_article.getLink() == link);
        REQUIRE(sample_article.getContent() == content);
        REQUIRE(sample_article.getDate().toString() == date);
    }
}

TEST_CASE("[setUnis]")
{
    vector<string> new_unis = {"1", "2"};

    Feed::Feed feed;
    feed.setUnis(new_unis);

    SECTION("Universities"){
        REQUIRE(feed.getUnis().size() == 2);
        REQUIRE(feed.getUnis()[0] == "1");
        REQUIRE(feed.getUnis()[1] == "2");
    }
}

TEST_CASE("[setTags]")
{
    vector<Tag> tags = {AI};
    Feed::Feed feed;
    feed.setTags(tags);

    SECTION("Tags"){
        REQUIRE(feed.getTags().size() == 1);
        REQUIRE(feed.getTags()[0] == AI);
    }
}

TEST_CASE("[setMaxDate]")
{
    Date::Date max_date = Date(14, 15, 2018);

    Feed::Feed feed;
    feed.setMaxDate(max_date);

    SECTION("Max date"){
        REQUIRE(feed.getMaxDate().toString() == "14/15/2018");
    }
}

TEST_CASE("[setMinDate]")
{
    Date::Date min_date = Date(2, 2, 2003);

    Feed::Feed feed;
    feed.setMinDate(min_date);

    SECTION("Min date"){
        REQUIRE(feed.getMinDate().toString() == "2/2/2003");
    }
}

TEST_CASE("[setFeed]")
{
    string source = "Test source";
    string title = "Test title";
    string link = "https://www.fsf.org/";
    string content = "A brief inquiry into online relationships.";
    string date = "12/17/2001";
    
    Article article = Article(source, title, link, content, date);
    vector<article::Article::Article> articles;
    articles.push_back(Article(source, title, link, content, date));
    
    Feed::Feed feed;
    feed.setFeed(articles);

    SECTION("Feed size")
    {
        REQUIRE(feed.getFeed().size() == 1);
    }

    SECTION("Feed content")
    {
        Article test_article = feed.getFeed()[0];
        
        REQUIRE(test_article.getSource() == source);
        REQUIRE(test_article.getTitle() == title);
        REQUIRE(test_article.getLink() == link);
        REQUIRE(test_article.getContent() == content);
        REQUIRE(test_article.getDate().toString() == date);
    }
}

TEST_CASE("[tagInList]")
{
   Tag tag_contained = AI;
   Tag tag_not_contained = RESEARCH;
    
    Feed::Feed feed;

    vector<Tag> tag_list = {AI, ML};

    SECTION("Tag is in list"){
        REQUIRE(feed.tagInList(tag_contained, tag_list) == true);
    }

    SECTION("Tag is not in list"){
        REQUIRE(feed.tagInList(tag_not_contained, tag_list) == false);
    }

}

TEST_CASE("[uniInList]")
{
    string contained_uni = "MSFC";
    string non_contained_uni = "LaRC";
    vector<string> unis = {"GSFC", "JSC", "MSFC"};

    Feed::Feed feed;

    SECTION("Uni is in list"){
        REQUIRE(feed.uniInList(contained_uni, unis) == true);
    }

    SECTION("Uni not in list"){
        REQUIRE(feed.uniInList(non_contained_uni, unis) == false);
    }
}

TEST_CASE("[tagsInList]")
{
    Article article;
    article.setTags({AI,ML});

    Feed::Feed feed;

    vector<Tag> test_tags_matching = {AI, ML};
    vector<Tag> test_tags_partial = {ML};
    vector<Tag> test_tags_unmatching = {RESEARCH};

    SECTION("Tags match"){
        REQUIRE(feed.tagsInList(article, test_tags_matching) == true);
    }

    SECTION("Tags partial match"){
        REQUIRE(feed.tagsInList(article, test_tags_partial) == false);
    }

    SECTION("Tags no match"){
        REQUIRE(feed.tagsInList(article, test_tags_unmatching) == false);
    }
}

TEST_CASE("[addArticle]")
{
    string source = "Test source";
    string title = "Test title";
    string link = "https://www.fsf.org/";
    string content = "A brief inquiry into online relationships.";
    string date = "12/17/2001";
    
    Article article = Article(source, title, link, content, date);
    Feed::Feed feed;

    feed.addArticle(article);
    vector<Article> feed_articles = feed.getArticles();

    SECTION("Articles size"){
        REQUIRE(feed_articles.size() == 1);
    }

    SECTION("Content")
    {
        Article test_article = feed_articles[0];
        
        REQUIRE(test_article.getSource() == source);
        REQUIRE(test_article.getTitle() == title);
        REQUIRE(test_article.getLink() == link);
        REQUIRE(test_article.getContent() == content);
        REQUIRE(test_article.getDate().toString() == date);
    }
}

// TEST_CASE("[sortLexigraph]")
// {
//     vector<Article> articles = {Article(), Article(), Article()};
//     articles[0].setTitle("c");
//     articles[1].setTitle("b");
//     articles[2].setTitle("a");

//     Feed::Feed feed;
//     feed.setArticles(articles);

//     vector<Article> sorted_articles = feed.getFeed();

//     SECTION("Sorted lexigraphically"){
//         REQUIRE(sorted_articles.size() == 3);

//         REQUIRE(sorted_articles[0].getTitle() == "a");
//         REQUIRE(sorted_articles[1].getTitle() == "b");
//         REQUIRE(sorted_articles[2].getTitle() == "c");
//     }
// }

TEST_CASE("[sortChrono]")
{
    vector<Article> articles = {Article(), Article(), Article()};
    
    articles[0].setTitle("c");
    articles[1].setTitle("b");
    articles[2].setTitle("a");
    
    articles[0].setDate(Date("1/1/2018"));
    articles[1].setDate(Date("1/3/2018"));
    articles[2].setDate(Date("2/1/2018"));

    Feed::Feed feed;
    feed.setArticles(articles);

    vector<Article> sorted_articles = feed.getArticles();

    SECTION("Sorted"){
        REQUIRE(sorted_articles.size() == 3);

        REQUIRE(sorted_articles[2].getDate().toString() == "2/1/2018");
        REQUIRE(sorted_articles[1].getDate().toString() == "1/3/2018");
        REQUIRE(sorted_articles[0].getDate().toString() == "1/1/2018");
    }
}