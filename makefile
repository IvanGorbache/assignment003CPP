CC := g++
CFLAGS := -Wall -Wextra -std=c++11

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := Catan

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
