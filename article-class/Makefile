CXX=clang++
TESTEXE=tests
BUILDARGS= -g -Wall -std=c++11

all : clean main $(TESTEXE)

date.o: src/date.hpp src/date.cpp
	$(CXX) $(BUILDARGS) -c -o date.o src/date.hpp

article.o: src/article.hpp src/article.cpp date.o
	$(CXX) $(BUILDARGS) -c -o article.o src/article.hpp

feed.o: src/feed.hpp src/feed.cpp date.o article.o
	$(CXX) $(BUILDARGS) -c -o feed.o src/feed.hpp

article_tests.o: tests/article_tests.cpp src/article.cpp
	$(CXX) $(BUILDARGS) -c -o article_tests.o tests/article_tests.cpp

article_tests: feed.o article_tests.o
	$(CXX) $(BUILDARGS) -o article_tests article_tests.o

date_tests.o: tests/date_tests.cpp src/date.cpp
	$(CXX) $(BUILDARGS) -c -o date_tests.o tests/date_tests.cpp

date_tests: date.o date_tests.o
	$(CXX) $(BUILDARGS) -o date_tests date_tests.o

clean :
	rm -rf *.o *.dSYM