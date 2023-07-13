CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -fPIC

# Name of the library
LIBRARY := lib1.so

# Source files
SOURCES := lib1.cpp

# Object files
OBJECTS := $(SOURCES:.cpp=.o)

# Build rules
all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CXX) -shared -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(LIBRARY) $(OBJECTS)
