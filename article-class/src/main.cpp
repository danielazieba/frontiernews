#include <iostream>
#include "article.hpp"

using namespace std;
using namespace article;

int main(int argc, const char *argv[])
{
    Article::Article article; 
    cout << article.getContent();
}