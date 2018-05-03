ALL: Function ThreadTest CondTest ThreadPoolTest
BOOST_HOME_DIR=/home/gzliuyu2014/boost
BOOST_LIB=$(BOOST_HOME_DIR)/lib
BOOST_INCLUDE=$(BOOST_HOME_DIR)/include
CC=g++

Function:FunctionTest.cpp
	$(CC) -g -Wall -o $@ $^ -L$(BOOST_LIB) -I$(BOOST_INCLUDE) -lboost_thread -lboost_system -pthread 

ThreadTest: ThreadTest.cpp Thread.cpp
	$(CC) -g -Wall $^ -o $@ -L$(BOOST_LIB) -I$(BOOST_INCLUDE) -lboost_thread -lboost_system -lpthread 

CondTest: ConditionTest.cpp Thread.cpp
	$(CC) -g -Wall $^ -o $@ -L$(BOOST_LIB) -I$(BOOST_INCLUDE) -lboost_thread -lboost_system -lpthread 

ThreadPoolTest: ThreadPoolTest.cpp ThreadPool.cpp Thread.cpp
	$(CC) -g -Wall $^ -o $@ -L$(BOOST_LIB) -I$(BOOST_INCLUDE) -lboost_thread -lboost_system -lpthread 

clean:
	rm $(ALL)
