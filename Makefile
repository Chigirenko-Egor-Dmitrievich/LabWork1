CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic -Iinclude

TARGET = run
TEST_TARGET = test 
REDACTOR = start

TARGET_SOURCES = src/main.cpp src/plugins.cpp src/gaussian_filter.cpp src/rotate_image.cpp 
TEST_TARGET_SOURCES = tests/test.cpp src/plugins.cpp src/gaussian_filter.cpp src/rotate_image.cpp
SOURCES = src/redactor.cpp src/plugins.cpp src/gaussian_filter.cpp src/rotate_image.cpp

TARGET_OBJECTS = $(TARGET_SOURCES:.cpp=.o)
TEST_TARGET_OBJECTS = $(TEST_TARGET_SOURCES:.cpp=.o)
OBJECTS = $(SOURCES:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(TARGET_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET_OBJECTS)
	
all: $(TARGET)

test: $(TEST_TARGET_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_TARGET_OBJECTS) -lgtest -lgtest_main -lpthread

redactor: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(REDACTOR) $(OBJECTS)

format:
	astyle -A1 -s4 *.cpp *.hpp

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET_OBJECTS)
	rm -f $(TEST_TARGET_OBJECTS)

cleanall:
	rm -f $(OBJECTS) $(REDACTOR)
	rm -f $(TARGET_OBJECTS) $(TARGET)
	rm -f $(TEST_TARGET_OBJECTS) $(TEST_TARGET)
	rm -f Images/2.bmp Images/3.bmp Images/4.bmp

.PHONY: all test clean
