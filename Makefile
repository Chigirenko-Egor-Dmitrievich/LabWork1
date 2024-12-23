CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic 
TARGET = start
SOURCES = main.cpp   debug_plugin.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

format:
	astyle -A1 -s4 *.cpp *.hpp

clean:
	rm -f $(OBJECTS)

cleanall:
	rm -f $(OBJECTS) $(TARGET)
