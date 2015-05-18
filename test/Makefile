CXX = g++
CXXFLAGS = -g -Wall -static -fprofile-arcs -ftest-coverage -I./ -I$(CPPUTEST_HOME)/include
LDFLAGS = -L./ -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
CPPUTEST_HOME = ./
TARGET = ButtonTest
SRCS = SW_Buttontest.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	 $(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

$(OBJS): $(SRCS)
	$(CXX) -c $(CXXFLAGS) $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) *.gcno *.gcov *~
	find . -name "*.gcda" | xargs -r rm
