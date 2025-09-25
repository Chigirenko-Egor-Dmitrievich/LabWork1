CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic

TARGET = test 
REDACTOR = start

TARGET_SOURCES = main.cpp plugins.cpp 
SOURCES = redactor.cpp plugins.cpp 

TARGET_OBJECTS = $(TARGET_SOURCES:.cpp=.o)
OBJECTS = $(SOURCES:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(TARGET_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET_OBJECTS)
	
all: $(TARGET)

redactor: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(REDACTOR) $(OBJECTS)

format:
	astyle -A1 -s4 *.cpp *.hpp

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET_OBJECTS)

cleanall:
	rm -f $(OBJECTS) $(REDACTOR)
	rm -f $(TARGET_OBJECTS) $(TARGET)
	rm -f 2.bmp 3.bmp 4.bmp
